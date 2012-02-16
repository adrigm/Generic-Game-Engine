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

void Camera::SetDefaultCamera()
{
	mCamera = mApp->mWindow.GetDefaultView();
}

} // Namespace GGE