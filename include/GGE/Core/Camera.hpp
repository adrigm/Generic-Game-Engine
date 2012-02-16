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

	void SetDefaultCamera();

private:
	/// Puntero a App
	App* mApp;
	/// Camara
	sf::View mCamera;

}; // Class Camera

} // Namespace GGE

#endif // CAMERA_HPP