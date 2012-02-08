#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/classes/IScene.hpp>

class SceneMenu : public GGE::IScene
{
public:
	SceneMenu(GGE::SceneID theID, GGE::App* theApp);

	virtual ~SceneMenu();

	virtual void Init();

	virtual void ReInit();

	virtual void Events(sf::Event theEvent);

	virtual void Update();

	virtual void Draw();

	virtual void Cleanup();

private:
	sf::String text;
};

#endif // SCENE_MENU_HPP