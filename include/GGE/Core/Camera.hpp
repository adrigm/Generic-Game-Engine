#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/maps/Map.hpp>

namespace GGE
{

class Camera : public sf::View
{
public:

	Camera();
	~Camera();

	void Update();

	void ConnectToSprite(sf::Sprite& theSprite);
	void DisconnectToSprite();

	void LockToMap(GGE::Map& theMap);

	void SetDefaultCamera();

	sf::FloatRect GetRect() const;

private:
	/// Puntero a App
	App* mApp;
	/// Puntero al Sprite conectado
	sf::Sprite* mSprite;
	/// Puntero al Mapa conectado
	GGE::Map* mMap;
	/// Dice si la Cámara está conectada a un Sprite
	bool mConectToSprite;
	/// Dice si la Cámara está conectada a un mapa
	bool mConectToMap;

}; // Class Camera

} // Namespace GGE

#endif // CAMERA_HPP