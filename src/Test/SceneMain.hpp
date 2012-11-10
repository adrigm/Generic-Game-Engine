#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <GGE/Core.hpp>
#include "Hero.hpp"

class SceneMain : public GGE::Scene
{
public:
	SceneMain(GGE::SceneID theID);

	virtual ~SceneMain();

	virtual void Init();

	virtual void ReInit();

	virtual void Events(sf::Event theEvent);

	virtual void Update();

	virtual void Cleanup();

private:
	GGE::App* app;
	sf::Texture* tex;
	Hero* heroe;
};

#endif // SCENE_MAIN_HPP
