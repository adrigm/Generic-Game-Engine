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
	mZOrder(2),
	mRectCollision(0, 0, 0, 0),
	mDefineRectCollision(false)
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
	
	if (!mDefineRectCollision)
	{
		mRectCollision.Left = GetPosition().x;
		mRectCollision.Right = GetPosition().x + mWidth;
		mRectCollision.Top = GetPosition().y;
		mRectCollision.Bottom = GetPosition().y + mHeight;
	}
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
	
	if (!mDefineRectCollision)
	{
		mRectCollision.Left = GetPosition().x;
		mRectCollision.Right = GetPosition().x + mWidth;
		mRectCollision.Top = GetPosition().y;
		mRectCollision.Bottom = GetPosition().y + mHeight;
	}

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
		mWidth = mListRects[theNumRect].Right - mListRects[theNumRect].Left;
		mHeight = mListRects[theNumRect].Bottom - mListRects[theNumRect].Top;

		mRectCollision.Left = GetPosition().x;
		mRectCollision.Right = GetPosition().x + mWidth;
		mRectCollision.Top = GetPosition().y;
		mRectCollision.Bottom = GetPosition().y + mHeight;
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

sf::FloatRect Actor::GetRectCollision() const
{
	return mRectCollision;
}

void Actor::SetRectCollision(const sf::FloatRect theRect)
{
	mRectCollision = theRect;
	mDefineRectCollision = true;
}

void Actor::SetPosition(float X, float Y)
{
	sf::Sprite::SetPosition(X, Y);

	mRectCollision.Left = this->GetPosition().x - this->GetCenter().x + mRectCollision.Left;
	mRectCollision.Right = this->GetPosition().x - this->GetCenter().x + mRectCollision.Right;
	mRectCollision.Top =  this->GetPosition().y - this->GetCenter().y + mRectCollision.Top;
	mRectCollision.Bottom = this->GetPosition().y - this->GetCenter().y + mRectCollision.Bottom;
	
	/*mRectCollision.Left = X - this->GetCenter().x;
	mRectCollision.Top = Y - this->GetCenter().y;
	mRectCollision.Right = mRectCollision.Left + mWidth;
	mRectCollision.Bottom = mRectCollision.Top + mHeight;*/
}

void Actor::SetPosition(const sf::Vector2f& Position)
{
	sf::Sprite::SetPosition(Position);

	mRectCollision.Left = this->GetPosition().x - this->GetCenter().x + mRectCollision.Left;
	mRectCollision.Right = this->GetPosition().x - this->GetCenter().x + mRectCollision.Right;
	mRectCollision.Top =  this->GetPosition().y - this->GetCenter().y + mRectCollision.Top;
	mRectCollision.Bottom = this->GetPosition().y - this->GetCenter().y + mRectCollision.Bottom;

	/*mRectCollision.Left = Position.x - this->GetCenter().x;
	mRectCollision.Top = Position.y - this->GetCenter().y;
	mRectCollision.Right = mRectCollision.Left + mWidth;
	mRectCollision.Bottom = mRectCollision.Top + mHeight;*/
}

 void Actor::SetX(float X)
 {
	sf::Sprite::SetX(X);
	mRectCollision.Left = X - this->GetCenter().x;
	mRectCollision.Right = mRectCollision.Left + mWidth;
 }

 void Actor::SetY(float Y)
 {
	sf::Sprite::SetY(Y);
	mRectCollision.Top = Y - this->GetCenter().y;
	mRectCollision.Bottom = mRectCollision.Top + mHeight;
 }

 void Actor::Move(float OffsetX, float OffsetY)
 {
	sf::Sprite::Move(OffsetX, OffsetY);
	mRectCollision.Offset(OffsetX, OffsetY);
 }

 void Actor::Move(const sf::Vector2f& Offset)
 {
	sf::Sprite::Move(Offset);
	mRectCollision.Offset(Offset.x, Offset.y);
 }

} // Namespace GGE