#include "scene_start.h"
#include <iostream>
#include <sstream>

SceneStart::SceneStart(BGE::SceneID id, BGE::App* m_app) :
	Scene(id, m_app)
{
}

SceneStart::~SceneStart()
{
}

void SceneStart::Init()
{
	BGE::Scene::Init();
	vis = false;
	contador = 0;
	text.SetText("0");
	text.SetPosition(640/2, 480/2);
	BGE::Scene* main = new SceneMain("Main", app);
	app->scene_manager->AddScene(main);
}

void SceneStart::ReInit()
{
}

void SceneStart::Events(sf::Event event)
{
	if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Tab)
	{
		if (!vis)
		{
			app->stat_manager.SetShow(true);
			vis = true;
		}
		else
		{
			app->stat_manager.SetShow(false);
			vis = false;
		}
	}

	if (event.Type == sf::Event::MouseButtonPressed)
	{
		if (event.MouseButton.Button == sf::Mouse::Left)
			contador += 10;
		if (event.MouseButton.Button == sf::Mouse::Right)
			contador -= 10;
			
		std::ostringstream stream;
		stream << contador;
		text.SetText(stream.str());
	}
	
	if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
	{
		app->scene_manager->SetActiveScene("Main");
	}
}

void SceneStart::Update()
{
	/*
	if (app->input.IsMouseButtonDown(sf::Mouse::Left))
	{
		contador++;
		std::ostringstream stream;
		stream << contador;
		text.SetText(stream.str());
	}*/
}

void SceneStart::Draw()
{
	app->window.Clear(sf::Color(150, 150, 150));
	app->window.Draw(text);
}

void SceneStart::Cleanup()
{
	BGE::Scene::Cleanup();
}
