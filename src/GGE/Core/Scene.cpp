#include <GGE/Core/App.hpp>
#include <GGE/Core/Camera.hpp>
#include <GGE/Core/Scene.hpp>
#include <GGE/Core/Actor.hpp>
#include <iostream> // Quitar

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
	// Establecemos el color de fondo
	mApp->mWindow.clear(mColorBack);

	// Recorremos la lista de Actores de la escena para dibujarla
	std::list<GGE::Actor*>::const_iterator element;
	for(element = mActors.begin(); element != mActors.end(); element++)
	{
		GGE::Actor* actor = *element;

		if (actor->IsVisible())
		{
			//mApp->mCamera->mView.getViewport().left;

			// Obtenemos un rect de la posición del actor
			sf::IntRect rect;
			rect.left = actor->getPosition().x - actor->getOrigin().x;
			rect.top = actor->getPosition().y - actor->getOrigin().y;
			rect.width = actor->getTextureRect().width;
			rect.height = actor->getTextureRect().height;

			mApp->mWindow.draw(*actor);
		}
	}
}

void Scene::AddActor(GGE::Actor* theActor)
{
	if (mActors.empty())
	{
		mActors.push_back(theActor);
		return;
	}

	std::list<GGE::Actor*>::iterator it;
	for (it = mActors.begin(); it != mActors.end(); it++)
	{
		if (theActor->mZOrder < (*it)->mZOrder)
		{
			mActors.insert(it, theActor);
			mActors.unique();
			return;
		}
	}
	mActors.push_back(theActor);
	mActors.unique();
}

void Scene::AddActors(std::vector<GGE::Actor*> theList)
{
	for (int i = 0; i < theList.size(); i++)
	{
		AddActor(theList[i]);
	}
}

void Scene::QuitActor(GGE::Actor* theActor)
{
	mActors.remove(theActor);
}

void Scene::QuitActors(std::vector<GGE::Actor*> theList)
{
	for (int i = 0; i < theList.size(); i++)
	{
		QuitActor(theList[i]);
	}
}


void Scene::DeleteActor(GGE::Actor* theActor)
{
	mActors.remove(theActor);
	delete theActor;
}

void Scene::DeleteActors(std::vector<GGE::Actor*> theList)
{
	for (int i = 0; i < theList.size(); i++)
	{
		DeleteActor(theList[i]);
	}
}

void Scene::SetBackgroundColor(sf::Color theColor)
{
	mColorBack = theColor;
}

} // Namespace GGE
