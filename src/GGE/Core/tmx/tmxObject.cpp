#include <GGE/Core/tmx/tmxObject.hpp>

namespace GGE
{

TmxObject::TmxObject()
{
}

TmxObject::~TmxObject()
{
}

void TmxObject::SetName(const std::string& theName)
{
	mName = theName;
}

std::string TmxObject::GetName() const
{
	return mName;
}

void TmxObject::SetType(const std::string& theType)
{
	mType = theType;
}

std::string TmxObject::GetType() const
{
	return mType;
}

void TmxObject::SetPosX(const int thePosX)
{
	mPosX = thePosX;
}

GGE::Uint32 TmxObject::GetPosX() const
{
	return mPosX;
}

void TmxObject::SetPosY(const int thePosY)
{
	mPosY = thePosY;
}

GGE::Uint32 TmxObject::GetPosY() const
{
	return mPosY;
}

void TmxObject::SetWidth(const int theWidth)
{
	mWidth = theWidth;
}

GGE::Uint32 TmxObject::GetWidth() const
{
	return mWidth;
}

void TmxObject::SetHeight(const int theHeight)
{
	mHeight = theHeight;
}

GGE::Uint32 TmxObject::GetHeight() const
{
	return mHeight;
}

void TmxObject::SetTile(const int theTile)
{
	mTile = theTile;
}

GGE::Uint32 TmxObject::GetTile() const
{
	return mTile;
}

} // Namespace GGE