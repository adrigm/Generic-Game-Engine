#include <algorithm>
#include <list>
#include <GGE/Core/App.hpp>
#include <GGE/Core/Camera.hpp>
#include <GGE/Core/Scene.hpp>
#include <GGE/Core/Actor.hpp>
#include <iostream> // Quitar

namespace GGE
{

struct ActorComparator
{
	bool operator()(const GGE::Actor* o1, const GGE::Actor* o2) const
    {
		return o1->mZOrder < o2->mZOrder;
    }
};

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

		if (actor->IsVisible() && mApp->mCamera->GetRect().intersects(actor->getGlobalBounds()))
		{
			mApp->mWindow.draw(*actor);
		}
	}
}

void Scene::AddActor(GGE::Actor* theActor)
{
	// FIX: Optimizar - No ordenar lista dos veces
	// Añadimos un nuevo Actor a la escena
	mActors.push_back(theActor);
	// Ordenamos los elementos de la escena
	mActors.sort();
	// Eliminamos los elementos repetidos
	mActors.unique();
	// Ordenamos en base a su Z
	mActors.sort(ActorComparator());
}

void Scene::AddActors(const std::vector<GGE::Actor*> &theList)
{
	std::vector<GGE::Actor*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		AddActor(*it);
	}
}

void Scene::QuitActor(GGE::Actor* theActor)
{
	mActors.remove(theActor);
}

void Scene::QuitActors(const std::vector<GGE::Actor*> &theList)
{
	std::vector<GGE::Actor*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		QuitActor(*it);
	}
}


void Scene::DeleteActor(GGE::Actor* theActor)
{
	mActors.remove(theActor);
	delete theActor;
}

void Scene::DeleteActors(const std::vector<GGE::Actor*> &theList)
{
	std::vector<GGE::Actor*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		DeleteActor(*it);
	}
}

void Scene::SetBackgroundColor(const sf::Color &theColor)
{
	mColorBack = theColor;
}

} // Namespace GGE
