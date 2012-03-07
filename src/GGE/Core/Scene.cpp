#include <GGE/Core/Scene.hpp>
#include <iostream> // Quitar

namespace GGE
{

Scene::Scene(SceneID theID) :
	mApp(NULL),
	mID(theID),
	mInit(false),
	mPaused(false),
	mCleanup(false),
	mColorBack(0, 0, 0),
	mMap(NULL)
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
	mApp->mWindow.Clear(mColorBack);
	
	if (mMap != NULL)
	{
		mMap->Draw();
	}

	// Recorremos la lista de Actores de la escena para dibujarla
	std::vector<GGE::Actor*>::const_iterator element;
	for(element = mActors.begin(); element != mActors.end(); element++)
	{
		GGE::Actor& actor = **element;

		if (actor.IsVisible())
		{
			// Obtenemos un rect con las posiciones del Actor
			sf::FloatRect pos;
			pos.Top = actor.GetPosition().y - actor.GetCenter().y;
			pos.Bottom = actor.GetPosition().y + actor.GetHeight() - actor.GetCenter().y;
			pos.Left = actor.GetPosition().x - actor.GetCenter().x;
			pos.Right = actor.GetPosition().x + actor.GetWidth() - actor.GetCenter().x;
		
			// Obtenemos el rect de la camara
			sf::FloatRect camera = mApp->mCamera->mView.GetRect();

			// Dibujamos solo los Actores que estén dentro de la cámara
			if (pos.Top <= camera.Bottom && pos.Bottom >= camera.Top)
				if (pos.Left <= camera.Right && pos.Right >= camera.Left)
					mApp->mWindow.Draw(actor);
		}
	}
}

void Scene::AddActor(GGE::Actor* theActor)
{
	// Comprobamos que el Actor no esté añadido ya a la escena
	std::vector<GGE::Actor*>::iterator element;
	element = std::find(mActors.begin(), mActors.end(), theActor);
	if (element == mActors.end())
		mActors.push_back(theActor);
}

void Scene::SetBackgroundColor(sf::Color theColor)
{
	mColorBack = theColor;
}

void Scene::AddMap(GGE::Map* theMap)
{
	mMap = theMap;
}

} // Namespace GGE
