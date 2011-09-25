#include "scene_main.h"
#include <iostream>

SceneMain::SceneMain(BGE::SceneID id, BGE::App* m_app) :
	Scene(id, m_app)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	BGE::Scene::Init();
	app->scene_manager->RemoveScene("Start");
}

void SceneMain::ReInit()
{
}

void SceneMain::Events(sf::Event event)
{
	if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
	{
		app->scene_manager->SetActiveScene("Start");
	}
}

void SceneMain::Update()
{
	//std::cout << "Hola BGE!!!\n";
}

void SceneMain::Draw()
{
	app->window.Clear(sf::Color(255, 0, 0));
}

void SceneMain::Cleanup()
{
	BGE::Scene::Cleanup();
}