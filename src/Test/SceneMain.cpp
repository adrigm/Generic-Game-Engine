#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	AM = GGE::AssetManager::Instance();
	mApp->mAssetManager->AddDirectory("Data/");
	hero.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	hero.SetGrid(4, 4);
	hero.SetCenter(hero.GetWidth()/2, hero.GetHeight());
	hero.SetPosition(160, 320);
	mapa.Load(mApp->mAssetManager->GetTmxMap("plat.tmx"));
	mApp->mCamera->ConnectToSprite(hero);
	mApp->mCamera->LockToMap(mapa);
	this->AddActor(&hero);
	this->SetBackgroundColor(sf::Color(200, 200, 200));
	this->AddMap(&mapa);

	joyas = mapa.LayerToActors("diamantes");
	this->AddActors(joyas);

	//std::vector<GGE::Actor*> plat = mapa.LayerToActors("Tile Layer 1");
	//this->AddActors(plat);
	
	suelo.SetImage(AM->GetImage("blank.png"));
	suelo.SetPosition(0, 416);
	suelo.AddRects(sf::IntRect(0, 416, 1600, 480));
	suelo.SelectRect(0);
	//std::cout << suelo.GetRectCollision().Left << ", " << suelo.GetRectCollision().Right << std::endl;
	this->AddActor(&suelo);
	//this->DeleteActor(&hero);
}

void SceneMain::ReInit()
{
}

void SceneMain::Events(sf::Event theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed)
	{
		if (theEvent.Key.Code == sf::Key::Escape)
			mApp->Quit(GGE::StatusAppOK);
		if (theEvent.Key.Code == sf::Key::Space)
			this->QuitActor(&hero);
	}
}

void SceneMain::Update()
{
	hero.Update();
}

void SceneMain::Cleanup()
{
}
