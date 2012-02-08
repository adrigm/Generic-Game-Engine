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
	GGE::ConfigReader conf = mApp->mAssetManager->GetConfigFile("window.cfg");
	std::cout << conf.GetUint32("window", "width", 0) << std::endl;
	mApp->mAssetManager->DeleteConfigFile("window.cfg");
	text.SetFont(mApp->mAssetManager->GetFont("segoeui.ttf"));
	text.SetText("Generic Game Engine");
	text.SetColor(sf::Color(255, 0, 0));
	text.SetSize(40);
	otext.SetFont(mApp->mAssetManager->GetFont("segoeui.ttf"));
	otext.SetText("Hola Mundo");
	otext.SetColor(sf::Color(0, 0, 0));
	otext.SetPosition(400, 400);
	buffersonido.LoadFromFile(mApp->GetExecutableDir() + "resources/sonido.ogg");
	sonido.SetBuffer(buffersonido);
	musica.OpenFromFile(mApp->GetExecutableDir() + "resources/musica.ogg");
	musica.SetLoop(true);
	musica.Play();
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
	if (mApp->mInput.IsKeyDown(sf::Key::Add))
	{
		otext.SetSize(10);
	}
	if (mApp->mInput.IsKeyDown(sf::Key::A))
	{
		sonido.Play();
	}
}

void SceneMain::Draw()
{
	mApp->mWindow.Clear(sf::Color(180, 200, 255));
	mApp->mWindow.Draw(hero);
	mApp->mWindow.Draw(text);
	mApp->mWindow.Draw(otext);
}

void SceneMain::Cleanup()
{
}