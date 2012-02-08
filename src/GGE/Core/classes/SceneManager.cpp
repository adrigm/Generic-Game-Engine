#include <GGE/Core/classes/SceneManager.hpp>


namespace GGE
{

SceneManager::SceneManager(App* theApp) :
	mApp(theApp),
	mActiveScene(NULL),
	mInactivesScenes(),
	mNextScene("")
{
}

SceneManager::~SceneManager()
{
	mApp->mLog << "SceneManager::~SceneManager() Destructor llamado" << std::endl;
}

void SceneManager::AddScene(IScene* theScene)
{
	for(std::map<SceneID, IScene*>::iterator it = mInactivesScenes.begin();
		it != mInactivesScenes.end(); ++it)
	{
		if(theScene->GetID() == it->first)
		{
			// Si ya existe la escena salimos
			mApp->mLog << "SceneManager::AddScene() ya existe una escena con ID=" 
				<< theScene->GetID() << std::endl; 
			return;
		}
	}

	// Si no existe la añadimos a la lista
	mInactivesScenes[theScene->GetID()] = theScene;

	// Inicializamos la escena si no lo esta
	if (!theScene->IsInitComplete())
	{
		theScene->Init();
	}

	mApp->mLog << "SceneManager::AddScene() Añadida escena con ID=" 
		<< theScene->GetID() << std::endl;
}

void SceneManager::SetActiveScene(SceneID theSceneID)
{
	for(std::map<SceneID, IScene*>::iterator it = mInactivesScenes.begin();
		it != mInactivesScenes.end(); ++it)
	{
		if(theSceneID == it->first)
		{
			mNextScene = theSceneID;
			return;
		}
	}

	if (theSceneID == mActiveScene->GetID())
	{
		mApp->mLog << "SceneManager::SetActiveScene() la escena con ID=" <<  mActiveScene->GetID()
			<< "ya esta activa" << std::endl;
		return;
	}

	mApp->mLog << "SceneManager::SetActiveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::ChangeScene(SceneID theSceneID)
{
	mNextScene = "";
	if (mActiveScene != NULL)
		mInactivesScenes[mActiveScene->GetID()] = mActiveScene;
	mActiveScene = mInactivesScenes[theSceneID];
	mInactivesScenes.erase(theSceneID);
	mApp->mLog << "SceneManager::ChangeScene() Activa escena con ID=" << theSceneID << std::endl;
}

void SceneManager::RemoveScene(SceneID theSceneID)
{
	// Buscamos en la lista de escenas inactivas
	for(std::map<SceneID, IScene*>::iterator it = mInactivesScenes.begin();
		it != mInactivesScenes.end(); ++it)
	{
		if(theSceneID == it->first)
		{
			mApp->mLog << "SceneManager::RemoveScene() Eliminada escena con ID=" 
				<< it->first << std::endl;
			it->second->Cleanup();
			delete it->second;
			mInactivesScenes.erase(it);
			return;
		}
	}

	if (theSceneID == mActiveScene->GetID())
	{
		mApp->mLog << "SceneManager::RemoveScene() la escena con ID=" << mActiveScene->GetID() 
			<< "esta activa y no se puede eliminar" << std::endl;
		return;
	}

	mApp->mLog << "SceneManager::RemoveScene() No existe ninguna escena con ID=" 
		<< theSceneID << std::endl;
}

void SceneManager::RemoveAllInactiveScene()
{
	// Recorremos la lista de escenas inactivas
	std::map<SceneID, IScene*>::iterator it = mInactivesScenes.begin();
	while(it != mInactivesScenes.end())
	{
		mApp->mLog << "SceneManager::RemoveAllInactiveScene() Eliminada escena con ID=" 
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

	// Eliminamos la escena activa
	mApp->mLog << "SceneManager::RemoveAllScene() Eliminada escena con ID=" 
		<< mActiveScene->GetID() << std::endl;
	mActiveScene->Cleanup();
	delete mActiveScene;
	mActiveScene = NULL;
}

void SceneManager::EventScene(sf::Event theEvent)
{
	mActiveScene->Events(theEvent);
}

void SceneManager::UpdateScene()
{
	mActiveScene->Update();
}

void SceneManager::DrawScene()
{
	mActiveScene->Draw();
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
