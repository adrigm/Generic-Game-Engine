#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID, GGE::App* theApp) :
	GGE::IScene(theID, theApp)
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
	sf::Image a = mApp->mAssetManager->GetImage("sprite.png");
	GGE::ConfigReader conf;
	conf = mApp->mAssetManager->GetConfigFile("swindow.cfg");
	std::cout << conf.GetUint32("window", "width", 0) << std::endl;
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
	/*if (mApp->mInput.IsKeyDown(sf::Key::Space))
	{
		mApp->mSceneManager->SetActiveScene("Menu");
	}*/
}

void SceneMain::Draw()
{
	mApp->mWindow.Clear(sf::Color(180, 200, 255));
	mApp->mWindow.Draw(hero);
}

void SceneMain::Cleanup()
{
}