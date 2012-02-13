#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID, GGE::App* theApp) :
	GGE::IScene(theID, theApp),
	hero(theApp),
	map(theApp)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	mApp->mSceneManager->AddScene(new SceneMenu("Menu", mApp));
	mApp->mAssetManager->AddDirectory("resources/");
	map.Load(mApp->mAssetManager->GetTmxMap("pueblo.tmx"));
	hero.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	mApp->mAssetManager->GetImage("sprite.png").SetSmooth(false);
	rejilla.SetImage(mApp->mAssetManager->GetImage("rejilla.png"));
	hero.SetGrid(4, 4);
	frame = 1;
	time = 0;
	hero.SetCenter(hero.GetWidth()/2, hero.GetHeight());
	hero.Move(432, 416);
	map.SetScrollParallax(hero);
	//std::cout << &mApp->mAssetManager->GetTmxMap("mapa2.tmx") << std::endl;
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
	//std::cout << hero.GetPosition().x << std::endl;
	map.Update();
	hero.Update();
}

void SceneMain::Draw()
{
	mApp->mWindow.Clear(sf::Color(200, 200, 200));
	map.Draw();
	//mApp->mWindow.Draw(rejilla);
	mApp->mWindow.Draw(hero);
	std::cout << 1.0f / mApp->GetUpdateTime() << std::endl;
}

void SceneMain::Cleanup()
{
}