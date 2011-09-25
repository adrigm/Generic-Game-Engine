#include "scene.h"

namespace BGE
{
Scene::Scene(SceneID m_id, App* p_app) :
	id(m_id),
	app(p_app),
	m_init(false),
	m_paused(false),
	m_cleanup(false),
	elapsed_time(0.0f),
	paused_time(0.0f)
{
	// Comprobamos que el puntero es correcto
	assert(NULL != p_app && "Scene::Scene() puntero p_app corrupto");

	// Puntero a la aplcación padre
	app = p_app;

	if (app != NULL)
	{
		app->log << "Scene::Scene() Constructor con ID=" << id << " llamado" << std::endl;
	}
}

Scene::~Scene()
{
	// Comprobamos que aún exista el puntero
	if (app != NULL)
	{
		app->log << "Scene::~Scene() Destructor con ID=" << id << " llamado" << std::endl;
	}

	// Eliminamos el puntero innecesario
	app = NULL;
}

SceneID Scene::GetID() const
{
	return id;
}

bool Scene::IsInitComplete() const
{
	return m_init;
}

bool Scene::IsPaused() const
{
	return m_paused;
}

void Scene::Init()
{
	app->log << "Scene::Init() con ID=" << id << " llamado" << std::endl;

	// Comprobamos si es necesario hacer limpieza
	if (m_cleanup)
	{
		Cleanup();
		m_cleanup = false;
	}

	// Comprobamos si la escena esta o no inicializada
	if (!m_init)
	{
		// Ponemos la escena en inicializada
		m_init = true;
		// Quitamos el pause si está activado
		m_paused = false;
		// Ponemos los contadores de tiempo a cero y reseteamos los relojes
		elapsed_time = 0.0f;
		elapsed_clock.Reset();
		paused_time = 0.0f;
		paused_clock.Reset();
	}
}

void Scene::DeInit()
{
	app->log << "Scene::DeInit() con ID=" << id << " llamado" << std::endl;

	// Comrpobamos que la escena esté inicializada
	if(m_init)
	{
		// Activamos la necesidad de limpieza
		m_cleanup = true;
		// Establecemos la escena como no inicializada
		m_init = false;
		// Actualizamos los contadores
		elapsed_time += elapsed_clock.GetElapsedTime();
		if(m_paused)
		{
			paused_time += paused_clock.GetElapsedTime();
		}
	}
}

void Scene::Pause()
{
	app->log << "Scene::Pause() con ID=" << id << " llamado" << std::endl;

	// Comprobamos si no está pausada ya la escena
	if (!m_paused)
	{
		// La ponemos en estadod de pausa
		m_paused = true;
		// Reseteamos el reloj de pausa
		paused_clock.Reset();
	}
}

void Scene::Resume()
{
	app->log << "Scene::Resume() con ID=" << id << " llamado" << std::endl;
	
	// Comprobamos si el juego está en pausa
	if (m_paused)
	{
		// Quitamos la pausa
		m_paused = false;
		// Añadimos el tiempo pausado a su contador
		paused_time += paused_clock.GetElapsedTime();
	}
}

void Scene::Cleanup()
{
	app->log << "Scene::Cleanup() con ID=" << id << " llamado" << std::endl;
}

float Scene::GetElapsedTime() const
{
	float result = elapsed_clock.GetElapsedTime();

	if(!m_init)
	{
		result = elapsed_time;
	}

	return result;
}

} // Namespace BGE
