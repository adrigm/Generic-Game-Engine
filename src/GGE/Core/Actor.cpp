#include <GGE/Core/Actor.hpp>
#include <iostream>

namespace GGE
{

Actor::Actor() :
	mRows(1),
	mCols(1),
	mWidth(0),
	mHeight(0),
	mVisible(true),
	mZOrder(2)
{
}

Actor::~Actor()
{
}

void Actor::SetImage(const sf::Image& Img)
{
	sf::Sprite::SetImage(Img);
	mWidth = GetImage()->GetWidth();
	mHeight = GetImage()->GetHeight();
}

void Actor::SetGrid(const GGE::Uint32 theRows, const GGE::Uint32 theCols)
{
	mRows = theRows;
	mCols = theCols;
	mWidth = this->GetImage()->GetWidth() / theCols;
	mHeight = this->GetImage()->GetHeight() / theRows;
	for (int r = 0; r <theRows; r++)
	{
		std::vector<sf::IntRect> anCol;
		for (int c = 0; c < theCols; c++)
		{
			anCol.push_back(sf::IntRect(mWidth*c, mHeight*r, mWidth*c+mWidth, mHeight*r+mHeight));
		}
		mRects.push_back(anCol);
		anCol.clear();
	}
	SetSubRect(mRects[0][0]); 
}

void Actor::SelectGid(const GGE::Uint32 theRow, const GGE::Uint32 theCol)
{
	if (theRow <= mRects.size() && theRow > 0)
		if (theCol <= mRects[0].size() && theCol > 0)
			SetSubRect(mRects[theRow-1][theCol-1]);
}

void Actor::AddRects(const std::vector<sf::IntRect> theListRects)
{
	mListRects.insert(mListRects.end(), theListRects.begin(), theListRects.end());
}

void Actor::AddRects(const sf::IntRect theRect)
{
	mListRects.push_back(theRect);
}

void Actor::SelectRect(const GGE::Uint32 theNumRect)
{
	if (theNumRect < mListRects.size())
	{
		SetSubRect(mListRects[theNumRect]);
	}
}

GGE::Uint32 Actor::GetWidth() const
{
	return mWidth;
}

GGE::Uint32 Actor::GetHeight() const
{
	return mHeight;
}

bool Actor::IsVisible() const
{
	return mVisible;
}

void Actor::Show()
{
	mVisible = true;
}

void Actor::Hide()
{
	mVisible = false;
}

} // Namespace GGE