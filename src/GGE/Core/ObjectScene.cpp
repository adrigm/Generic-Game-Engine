#include <GGE/Core/ObjectScene.hpp>

namespace GGE
{

ObjectScene::ObjectScene() :
	mVisible(true),
	mZOrder(0)
{
}

ObjectScene::~ObjectScene()
{
}

GGE::Int32 ObjectScene::GetZOrder() const
{
	return mZOrder;
}

void ObjectScene::SetZOrder(int z)
{
	mZOrder = z;
}

bool ObjectScene::IsVisible() const
{
	return mVisible;
}

void ObjectScene::Show()
{
	mVisible = true;
}

void ObjectScene::Hide()
{
	mVisible = false;
}

} // Namespace GGE