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

private:
	std::string t;
	GGE::Int32 control;
	GGE::Tmx::Map map;

}; // class SceneMain

#endif // SCENE_MAIN