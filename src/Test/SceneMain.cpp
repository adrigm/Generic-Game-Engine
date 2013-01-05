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
	GGE::AssetManager* am = GGE::AssetManager::Instance();

	am->SetPath("Data");

	sprite.setTexture(*am->GetTexture("sprite.png"));
	sound.setBuffer(*am->GetSoundBuffer("sonido.ogg"));
	text.setFont(*am->GetFont("segoeui.ttf"));
	text.setString("Hola GGE");
	text.setPosition(200, 200);
	text.setColor(sf::Color(255,0,0));

	map = am->GetTmxMap("example.tmx");
	std::cout << map->GetHeight() << std::endl;

	conf = am->GetConfigFile("../window.cfg");
	std::cout << conf->GetUint32("window", "width", 666) << std::endl;

	music = am->GetMusic("musica.ogg");
	music->play();
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
		sound.play();
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

void SceneMain::Draw()
{
	m_app->window.clear(sf::Color(200, 200, 200));

	m_app->window.draw(sprite);
	m_app->window.draw(text);
}