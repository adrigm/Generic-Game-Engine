#ifndef SCENE_MAP
#define SCENE_MAP

#include <GGE/Core.hpp>

class SceneMap : public GGE::Scene
{
public:
	SceneMap(GGE::SceneID theID);
	~SceneMap();

	void Init();

	void Update();

	void Event(sf::Event theEvent);

	void Resume();

	void Pause();

	void Cleanup();

}; // class SceneMap

#endif // SCENE_MAP