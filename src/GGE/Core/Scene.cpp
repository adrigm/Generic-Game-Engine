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
	bool operator()(const GGE::ObjectScene* o1, const GGE::ObjectScene* o2) const
    {
		return o1->GetZOrder() < o2->GetZOrder();
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
	std::list<GGE::ObjectScene*>::const_iterator element;
	for(element = mObjects.begin(); element != mObjects.end(); element++)
	{
		GGE::ObjectScene* object = *element;
		
		if (object->IsVisible() && mApp->mCamera->GetRect().intersects(object->getGlobalBounds()))
		{
			mApp->mWindow.draw(*object);
		}
	}
}

void Scene::AddObject(GGE::ObjectScene* theObject)
{
	// FIX: Optimizar - No ordenar lista dos veces
	// Añadimos un nuevo Actor a la escena
	mObjects.push_back(theObject);
	// Ordenamos los elementos de la escena
	mObjects.sort();
	// Eliminamos los elementos repetidos
	mObjects.unique();
	// Ordenamos en base a su Z
	mObjects.sort(ActorComparator());
}

void Scene::AddObjects(const std::vector<GGE::ObjectScene*> &theList)
{
	std::vector<GGE::ObjectScene*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		AddObject(*it);
	}
}

void Scene::QuitObject(GGE::ObjectScene* theActor)
{
	mObjects.remove(theActor);
}

void Scene::QuitObjects(const std::vector<GGE::ObjectScene*> &theList)
{
	std::vector<GGE::ObjectScene*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		QuitObject(*it);
	}
}


void Scene::DeleteObject(GGE::ObjectScene* theObject)
{
	mObjects.remove(theObject);
	delete theObject;
}

void Scene::DeleteObjects(const std::vector<GGE::ObjectScene*> &theList)
{
	std::vector<GGE::ObjectScene*>::const_iterator it;
	for (it = theList.begin(); it != theList.end(); it++)
	{
		DeleteObject(*it);
	}
}

void Scene::SetBackgroundColor(const sf::Color &theColor)
{
	mColorBack = theColor;
}

} // Namespace GGE
