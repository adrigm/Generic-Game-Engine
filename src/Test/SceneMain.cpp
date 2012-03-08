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
	GGE::TmxMap& tmx = mApp->mAssetManager->GetTmxMap("plat.tmx");
	joya = new GGE::Actor();
	joya->SetImage(mApp->mAssetManager->GetImage("tileset_platformer.png"));
	joya->AddRects(sf::IntRect(120, 64, 160, 96));
	joya->SelectRect(0);
	joya->SetPosition(200, 200);
	this->AddActor(joya);
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
	}
}

void SceneMain::Update()
{
	hero.Update();
}

void SceneMain::Cleanup()
{
	delete joya;
}
