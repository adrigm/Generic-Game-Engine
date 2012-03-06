#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/Scene.hpp>

class SceneMenu : public GGE::Scene
{
public:
	SceneMenu(GGE::SceneID theID);

	virtual ~SceneMenu();

	virtual void Init();

	virtual void ReInit();

	virtual void Events(sf::Event theEvent);

	virtual void Update();

	virtual void Draw();

	virtual void Cleanup();
};

#endif // SCENE_MENU_HPP
