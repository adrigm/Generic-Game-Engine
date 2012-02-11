#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID, GGE::App* theApp) :
	GGE::IScene(theID, theApp),
	hero(theApp)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	mApp->mSceneManager->AddScene(new SceneMenu("Menu", mApp));
	mApp->mAssetManager->AddDirectory("resources/");
	hero.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	hero.SetGrid(4, 4);
	frame = 1;
	time = 0;
	//hero.SetCenter(hero.GetWidth()/2, hero.GetHeight());
}

void SceneMain::ReInit()
{
}

void SceneMain::Events(sf::Event theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed)
	{
		if (theEvent.Key.Code == sf::Key::Space)
			mApp->mSceneManager->SetActiveScene("Menu");

		if (theEvent.Key.Code == sf::Key::Escape)
			mApp->Quit(GGE::StatusAppOK);
	}
}

void SceneMain::Update()
{
	hero.Update();
	std::cout << hero.GetPosition().x << std::endl;
}

void SceneMain::Draw()
{
	mApp->mWindow.Clear(sf::Color(200, 200, 200));
	mApp->mWindow.Draw(hero);
}

void SceneMain::Cleanup()
{
}