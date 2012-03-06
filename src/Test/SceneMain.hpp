#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

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

	virtual void Draw();

	virtual void Cleanup();

private:
	Hero hero;
	GGE::Map mapa;
};

#endif // SCENE_MAIN_HPP
