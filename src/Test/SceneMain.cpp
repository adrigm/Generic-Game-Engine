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
	control = 0;

	GGE::AssetManager *sm = GGE::AssetManager::Instance();

	std::cout << sm->AddDirectory("Data") << std::endl;
	std::cout << sm->AddDirectory("Data/españaíuÜán") << std::endl;
	std::cout << sm->AddDirectory("Data/") << std::endl;
	std::cout << sm->AddDirectory("Data/otro") << std::endl;
	std::cout << sm->AddDirectory(".") << std::endl;
	std::cout << sm->AddDirectory("../bin/Data") << std::endl;
	std::cout << sm->AddDirectory("..\\lib") << std::endl;
	std::cout << sm->AddDirectory("../../engine") << std::endl;
	std::cout << sm->AddDirectory("C:\\Users\\Adrian\\Documents\\Proyectos\\Generic-Game-Engine\\bin\\Data") << std::endl;

	sm->RemoveDirectory("Data");
	sm->RemoveDirectory("../bin/Data");
	sm->RemoveDirectory("../bin/Data/otro");
}

void SceneMain::Update()
{

	/*control += m_app->GetUpdateTime().asMilliseconds();

	if (control >= 100)
	{
		std::cout << static_cast<float>(m_app->GetTotalTime().asMilliseconds() / 1000.0f) << std::endl;
		control = 0;
	}*/

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