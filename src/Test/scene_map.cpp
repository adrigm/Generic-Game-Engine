#include "scene_map.h"
#include <GGE/Core/assets/ImageAsset.hpp>
#include <iostream>

SceneMap::SceneMap(GGE::SceneID id, GGE::App* m_app) :
	Scene(id, m_app)
{
}

SceneMap::~SceneMap()
{
}

void SceneMap::Init()
{
	GGE::Scene::Init();

	img_hero = app->asset_manager->AddImage("hero", app->GetExecutableDir()+"resources/sprite.png", GGE::AssetLoadStyleImmediate);
	sp_hero.SetImage(img_hero->GetAsset());
	sp_hero.SetPosition(200, 200);
	otro.SetImage(img_hero->GetAsset());
	otro.SetPosition(200, 200);
	otro.Scale(2.0f, 2.0f);
	sp_hero.SetCenter(sp_hero.GetSize().x/2, sp_hero.GetSize().y/2);


	int fil = 4;
	int col = 4;
	int width = sp_hero.GetSize().x / col;
	int height = sp_hero.GetSize().y / fil;

	for (int f = 0; f < fil; f++)
	{
		std::vector<sf::IntRect> fil;
		for (int c = 0; c < col; c++)
		{
			fil.push_back(sf::IntRect(c*width, f*height, c*width+width, f*height+height));
		}
		frames.push_back(fil);
	}

	sp_hero.SetSubRect(frames[0][0]);
}

void SceneMap::Events(sf::Event event)
{
}

void SceneMap::Update()
{
	// Get elapsed time
	float ElapsedTime = app->GetUpdateTime();
	if (app->input.IsKeyDown(sf::Key::Left)) sp_hero.Move(-100*ElapsedTime, 0);
	if (app->input.IsKeyDown(sf::Key::Right)) sp_hero.Move(100*ElapsedTime, 0);
	if (app->input.IsKeyDown(sf::Key::Up)) sp_hero.Move(0, -100*ElapsedTime);
	if (app->input.IsKeyDown(sf::Key::Down)) sp_hero.Move(0, 100*ElapsedTime);
	if (app->input.IsMouseButtonDown(sf::Mouse::Left)) sp_hero.Rotate(100*ElapsedTime);
	if (app->input.IsMouseButtonDown(sf::Mouse::Right)) sp_hero.Rotate(-100*ElapsedTime);

	if (otro.GetScale().x >= 0.0f && app->input.IsKeyDown(sf::Key::O))
	{
		otro.SetScale(otro.GetScale().x-0.1f, otro.GetScale().y-0.1f);
	}
	if (otro.GetScale().x >= 0.0f && app->input.IsKeyDown(sf::Key::P))
	{
		otro.SetScale(otro.GetScale().x+0.1f, otro.GetScale().y+0.1f);
	}
}

void        
SceneMap::Draw()
{
	app->window.Clear(sf::Color(200, 220, 255));
	app->window.Draw(sp_hero);
	app->window.Draw(otro);
}

void SceneMap::Cleanup()
{
	GGE::Scene::Cleanup();
}
