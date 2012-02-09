#include <GGE/Core/App.hpp>
#include <GGE/Core/ConfigReader.hpp>

namespace GGE
{

App::App(const std::string TheTitle) :
	mTitle(TheTitle),
	mVideoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP),
	mWindow(),
	mWindowSettings(),
	mWindowStyle(sf::Style::Close | sf::Style::Resize),
	mInput(mWindow.GetInput()),
	mExitCode(GGE::StatusNoError),
	mRunning(false),
	mUpdateClock(),
	mUpdateTime(0.0f),
	mScene(NULL)
{
	// Creamos el archivo de log
	mLogFile.assign(this->GetExecutableDir() + "log.txt");
	mLog.open(mLogFile.c_str());
	mLog << "LogFile: " << mLogFile << std::endl;

	// Escribimos en el log
	mLog << "App::App() consructor llamado" << std::endl;
}

App::~App()
{
	// Escribimos en el log el código de salida
	mLog << "App::Run() terminado con codigo: " << mExitCode << std::endl;
}

void App::ProcessArguments(int argc, char* argv[])
{
	// TODO: Implementar procesador de argumentos
	mLog << "App::ProcessArguments() Program: " << argv[0] << std::endl;
	mLog << "App::ProcessArguments() Command Line: ";
	for(int iloop = 1; iloop<argc; iloop++)
	{
		mLog << argv[iloop] << ", ";
	}
	mLog << std::endl;

	// Obtenemos la ruta el ejecutable
	mExecutableDir = argv[0];
	// Buscamos rutas de Windows
	int indx = mExecutableDir.find_last_of('\\');
	// Si devuelve -1 buscamos rutas Unix.
	if (indx == -1)
		int indx = mExecutableDir.find_last_of('/');
	mExecutableDir = mExecutableDir.substr(0, indx+1);
}

int App::Run()
{
	// Cambiamos los aplicacion a ejecutandose
	mRunning = true;

	// PreInit() Se encarga de 2 cosas:
	// 1) Abrir el archivo de configuración
	// 2) Crear la ventana con los valores obtenidos del archivo
	PreInit();

	// Init() Se encarga de crear el SceneManager y cargar la primera escena
	Init();
	
	// Loop() Implementa el bucle de la aplicación
	Loop();
	
	// Cleanup() Se encarga de eliminar todos los objetos creados
	Cleanup();

	// Código de salida de la aplicación
	return mExitCode;
}

bool App::IsRunning() const
{
	return mRunning;
}

float App::GetUpdateTime() const
{
	return mUpdateTime;
}

void App::Quit(int the_exit_code)
{
	mExitCode = the_exit_code;
	mRunning = false;
}

std::string App::GetExecutableDir() const
{
	return mExecutableDir;
}

void App::PreInit()
{
	ConfigReader anConfig;       // For reading .INI style files
 
	// Use our default configuration file to obtain the initial window settings
	anConfig.RegisterApp(this);  // For logging purposes, let ConfigReader know about us
	anConfig.Read(this->GetExecutableDir() + "resources/window.cfg"); // Read in our window settings
 
	// Are we in Fullscreen mode?
	if(anConfig.GetBool("window","fullscreen", false))
	{
	  mWindowStyle = sf::Style::Fullscreen;
	}
 
	// What size window does the user want?
	mVideoMode.Width = anConfig.GetUint32("window","width",DEFAULT_VIDEO_WIDTH);
	mVideoMode.Height = anConfig.GetUint32("window","height",DEFAULT_VIDEO_HEIGHT);
	mVideoMode.BitsPerPixel = anConfig.GetUint32("window","depth",DEFAULT_VIDEO_BPP);
 
	// For Fullscreen, verify valid VideoMode, otherwise revert to defaults for Fullscreen
	if(sf::Style::Fullscreen == mWindowStyle && false == mVideoMode.IsValid())
	{
	  mVideoMode.Width = DEFAULT_VIDEO_WIDTH;
	  mVideoMode.Height = DEFAULT_VIDEO_HEIGHT;
	  mVideoMode.BitsPerPixel = DEFAULT_VIDEO_BPP;
	}
 
	// Create a RenderWindow object using VideoMode object above
	mWindow.Create(mVideoMode, mTitle, mWindowStyle, mWindowSettings);

	// Activamos VSync
	mWindow.UseVerticalSync(true);

	mLog << "App::PreInit() Completado" << std::endl;
}

void App::Init()
{
	// Creamos el SceneManager
	mSceneManager = new SceneManager(this);

	// Creamos el AssetManager
	mAssetManager = new AssetManager(this);

	// Comprobamos que se haya establecido escena inicial
	if (mScene != NULL)
	{
		// Añadimos la primera escena
		mSceneManager->AddScene(mScene);

		mSceneManager->SetActiveScene(mScene->GetID());

		// La establecemos como escena activa
		mSceneManager->ChangeScene(mSceneManager->mNextScene);
	}
	else
	{
		// Escribimos el error en el log
		mLog << "ERROR: App::Init() No se ha establecido escena inicial"
			<< std::endl;
			
		// Salimos con código -2
		Quit(StatusAppInitFailed);
	}

	// Escribimos en el log
	mLog << "App::Init() Completado" << std::endl;
}

void App::Loop()
{
	// Bucle mientras se esté ejecutando y la ventana esté abierta
	while (IsRunning() && mWindow.IsOpened())
	{
		// Manejamos los eventos de la ventana
		sf::Event event;
		while (mWindow.GetEvent(event))
		{
			switch (event.Type)
			{
			case sf::Event::Closed:			// La ventana es cerrada
				Quit(StatusAppOK);
				break;
			case sf::Event::GainedFocus:	// La ventana obtiene el foco
				break;
			case sf::Event::LostFocus:		// La ventana pierde el foco
				break;
			case sf::Event::Resized:		// La ventana es redimensionada
				break;
			default:	// Otros eventos se los pasamos a la ecena activa
				mSceneManager->EventScene(event);
			} // switch (event.Type)
		} // while (window.GetEvent(event))
		
		// Obtenemos el tiempo pasado en cada ciclo
		mUpdateTime = mUpdateClock.GetElapsedTime();
		mUpdateClock.Reset();

		// Llamamos al método Update() de la escena activa
		mSceneManager->UpdateScene();

		// Llamamos al método Draw() de la escena activa
		mSceneManager->DrawScene();

		// Actualizamos la ventana
		mWindow.Display();

		// Comprobamos cambios de escena
		if (mSceneManager->HandleChangeScene())
		{
			mSceneManager->ChangeScene(mSceneManager->mNextScene);
		}

	} // while (IsRunning() && window.IsOpened())
}

void App::Cleanup()
{
	// Eliminamos todas las escenas del SceneManager
	mSceneManager->RemoveAllScene();

	// Eliminamos todos los recursos
	mAssetManager->Cleanup();

	// Eliminamos el SceneManager
	delete mSceneManager;

	// Eliminamos el AssetManager
	delete mAssetManager;

	mLog << "App::Cleanup() Completado" << std::endl;
}

void App::SetFirstScene(IScene* theScene)
{
	if (mScene == NULL)
	{
		mScene = theScene;
	}
}

} // namespace GGE