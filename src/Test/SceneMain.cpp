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
	app = GGE::App::Instance();
	this->SetBackgroundColor(sf::Color(200, 220, 255));
	mApp->mAssetManager->AddDirectory("Data/");
	tex = mApp->mAssetManager->GetTexture("indiana.png");
	heroe = new Hero();
	heroe->setTexture(*tex);
	this->AddActor(heroe);

	heroe->SetFramesByNum(4, 12);
	heroe->SelectFrame(1);

	GGE::Animation Walk_left;
	Walk_left.fps = 24;
	Walk_left.firstFrame = 2;
	Walk_left.lastFrame = 11;

	heroe->AddAnimation("walk", Walk_left);
	heroe->SetActiveAnimation("walk");
}

void SceneMain::ReInit()
{
}

void SceneMain::Events(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
	}
}

void SceneMain::Update()
{
	heroe->Update();
}

void SceneMain::Cleanup()
{
}
