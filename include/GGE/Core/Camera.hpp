#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/Actor.hpp>
#include <GGE/Core/maps/Map.hpp>

namespace GGE
{

class Camera
{
public:
	Camera();
	~Camera();

	void RegisterApp(App* theApp);

	void Update();

	void SetDefaultCamera();

	void SetRPGCamera(Map& theMap, Actor& theActor);
	void SetRTSCamera();

private:
	/// Puntero a App
	App* mApp;
	/// Puntero al Player
	Actor* mPlayer;
	/// Puntero al mapa
	Map* mMap;
	/// Camara que sigue al jugador
	sf::View mRPGCamera;
	/// Camapara por defecto
	sf::View mDefaultCamera;

}; // Class Camera

} // Namespace GGE

#endif // CAMERA_HPP