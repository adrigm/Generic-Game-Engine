#include <GGE/Core/Camera.hpp>

namespace GGE
{

Camera::Camera()
{
	mApp = App::Instance();
	// Establecemos la vista por defecto
	mView = mApp->mWindow.getDefaultView();
	// Establecemos las conexiones como falsas
	mConectToSprite = false;
	mConectToMap = false;
	mApp->mWindow.setView(mView);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	mApp->mWindow.setView(mView);
}

void Camera::ConnectToSprite(sf::Sprite& theSprite)
{
	mSprite = &theSprite;
	mConectToSprite = true;
}

void Camera::DisconnectToSprite()
{
	mConectToSprite = false;
	mSprite = 0;
}

void Camera::LockToMap(GGE::Map& theMap)
{
	mMap = &theMap;
	mConectToMap = true;
}

void Camera::SetDefaultCamera()
{
	mConectToSprite = false;
	mView = mApp->mWindow.getDefaultView();
}

} // Namespace GGE