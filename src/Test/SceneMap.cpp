#include "SceneMap.hpp"
#include "SceneMain.hpp"
#include <iostream>

SceneMap::SceneMap(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

SceneMap::~SceneMap()
{
}

void SceneMap::Init()
{
	this->SetBackgroundColor(sf::Color(255, 210, 152));
	//std::cout << "Soy Map!" << std::endl;
}

void SceneMap::Update()
{
}

void SceneMap::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
	}
}

void SceneMap::Resume()
{
	std::cout << "Continua" << std::endl;
	m_app->sceneManager->SetActiveScene("Main");
}

void SceneMap::Pause()
{
}

void SceneMap::Cleanup()
{
}