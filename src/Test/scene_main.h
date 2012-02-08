#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include <SFML/Graphics.hpp>

#include <GGE/Core.hpp>
#include "scene_start.h"

class SceneMain : public GGE::Scene
{

public:
	SceneMain(GGE::SceneID id, GGE::App* m_app);
	virtual ~SceneMain();

	virtual void Init(void);
	virtual void Events(sf::Event theEvent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Cleanup(void);

};

#endif // SCENEMAIN_H
