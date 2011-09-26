#include "scene_manager.h"

namespace BGE
{

SceneManager* SceneManager::ms_instance = 0;

SceneManager::SceneManager() :
	active_scene(NULL),
	inactives_scenes(),
	next_scene("")
{
}

SceneManager::~SceneManager()
{
	app->log << "SceneManager::~SceneManager() Destructor llamado" << std::endl;
}

void SceneManager::AddScene(Scene* a_scene)
{
	bool add = false;
	for (int i = 0; i < inactives_scenes.size(); i++)
	{
		if (inactives_scenes[i] == NULL)
		{
			inactives_scenes[i] = a_scene;
			add = true;
			app->log << "SceneManager::AddScene() añadida escena con ID="
					 << a_scene->GetID() << std::endl;
			break;
		}
	}
	if (!add)
	{
		inactives_scenes.push_back(a_scene);
		app->log << "SceneManager::AddScene() añadida escena con ID="
					 << a_scene->GetID() << std::endl;
	}
}

void SceneManager::SetActiveScene(SceneID id_scene)
{
	next_scene = id_scene;
}

void SceneManager::ChangeScene(SceneID id_scene)
{
	for (int i = 0; i < inactives_scenes.size(); i++)
	{
		if (inactives_scenes[i] != NULL && id_scene == inactives_scenes[i]->GetID())
		{
			Scene* aux = active_scene;
			active_scene = inactives_scenes[i];
			inactives_scenes[i] = aux;
			// Llamamos al Init() si no ha sido llamado
			if (!active_scene->IsInitComplete())
			{
				active_scene->Init();
			}
			app->log << "SceneManager::ChangeScene() activa escena con ID="
					 << id_scene << std::endl;
			break;
		}
	}
}

void SceneManager::RemoveScene(SceneID id_scene)
{
	for (int i = 0; i < inactives_scenes.size(); i++)
	{
		if (inactives_scenes[i] != NULL && id_scene == inactives_scenes[i]->GetID())
		{
			inactives_scenes[i]->Cleanup();
			delete inactives_scenes[i];
			inactives_scenes[i] = NULL;
			app->log << "SceneManager::RemoveScene() Eliminada escena con ID="
					 << id_scene << std::endl;
			break;
		}
	}
}

void SceneManager::RemoveAllScene()
{
	for (int i = 0; i < inactives_scenes.size(); i++)
	{
		if(inactives_scenes[i] != NULL)
		{
			app->log << "SceneManager::RemoveAllScene() Eliminada escena con ID="
					 << inactives_scenes[i]->GetID() << std::endl;
			inactives_scenes[i]->Cleanup();
			delete inactives_scenes[i];
			inactives_scenes[i] = NULL;
		}
	}
	
	if (active_scene)
	{
		app->log << "SceneManager::RemoveAllScene() Eliminada escena con id="
					<< active_scene->GetID() << std::endl;
		active_scene->Cleanup();
		delete active_scene;
		active_scene = NULL;
	}
}

void SceneManager::RemoveAllInactiveScene()
{
	for (int i = 0; i < inactives_scenes.size(); i++)
	{
		if(inactives_scenes[i] != NULL)
		{
			app->log << "SceneManager::RemoveAllInactiveScene() Eliminada escena con id="
					 <<inactives_scenes[i]->GetID() << std::endl;
			inactives_scenes[i]->Cleanup();
			delete inactives_scenes[i];
			inactives_scenes[i] = NULL;
		}
	}
}

void SceneManager::DrawScene()
{
	active_scene->Draw();
}

void SceneManager::UpdateScene()
{
	active_scene->Update();
}

void SceneManager::EventScene(sf::Event a_event)
{
	active_scene->Events(a_event);
}

SceneManager* SceneManager::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new SceneManager();
	}
	return ms_instance;
}

void SceneManager::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

} // Namespace BGE
