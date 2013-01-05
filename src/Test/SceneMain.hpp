#ifndef SCENE_MAIN
#define SCENE_MAIN

#include <GGE/Core.hpp>

class SceneMain : public GGE::Scene
{
public:
	SceneMain(GGE::SceneID theID);
	~SceneMain();

	void Init();

	void Update();

	void Event(sf::Event theEvent);

	void Resume();

	void Pause();

	void Cleanup();

	void Draw();

private:
	sf::Sprite sprite;
	sf::Sound sound;
	sf::Music* music;
	sf::Text text;
	GGE::Tmx::Map* map;
	GGE::ConfigReader* conf;

}; // class SceneMain

#endif // SCENE_MAIN