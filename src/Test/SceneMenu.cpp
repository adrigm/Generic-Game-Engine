#include <iostream>
#include "SceneMenu.hpp"

SceneMenu::SceneMenu(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Init()
{
	app = GGE::App::Instance();
	this->SetBackgroundColor(sf::Color(255, 215, 50));
	std::cout << "Scene Menu" << std::endl;
}

void SceneMenu::ReInit()
{
}

void SceneMenu::Events(sf::Event theEvent)
{
}

void SceneMenu::Update()
{
}

void SceneMenu::Cleanup()
{
}
