#ifndef SCENESTART_H
#define SCENESTART_H

#include <SFML/Graphics.hpp>

#include <GGE/Core.hpp>
#include "scene_main.h"

class SceneStart : public GGE::Scene
{

public:
	SceneStart(GGE::SceneID id, GGE	::App* m_app);
	virtual ~SceneStart();

	virtual void Init(void);
	virtual void Events(sf::Event theEvent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Cleanup(void);
	
private:
	bool vis;
	int contador;
	sf::String text;
};

#endif // SceneStart_H
