#include <GGE/Core/SceneManager.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/Scene.hpp>


namespace GGE
{

SceneManager* SceneManager::ms_instance = 0;

SceneManager::SceneManager() :
	m_app(NULL),
	mActiveScene(NULL),
	mInactivesScenes(),
	mNextScene("")
{
	m_app = GGE::App::Instance();
	m_app->log << "SceneManager::ctor()" << std::endl;
}

SceneManager::~SceneManager()
{
	m_app->log << "SceneManager::dtor()" << std::endl;
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


void SceneManager::AddScene(Scene* theScene)
{
	std::map<SceneID, Scene*>::const_iterator it = mInactivesScenes.find(theScene->GetID());
	if (it != mInactivesScenes.end())
	{
		// Si ya existe la escena salimos
			m_app->log << "SceneManager::AddScene() ya existe una escena con ID=" 
				<< theScene->GetID() << std::endl; 
			return;
	}

	// Si no existe la añadimos a la lista
	mInactivesScenes[theScene->GetID()] = theScene;

	// Inicializamos la escena si no lo esta
	if (!theScene->IsInitComplete())
	{
		theScene->Init();
	}

	m_app->log << "SceneManager::AddScene() Añadida escena con ID=" 
		<< theScene->GetID() << std::endl;
}

void SceneManager::SetActiveScene(SceneID theSceneID)
{
	std::map<SceneID, Scene*>::const_iterator it = mInactivesScenes.find(theSceneID);
	if (it != mInactivesScenes.end())
	{
		mNextScene = theSceneID;
		return;
	}

	if (theSceneID == mActiveScene->GetID())
	{
		m_app->log << "SceneManager::SetActiveScene() la escena con ID=" <<  mActiveScene->GetID()
			<< "ya esta activa" << std::endl;
		return;
	}

	m_app->log << "SceneManager::SetActiveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::ChangeScene(SceneID theSceneID)
{
	mNextScene = "";
	if (mActiveScene != NULL)
		mInactivesScenes[mActiveScene->GetID()] = mActiveScene;
	mActiveScene = mInactivesScenes[theSceneID];
	mInactivesScenes.erase(theSceneID);
	m_app->log << "SceneManager::ChangeScene() Activa escena con ID=" << theSceneID << std::endl;
}

void SceneManager::RemoveScene(SceneID theSceneID)
{
	// Buscamos en la lista de escenas inactivas
	std::map<SceneID, Scene*>::const_iterator it = mInactivesScenes.find(theSceneID);
	if (it != mInactivesScenes.end())
	{
		m_app->log << "SceneManager::RemoveScene() Eliminada escena con ID=" 
			<< it->first << std::endl;
		it->second->Cleanup();
		delete it->second;
		mInactivesScenes.erase(it);
		return;
	}

	if (theSceneID == mActiveScene->GetID())
	{
		m_app->log << "SceneManager::RemoveScene() la escena con ID=" << mActiveScene->GetID() 
			<< "esta activa y no se puede eliminar" << std::endl;
		return;
	}

	m_app->log << "SceneManager::RemoveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::RemoveAllInactiveScene()
{
	// Recorremos la lista de escenas inactivas
	std::map<SceneID, Scene*>::iterator it = mInactivesScenes.begin();
	while(it != mInactivesScenes.end())
	{
		m_app->log << "SceneManager::RemoveAllInactiveScene() Eliminada escena con ID=" 
			<< it->first << std::endl;
		it->second->Cleanup();
		delete it->second;
		mInactivesScenes.erase(it++);
	}
}

void SceneManager::RemoveAllScene()
{
	// Eliminamos todas las escenas inactivas
	RemoveAllInactiveScene();

	if (mActiveScene != NULL)
	{
		// Eliminamos la escena activa
		m_app->log << "SceneManager::RemoveAllScene() Eliminada escena con ID=" 
			<< mActiveScene->GetID() << std::endl;
		mActiveScene->Cleanup();
		delete mActiveScene;
		mActiveScene = NULL;
	}
}

void SceneManager::EventScene(sf::Event theEvent)
{
	mActiveScene->Event(theEvent);
}

void SceneManager::UpdateScene()
{
	mActiveScene->Update();
}

void SceneManager::DrawScene()
{
	mActiveScene->Draw();
}

void SceneManager::ResumeScene()
{
	mActiveScene->Resume();
}

void SceneManager::PauseScene()
{
	mActiveScene->Pause();
}

bool SceneManager::HandleChangeScene()
{
	if (mNextScene == "")
	{
		return false;
	}
	return true;
}

} // Namespace GGE