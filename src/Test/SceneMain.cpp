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
	//GGE::App* APP = GGE::App::Instance();
	//GGE::SceneManager* SM = GGE::SceneManager::Instance();
	GGE::AssetManager* AM = GGE::AssetManager::Instance();

	this->SetBackgroundColor(sf::Color(200, 220, 255));
	
	AM->AddDirectory("Data/");

	this->heroe = new Hero();
	this->heroe->setTexture(*AM->GetTexture("indiana.png"));
	this->heroe->SetFramesBySize(64, 64);
	this->AddObject(heroe);

	heroe->LoadAnimationsFromConfig(AM->GetConfig("inidiana_animations.cfg"));
	heroe->SetActiveAnimation("run_right");
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
	//heroe->Update();
	heroe->Animate();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mApp->mCamera->move(-5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mApp->mCamera->move(5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mApp->mCamera->move(0, -5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mApp->mCamera->move(0, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		heroe->Show();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		heroe->Hide();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		heroe->FlipX(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		heroe->FlipX(false);
	}
}

void SceneMain::Cleanup()
{
}