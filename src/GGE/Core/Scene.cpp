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
	mMap(NULL),
	mShowCollision(false)
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
	std::list<GGE::Actor*>::const_iterator element;
	for(element = mActors.begin(); element != mActors.end(); element++)
	{
		GGE::Actor& actor = **element;

		if (actor.IsVisible())
		{
			// Obtenemos un Rect con las posiciones del Actor
			sf::FloatRect pos;
			pos.Top = actor.GetPosition().y - actor.GetCenter().y;
			pos.Bottom = actor.GetPosition().y + actor.GetHeight() - actor.GetCenter().y;
			pos.Left = actor.GetPosition().x - actor.GetCenter().x;
			pos.Right = actor.GetPosition().x + actor.GetWidth() - actor.GetCenter().x;

		
			// Obtenemos el Rect de la camara
			sf::FloatRect camera = mApp->mCamera->mView.GetRect();

			// Dibujamos solo los Actores que estén dentro de la cámara
			if (pos.Top <= camera.Bottom && pos.Bottom >= camera.Top)
				if (pos.Left <= camera.Right && pos.Right >= camera.Left)
				{
					mApp->mWindow.Draw(actor);
					// Comprobamos si debemos dibujar las colisiones
					if (mShowCollision)
					{
						sf::Shape rect = sf::Shape::Rectangle(actor.GetRectCollision().Left,
							actor.GetRectCollision().Top, actor.GetRectCollision().Right,
							actor.GetRectCollision().Bottom, sf::Color(0,0,0,0), -1.0f,
							sf::Color(0,255,0));
						mApp->mWindow.Draw(rect);
					}
				}
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

void Scene::AddMap(GGE::Map* theMap)
{
	mMap = theMap;
}

void Scene::QuitMap()
{
	mMap = NULL;
}

bool Scene::IsVisibleCollision() const
{
	return mShowCollision;
}

void Scene::VisibleCollision(bool visibility)
{
	mShowCollision = visibility;
}

} // Namespace GGE
