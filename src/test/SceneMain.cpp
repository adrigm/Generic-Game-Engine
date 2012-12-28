#include <SFML/Graphics.hpp>
#include "SceneMain.hpp"
#include "SceneMap.hpp"
#include <iostream>

SceneMain::SceneMain(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	this->SetBackgroundColor(sf::Color(180, 200, 255));
	t = m_app->GetTitle();

	m_app->sceneManager->AddScene(new SceneMap("Map"));
	time = 0U;
	control = 0;
}

void SceneMain::Update()
{

	time += m_app->GetUpdateTime().asMilliseconds();
	control += m_app->GetUpdateTime().asMilliseconds();

	if (control >= 1000)
	{
		std::cout << time / 1000 << std::endl;
		control = 0;
	}
	/*std::string fps = GGE::ConvertFloat(1000.0f /m_app->GetUpdateTime());
	std::string title = t + "FPS: " + fps;
	m_app->SetTitle(title);*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Pulsando A" << std::endl;
	}
}

void SceneMain::Event(sf::Event theEvent)
{
	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::Space)
	{
	}
}

void SceneMain::Resume()
{
}

void SceneMain::Pause()
{
	std::cout << "Pausa" << std::endl;
	m_app->sceneManager->SetActiveScene("Map");
}

void SceneMain::Cleanup()
{
}