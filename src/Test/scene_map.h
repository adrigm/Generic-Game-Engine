#ifndef SCENEMAP_H
#define SCENEMAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <GGE/Core.hpp>

class SceneMap : public GGE::Scene
{

public:
	SceneMap(GGE::SceneID id, GGE	::App* m_app);
	virtual ~SceneMap();

	virtual void Init(void);
	virtual void Events(sf::Event theEvent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Cleanup(void);
	
private:
	GGE::ImageAsset* img_hero;
	sf::Sprite sp_hero;
	sf::Sprite otro;
	std::vector<std::vector<sf::IntRect> > frames;
};

#endif // SCENEMAP_H
