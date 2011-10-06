#include <BGE/Core/classes/App.hpp>
#include <BGE/Core/classes/ConfigReader.hpp>

namespace BGE
{
App* App::ms_instance = 0;

App::App() :
	title("Basic Game Engine"),
	video_mode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP),
	window(),
	window_settings(),
	window_style(sf::Style::Close | sf::Style::Resize),
	input(window.GetInput()),
	exit_code(BGE::StatusNoError),
	running(false),
	update_clock(),
	update_time(0.0f),
	scene(NULL),
	scene_manager(),
	asset_manager()
{
	// Creamos el archivo de log
	log_file.assign(this->GetExecutableDir() + "log.txt");
	log.open(log_file.c_str());
	log << "LogFile: " << log_file << std::endl;

	// Escribimos en el log
	log << "App::App() consructor llamado" << std::endl;
}

App::~App()
{
	// Escribimos en el log el código de salida
	log << "App::Run() terminado con código: " << exit_code << std::endl;
}

void App::SetFirstScene(Scene* first)
{
	// Comprobamos que ya no se haya establecido una escena como primera
	if (!scene)
	{
		scene = first;
	}
}

void App::ProcessArguments(int argc, char* argv[])
{
	// TODO: Implementar procesador de argumentos
	log << "App::ProcessArguments() Program: " << argv[0] << std::endl;
	log << "App::ProcessArguments() Command Line: ";
	for(int iloop = 1; iloop<argc; iloop++)
	{
		log << argv[iloop] << ", ";
	}
	log << std::endl;

	// Obtenemos la ruta el ejecutable
	executable_dir = argv[0];
	// Buscamos rutas de Windows
	int indx = executable_dir.find_last_of('\\');
	// Si devuelve -1 buscamos rutas Unix.
	if (indx == -1)
		int indx = executable_dir.find_last_of('/');
	executable_dir = executable_dir.substr(0, indx+1);
}

int App::Run()
{
	// Cambiamos los aplicacion a ejecutandose
	running = true;

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
	return exit_code;
}

bool App::IsRunning() const
{
	return running;
}

float App::GetUpdateTime() const
{
	return update_time;
}

void App::Quit(int the_exit_code)
{
	exit_code = the_exit_code;
	running = false;
}

std::string App::GetExecutableDir() const
{
	return executable_dir;
}

void App::PreInit()
{
	ConfigReader config;       // For reading .INI style files
 
	// Use our default configuration file to obtain the initial window settings
	config.RegisterApp(this);  // For logging purposes, let ConfigReader know about us
	config.Read(this->GetExecutableDir() + "resources/window.cfg"); // Read in our window settings
 
	// Are we in Fullscreen mode?
	if(config.GetBool("window","fullscreen", false))
	{
	  window_style = sf::Style::Fullscreen;
	}
 
	// What size window does the user want?
	video_mode.Width = config.GetUint32("window","width",DEFAULT_VIDEO_WIDTH);
	video_mode.Height = config.GetUint32("window","height",DEFAULT_VIDEO_HEIGHT);
	video_mode.BitsPerPixel = config.GetUint32("window","depth",DEFAULT_VIDEO_BPP);
 
	// For Fullscreen, verify valid VideoMode, otherwise revert to defaults for Fullscreen
	if(sf::Style::Fullscreen == window_style && false == video_mode.IsValid())
	{
	  video_mode.Width = DEFAULT_VIDEO_WIDTH;
	  video_mode.Height = DEFAULT_VIDEO_HEIGHT;
	  video_mode.BitsPerPixel = DEFAULT_VIDEO_BPP;
	}
 
	// Create a RenderWindow object using VideoMode object above
	window.Create(video_mode, title, window_style, window_settings);

	// Activamos VSync
	window.UseVerticalSync(true);

	log << "App::PreInit() Completado" << std::endl;
}

void App::Init()
{
	// Creamos el SceneManager
	scene_manager = SceneManager::Instance();

	// Pasamos la dirección de la App al SceneManager
	scene_manager->RegisterApp(this);

	// Creamos el AssetManager
	asset_manager = new AssetManager();

	// Registramos el AssetManager
	asset_manager->RegisterApp(this);


	// Comprobamos que se haya establecido escena inicial
	if (scene != NULL)
	{
		// Añadimos la primera escena
		scene_manager->AddScene(scene);

		// La establecemos como escena activa
		scene_manager->ChangeScene(scene->GetID());
	}
	else
	{
		// Escribimos el error en el log
		log << "ERROR: App::Init() No se ha establecido escena inicial"
			<< std::endl;
			
		// Salimos con código -2
		Quit(StatusAppInitFailed);
	}

	// Escribimos en el log
	log << "App::Init() Completado" << std::endl;
}

void App::Loop()
{
	// Bucle mientras se esté ejecutando y la ventana esté abierta
	while (IsRunning() && window.IsOpened())
	{
		// Manejamos los eventos de la ventana
		sf::Event event;
		while (window.GetEvent(event))
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
				scene_manager->EventScene(event);
			} // switch (event.Type)
		} // while (window.GetEvent(event))
		
		// Obtenemos el tiempo pasado en cada ciclo
		update_time = update_clock.GetElapsedTime();
		update_clock.Reset();

		// Llamamos al método Update() de la escena activa
		scene_manager->UpdateScene();

		// Llamamos al método Draw() de la escena activa
		scene_manager->DrawScene();

		// Actualizamos la ventana
		window.Display();

		// Comprobamos cambios de escena
		if (scene_manager->next_scene != "")
		{
			scene_manager->ChangeScene(scene_manager->next_scene);
			scene_manager->next_scene = "";
		}

	} // while (IsRunning() && window.IsOpened())
}

void App::Cleanup()
{
	scene_manager->RemoveAllScene();

	// Eliminamos el SceneManager
	SceneManager::Release();
}

App* App::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new App();
	}
	return ms_instance;
}

void App::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}
} // namespace BGE
