#ifndef SCENESTART_H
#define SCENESTART_H

#include <SFML/Graphics.hpp>

#include "BGE/BGE.h"
#include "scene_main.h"

class SceneStart : public BGE::Scene
{

public:
	SceneStart(BGE::SceneID id, BGE	::App* m_app);
	virtual ~SceneStart();

	virtual void Init(void);
	virtual void ReInit(void);
	virtual void Events(sf::Event theEvent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Cleanup(void);
	
private:
	bool vis;
	int contador;
	sf::String text;
};

#endif // SCENESTART_H
