#include <GGE/Core/Camera.hpp>

namespace GGE
{

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::RegisterApp(App* theApp)
{
	mApp = theApp;
}

void Camera::Update()
{
}

void Camera::SetDefaultCamera()
{
	mApp->mWindow.SetView(mApp->mWindow.GetDefaultView());
}

void Camera::SetRPGCamera(Map& theMap, Actor& theActor)
{
	mApp->mWindow.SetView(mRPGCamera);
}

void Camera::SetRTSCamera()
{
}

} // Namespace GGE