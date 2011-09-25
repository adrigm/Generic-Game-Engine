#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include <SFML/Graphics.hpp>

#include "BGE/BGE.h"
#include "scene_start.h"

class SceneMain : public BGE::Scene
{

public:
	SceneMain(BGE::SceneID id, BGE::App* m_app);
	virtual ~SceneMain();

	virtual void Init(void);
	virtual void ReInit(void);
	virtual void Events(sf::Event theEvent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Cleanup(void);

};

#endif // SCENEMAIN_H
