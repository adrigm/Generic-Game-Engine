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
	mApp->mAssetManager->AddDirectory("resources/");
	hero.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	hero.SetGrid(4, 4);
	hero.SetCenter(hero.GetWidth()/2, hero.GetHeight());
	hero.SetPosition(160, 320);
	mapa.Load(mApp->mAssetManager->GetTmxMap("plat.tmx"));
	mApp->mCamera->ConnectToSprite(hero);
	mApp->mCamera->LockToMap(mapa);
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

void SceneMain::Draw()
{
	mApp->mWindow.Clear(sf::Color(200, 200, 200));

	mapa.Draw();

	mApp->mWindow.Draw(hero);
}

void SceneMain::Cleanup()
{
}
