#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	GGE::AssetManager* AM;
	Hero hero;
	GGE::Map mapa;
	std::vector<GGE::Actor*> joyas;
	std::vector<GGE::Actor*> plat;
	sf::Shape cir;
	GGE::Actor suelo;
};

#endif // SCENE_MAIN_HPP
