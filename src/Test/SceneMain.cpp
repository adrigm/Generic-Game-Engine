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
	GGE::App* APP = GGE::App::Instance();
	GGE::SceneManager* SM = GGE::SceneManager::Instance();
	GGE::AssetManager* AM = GGE::AssetManager::Instance();


	this->SetBackgroundColor(sf::Color(200, 220, 255));
	
	AM->AddDirectory("Data/");

	this->heroe = new Hero();
	this->heroe->setTexture(*AM->GetTexture("indiana.png"));
	this->heroe->SetFramesBySize(64, 64);
	this->AddObject(heroe);

	GGE::ConfigReader* anim_file = AM->GetConfig("inidiana_animations.cfg");
	GGE::Animation Run_left;
	Run_left.fps = anim_file->GetUint32("run_left", "fps", 20);
	Run_left.firstFrame = anim_file->GetUint32("run_left", "firstFrame", 1);
	Run_left.lastFrame = anim_file->GetUint32("run_left", "lastFrame", 1);
	std::vector<std::string> names = anim_file->GetAllNameSections();
	std::cout << names[0] << std::endl;


	heroe->AddAnimation("run", Run_left);
	heroe->SetActiveAnimation("run");
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