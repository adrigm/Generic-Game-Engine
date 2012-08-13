#ifndef SCENE_PLATFORM_HPP
#define SCENE_PLATFORM_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <GGE/Core.hpp>
#include "Player.hpp"

class ScenePlatform : public GGE::Scene
{
public:
	ScenePlatform(GGE::SceneID theID);

	virtual ~ScenePlatform();

	virtual void Init();

	virtual void ReInit();

	virtual void Events(sf::Event theEvent);

	virtual void Update();

	virtual void Cleanup();

private:
	// Acceso rápido al AssetManager
	GGE::AssetManager* AM;
	// Mapa de la escena
	GGE::Map* anMap;
	// Puntero al jugador
	Player* player;
	// Creamos un vector para los diamentes
	std::vector<GGE::Actor*> diamantes;
	// Lista de plataformas del mapa
	std::vector<sf::FloatRect> plataformas;
};

#endif // SCENE_PLATFORM_HPP
