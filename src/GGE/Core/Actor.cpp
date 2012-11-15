#include <GGE/Core/App.hpp>
#include <GGE/Core/Actor.hpp>
#include <iostream> // Quitar

namespace GGE
{

Actor::Actor() :
	mZOrder(2),
	mSelectFrame(1),
	mSelectFrameAnimation(0),
	mElapsedTime(0.0f),
	mIsFlippedX(false),
	mIsFlippedY(false)
{
	mApp = GGE::App::Instance();
}

Actor::~Actor()
{
}

void Actor::SetFramesBySize(GGE::Uint32 theWidth, GGE::Uint32 theHeight)
{
	mRectsList.clear();

	GGE::Uint32 cols = this->getTexture()->getSize().x / theWidth;
	GGE::Uint32 rows = this->getTexture()->getSize().y / theHeight;

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			mRectsList.push_back(sf::IntRect(c*theWidth, r*theHeight, theWidth, theHeight));

	this->setTextureRect(mRectsList[0]);

	this->SelectFrame(1);
}

void Actor::SetFramesByGrid(GGE::Uint32 theRows, GGE::Uint32 theCols)
{
	mRectsList.clear();

	GGE::Uint32 width = this->getTexture()->getSize().x / theCols;
	GGE::Uint32 height = this->getTexture()->getSize().y / theRows;

	for (int r = 0; r < theRows; r++)
		for (int c = 0; c < theCols; c++)
			mRectsList.push_back(sf::IntRect(c*width, r*height, width, height));

	this->SelectFrame(1);
}

void Actor::SelectFrame(GGE::Uint32 theFrame)
{
	if (!mRectsList.empty())
	{
		// Elegimos el frame de forma modular
		this->setTextureRect(mRectsList[(theFrame - 1) % mRectsList.size()]);
		// Le damos la vuelta al rect de la textura según los flips
		if (mIsFlippedX)
			this->setTextureRect(sf::IntRect(this->getTextureRect().left + this->getTextureRect().width, this->getTextureRect().top, -this->getTextureRect().width, this->getTextureRect().height));
		if (mIsFlippedY)
			this->setTextureRect(sf::IntRect(this->getTextureRect().left, this->getTextureRect().top + this->getTextureRect().height, this->getTextureRect().width, -this->getTextureRect().height));
		this->mSelectFrame = theFrame;
	}
}

GGE::Uint32 Actor::GetSelectFrame() const
{
	return this->mSelectFrame;
}

void Actor::AddAnimation(const std::string theName, const GGE::Animation theAnim)
{
	if (mListAnim.find(theName) == mListAnim.end())
		this->mListAnim[theName] = theAnim;
}


GGE::Animation Actor::GetAnimation(std::string theName) const
{
	return mListAnim.find(theName)->second;
}

void Actor::SetActiveAnimation(const std::string theName, bool reset)
{
	mActiveAnimation = mListAnim.find(theName)->second;
	this->SelectFrame(this->GetActiveAnimation().firstFrame);
	mSelectFrameAnimation = this->GetSelectFrame();
}

GGE::Animation Actor::GetActiveAnimation() const
{
	return mActiveAnimation;
}

void Actor::Animate()
{
	mElapsedTime += mApp->GetUpdateTime();

	if (mElapsedTime >= 1.0f / this->GetActiveAnimation().fps)
	{
		mElapsedTime = 0.0f;

		this->SelectFrame(mSelectFrameAnimation);

		if (this->GetSelectFrame() < this->GetActiveAnimation().lastFrame)
			mSelectFrameAnimation++;
		else
			mSelectFrameAnimation = this->GetActiveAnimation().firstFrame;
	}
}

void Actor::FlipX(bool flippedX)
{
	mIsFlippedX = flippedX;
	this->SelectFrame(this->GetSelectFrame());
}

void Actor::FlipY(bool flippedY)
{
	mIsFlippedY = flippedY;
	this->SelectFrame(this->GetSelectFrame());
}

void Actor::SetLeftPosition(float x)
{
	this->setPosition(x + this->getOrigin().x, this->getPosition().y);
}


void Actor::SetTopPosition(float y)
{
	this->setPosition(this->getPosition().x, y + this->getOrigin().y);
}

void Actor::SetRightPosition(float x)
{
	this->setPosition(x - (this->getGlobalBounds().width - this->getOrigin().x), this->getPosition().y);
}

void Actor::SetBottomPosition(float y)
{
	this->setPosition(this->getPosition().x, y - (this->getGlobalBounds().height - this->getOrigin().y));
}

float Actor::GetLeftPosition() const
{
	return this->getGlobalBounds().left;
}

float Actor::GetTopPosition() const
{
	return this->getGlobalBounds().top;
}
float Actor::GetRightPosition() const
{
	return this->getGlobalBounds().left + this->getGlobalBounds().width;
}

float Actor::GetBottomPosition() const
{
	return this->getGlobalBounds().top + this->getGlobalBounds().height;
}

} // Namespace GGE