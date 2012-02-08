#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GGE/Core.hpp>

class SceneMain : public GGE::IScene
{
public:
	SceneMain(GGE::SceneID theID, GGE::App* theApp);

	virtual ~SceneMain();

	virtual void Init();

	virtual void ReInit();

	virtual void Events(sf::Event theEvent);

	virtual void Update();

	virtual void Draw();

	virtual void Cleanup();

private:
	sf::Sprite hero;
	sf::String text;
	sf::String otext;
	sf::Sound sonido;
	sf::Music musica;
};

#endif // SCENE_MAIN_HPP