#include <GGE/Core/Camera.hpp>

namespace GGE
{

Camera::Camera()
{
	mApp = App::Instance();
	// Establecemos la vista por defecto
	mView = mApp->mWindow.GetDefaultView();
	// Establecemos las conexiones como falsas
	mConectToSprite = false;
	mConectToMap = false;
	mApp->mWindow.SetView(mView);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	// Si la cámara está conectada a un sprite (lo sigue)
	if (mConectToSprite)
	{
		// Obtenemos la posición del Sprite conectado
		sf::Vector2f pos = mSprite->GetPosition();
		
		// Si está conectada a un mapa no dejamos que vaya más allá
		if (mConectToMap)
		{
			// Comprobamos los bordes de los mapas para detener el Scroll
			// Eje X
			if (pos.x < mApp->mWindow.GetWidth() / 2)
				pos.x = mApp->mWindow.GetWidth() / 2;
			else if (pos.x > mMap->GetWidth() * mMap->GetTileWidth() - mApp->mWindow.GetWidth() / 2)
				pos.x = mMap->GetWidth() * mMap->GetTileWidth() - mApp->mWindow.GetWidth() / 2;
			// Eje y
			if (pos.y < mApp->mWindow.GetHeight() / 2)
				pos.y = mApp->mWindow.GetHeight() / 2;
			else if (pos.y > mMap->GetHeight() * mMap->GetTileHeight() - mApp->mWindow.GetHeight() / 2)
				pos.y = mMap->GetHeight() * mMap->GetTileHeight() - mApp->mWindow.GetHeight() / 2;
		}
		
		// Cambiamos la posición de la Cámara
		mView.SetCenter(pos);
	}
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
	mView = mApp->mWindow.GetDefaultView();
}

} // Namespace GGE