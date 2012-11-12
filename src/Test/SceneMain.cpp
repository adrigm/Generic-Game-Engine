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

	heroe->setOrigin(heroe->getLocalBounds().width/2, heroe->getLocalBounds().height/2);
	heroe->SetTopPosition(0);
	heroe->SetLeftPosition(0);
	heroe->FlipX(true);
	
	/*std::cout << heroe->getGlobalBounds().left << std::endl;
	std::cout << heroe->getGlobalBounds().top << std::endl;
	std::cout << heroe->getGlobalBounds().width << std::endl;
	std::cout << heroe->getGlobalBounds().height << std::endl;

	std::cout << heroe->GetBottomPosition() << std::endl;*/

	heroe->AddAnimation("walk", Walk_left);
	heroe->SetActiveAnimation("walk");

	GGE::RectCollision rect(25, 25, 50, 50);

	r = new sf::RectangleShape();
	r->setPosition(rect.left, rect.top);
	r->setSize(sf::Vector2f(rect.width, rect.height));
	r->setFillColor(sf::Color(0, 0, 0, 0));
	r->setOutlineColor(sf::Color(255, 0, 255));
	r->setOutlineThickness(1.0f);
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
	mApp->mWindow.draw(*r);
}

void SceneMain::Cleanup()
{
}