////////////////////////////////////////////////////////////
//
// GGE - Generic Game Engine
// Copyright (C) 2011-2012 Adrián Guerra (adrigm@razonartificial.com)
//
////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>
#include <SFML/System.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/StringUtil.hpp>
#include <GGE/Core/ConfigReader.hpp>
#include <GGE/Core/SceneManager.hpp>
#include <GGE/Core/Scene.hpp>
#include <iostream> // Quitar

namespace GGE
{

App* App::ms_instance = 0;

App::App() :
	videoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP),
	window(),
	contextSettings(),
	windowStyle(sf::Style::Default),
	m_title("GGE Application"),
	m_exitCode(GGE::StatusNoError),
	m_running(false),
	m_executableDir(""),
	m_InitialScene(0),
	m_updateTime(),
	m_totalTime()
{
#if defined(GGE_DEBUG)
	// Creamos el archivo de log
	boost::filesystem::path path(boost::filesystem::current_path() / "log.txt");
	log.open(path.c_str());
	log << "LogFile: " << path.string() << std::endl << std::endl;
#endif
	// Escribimos en el log
	log << "App::App() consructor llamado" << std::endl;
}

App::~App()
{
	log << "App::dtor()" << std::endl;

	log << std::endl << "Archivo de log cerrado" << std::endl;

#if defined(GGE_DEBUG)
	log.close();
#endif
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

void App::ProcessArguments(int argc, char** argv)
{
	// TODO: Implementar Procesador de argumentos

	if (argc == 1)
	{
		log << "Aplicación: " << argv[0];
	}
	else
	{
		log << "Aplicación: " << argv[0] << ". Comandos: ";
		m_executableDir = argv[0];
		for (int i = 1; i < argc; i++)
		{
			log << argv[i];
		}
		log << std::endl;
	}
}

void App::RegisterExecutableDir(int argc, char** argv)
{
	if (argc > 0)
	{
		boost::filesystem::path path;
		path = boost::filesystem::system_complete(argv[0]);
		path = path.remove_filename();
		m_executableDir = path.string();
#if defined(GGE_SYSTEM_WINDOWS)
		m_executableDir.append("\\");
#else
		m_executableDir.append("/");
#endif
		log << "Directorio de la aplicacion: " << m_executableDir << std::endl;
	}
}

std::string App::GetExecutableDir() const
{
	return m_executableDir;
}

int App::Run()
{
	// Comprobamos que se ha llamado a RegisterExecutableDir para establecer la ruta del ejecutable
	if (m_executableDir == "")
	{
		log << "[ERROR] No se ha definido la ruta del ejecutable. ";
		log << "LLamar a App::RegisterExecutableDir() antes que a App::Run()";
		log << std::endl;

		return GGE::StatusAppInitFailed;
	}

	// Cambiamos los aplicacion a ejecutandose
	m_running = true;

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
	return m_exitCode;
}

bool App::IsRunning() const
{
	return m_running;
}

sf::Time App::GetUpdateTime() const
{
	return m_updateTime;
}

sf::Time App::GetTotalTime() const
{
	return m_totalTime;
}

void App::Quit(int the_exit_code)
{
	m_exitCode = the_exit_code;
	m_running = false;
}

std::string App::GetTitle() const
{
	return m_title;
}

void App::SetTitle(const std::string theTitle)
{
	m_title = theTitle;
	window.setTitle(theTitle);

	log << "App::SetTitle() Titulo cambiado a: " << theTitle << std::endl;
}

void App::SetFirstScene(GGE::Scene* theScene)
{
	if (m_InitialScene == 0)
	{
		m_InitialScene = theScene;
		log << "Establecida escena inicial: " << theScene->GetID() << std::endl;
	}
	else
	{
		log << "Ya se habia establecido una escena inicial" << std::endl;
	}
}

void App::PreInit()
{
	GGE::ConfigReader anConfig;
	// TODO: Cambiar para buscar donde se encuentra el ejecutable
	anConfig.LoadFromFile("window.cfg");

	GGE::Uint32 width = anConfig.GetUint32("window", "width", DEFAULT_VIDEO_WIDTH);
	GGE::Uint32 height = anConfig.GetUint32("window", "height", DEFAULT_VIDEO_HEIGHT);
	GGE::Uint32 bpp = anConfig.GetUint32("window", "bpp", DEFAULT_VIDEO_BPP);
	bool fullscreen = anConfig.GetBool("window", "fullscreen", false);

	// TODO: Comprobar si el formato es válido
	
	/*sf::VideoMode v = sf::VideoMode::getDesktopMode();
	std::cout << v.width << ", " << v.height << ", " << v.bitsPerPixel << std::endl;

	std::vector<sf::VideoMode> b = sf::VideoMode::getFullscreenModes();
	std::vector<sf::VideoMode>::const_iterator it;
	for (it = b.begin(); it != b.end(); it++)
	{
		std::cout << it->width << ", " << it->height << ", " << it->bitsPerPixel << std::endl;
	}*/

	videoMode.width = width;
	videoMode.height = height;
	videoMode.bitsPerPixel = bpp;

	if (fullscreen)
		windowStyle = sf::Style::Fullscreen;

	// Create a RenderWindow object using VideoMode object above
	window.create(videoMode, m_title, windowStyle, contextSettings);

	// Activamos VSync
	window.setVerticalSyncEnabled(true);

	log << "App::PreInit() Completado" << std::endl;
}

void App::Init()
{
	// Creamos el SceneManager
	sceneManager = GGE::SceneManager::Instance();

	// Establecemos la escene inicial
	if (m_InitialScene != 0)
	{
		// Añadimos la primera escena
		sceneManager->AddScene(m_InitialScene);
		// La establecemos como escena activa
		sceneManager->SetActiveScene(m_InitialScene->GetID());
		sceneManager->ChangeScene(sceneManager->mNextScene);
	}
	else
	{
		log << "[ERROR] No se ha establecido escena inicial. LLamar a App::SetFirstScene() primero" 
			<< std::endl;
		// Salimos con código -2
		Quit(GGE::StatusAppInitFailed);
	}

	log << "App::Init() Completado" << std::endl;
}

void App::Loop()
{
	// Bucle mientras se esté ejecutando y la ventana esté abierta
	while (IsRunning() && window.isOpen())
	{
		// Manejamos los eventos de la ventana
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:			// La ventana es cerrada
				Quit(StatusAppOK);
				break;
			case sf::Event::GainedFocus:	// La ventana obtiene el foco
				sceneManager->ResumeScene();
				break;
			case sf::Event::LostFocus:		// La ventana pierde el foco
				sceneManager->PauseScene();
				break;
			default:	// Otros eventos se los pasamos a la ecena activa
				sceneManager->EventScene(event);
			} // switch (event.Type)
		} // while (window.GetEvent(event))

		// Obtenemos el tiempo pasado en cada ciclo
		m_updateTime = m_updateClock.restart();
		m_totalTime += m_updateTime;

		// Llamamos al método Update() de la escena activa
		sceneManager->UpdateScene();

		// Llamamos al método Draw() de la escena activa
		sceneManager->DrawScene();
		
		// Actualizamos la ventana
		window.display();

		// Comprobamos cambios de escena
		if (sceneManager->HandleChangeScene())
		{
			// Cambiamos el puntero de la escena activa
			sceneManager->ChangeScene(sceneManager->mNextScene);
		}
	} // while (IsRunning() && window.IsOpened())
}

void App::Cleanup()
{
	// Eliminamos todas las escenas
	sceneManager->RemoveAllScene();

	// Eliminamos el SceneManager
	GGE::SceneManager::Release();

	log << "App::Cleanup() Completado" << std::endl;
}

} // namespace GGE