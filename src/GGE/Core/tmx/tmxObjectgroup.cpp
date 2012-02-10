#include <GGE/Core/tmx/tmxObjectgroup.hpp>

namespace GGE
{

TmxObjectGroup::TmxObjectGroup()
{
}

TmxObjectGroup::~TmxObjectGroup()
{
}

void TmxObjectGroup::SetName(const std::string& theName)
{
	mName = theName;
}

std::string TmxObjectGroup::GetName() const
{
	return mName;
}

void TmxObjectGroup::SetWidth(const int theWidth)
{
	mWidth = theWidth;
}

int TmxObjectGroup::GetWidth() const
{
	return mWidth;
}

void TmxObjectGroup::SetHeight(const int theHeight)
{
	mHeight = theHeight;
}

int TmxObjectGroup::GetHeight() const
{
	return mHeight;
}

void TmxObjectGroup::SetColor(const std::string& theColor)
{
	mColor = theColor;
}

std::string TmxObjectGroup::GetColor() const
{
	return mColor;
}

void TmxObjectGroup::SetVisible(bool theVisible)
{
	mVisible = theVisible;
}

bool TmxObjectGroup::GetVisible() const
{
	return mVisible;
}

void TmxObjectGroup::SetOpacity(const double theOpacity)
{
	mOpacity = theOpacity;
}

double TmxObjectGroup::GetOpacity() const
{
	return mOpacity;
}

} // Namespace GGE