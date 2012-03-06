#include <GGE/Core/Scene.hpp>

namespace GGE
{

Scene::Scene(SceneID theID) :
	mApp(NULL),
	mID(theID),
	mInit(false),
	mPaused(false),
	mCleanup(false),
	mColorBack(0, 0, 0)
{
	mApp = GGE::App::Instance();
}

Scene::~Scene()
{
}

const SceneID Scene::GetID() const
{
	return mID;
}
	
const bool Scene::IsInitComplete() const
{
	return mInit;
}
	
const bool Scene::IsPaused() const
{
	return mPaused;
}
	

void Scene::Init()
{
	mApp->mLog << "Scene::Init(" << mID << ") llamado" << std::endl;

	if (!mInit)
	{
		mInit = true;
		mPaused = false;
	}
}

void Scene::ReInit()
{
	mApp->mLog << "Scene::ReInit(" << mID << ") llamado" << std::endl;
}

void Scene::Pause()
{
	mApp->mLog << "Scene::Pause(" << mID << ") llamado" << std::endl;

	mPaused = true;
}
	
void Scene::Resume()
{
	mApp->mLog << "Scene::Resume(" << mID << ") llamado" << std::endl;

	mPaused = false;
}

void Scene::HandleCleanup(void)
{
	if(mCleanup)
	{
		Cleanup();
		mCleanup = false;
	}
}
	

void Scene::Cleanup()
{
	mApp->mLog << "Scene::Cleanup(" << mID << ") llamado" << std::endl;
}

void Scene::Events(sf::Event TheEvent)
{
}
	
void Scene::Update(void)
{
}

void Scene::Draw(void)
{
	mApp->mWindow.Clear(mColorBack);

	std::vector<GGE::Actor*>::const_iterator element;
	for(element = mActors.begin(); element != mActors.end(); element++)
	{
		mApp->mWindow.Draw(**element);
	}
}

void Scene::AddActor(GGE::Actor* theActor)
{
	// Comprobamos que el Actor no esté añadido ya a la escena
	std::vector<GGE::Actor*>::iterator element;
	element = std::find(mActors.begin(), mActors.end(), theActor);
	if (element == mActors.end())
	{
		mActors.push_back(theActor);
	}
}

void Scene::SetBackgroundColor(sf::Color theColor)
{
	mColorBack = theColor;
}

} // Namespace GGE
