#include <GGE/Core/Camera.hpp>

namespace GGE
{

Camera::Camera()
{
	mApp = App::Instance();
	this->SetDefaultCamera();
	// Establecemos las conexiones como falsas
	mConectToSprite = false;
	mConectToMap = false;
}

Camera::~Camera()
{
}

void Camera::Update()
{
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
	this->reset(sf::FloatRect(0, 0, static_cast<float>(mApp->mWindow.getSize().x), static_cast<float>(mApp->mWindow.getSize().y)));
	mConectToSprite = false;
}

sf::FloatRect Camera::GetRect() const
{
	sf::FloatRect rect;
	rect.left = this->getCenter().x - this->getSize().x / 2.0f;
	rect.top = this->getCenter().y - this->getSize().y / 2.0f;
	rect.width = this->getSize().x;
	rect.height = this->getSize().y;
	return rect;
}

} // Namespace GGE