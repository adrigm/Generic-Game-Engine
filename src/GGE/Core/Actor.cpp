#include <GGE/Core/App.hpp>
#include <GGE/Core/Actor.hpp>
#include <iostream> // Quitar

namespace GGE
{

Actor::Actor() :
	mZOrder(2),
	mVisible(true),
	mSelectFrame(1),
	mSelectFrameAnimation(0),
	mElapsedTime(0.0f),
	myIsFlippedX(false)
{
	mApp = GGE::App::Instance();
}

Actor::~Actor()
{
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

void Actor::SetFramesByNum(GGE::Uint32 theRows, GGE::Uint32 theCols)
{
	mRectsList.clear();

	GGE::Uint32 width = this->getTexture()->getSize().x / theCols;
	GGE::Uint32 height = this->getTexture()->getSize().y / theRows;

	for (int r = 0; r < theRows; r++)
	{
		for (int c = 0; c < theCols; c++)
		{
			mRectsList.push_back(sf::IntRect(c*width, r*height, width, height));
		}
	}

	this->SelectFrame(1);
}

bool Actor::SelectFrame(GGE::Uint32 theFrame)
{
	if (theFrame < 1 || theFrame > mRectsList.size())
	{
		mApp->mLog << "Actor::SelectFrame() Frame fuera de rango: " << theFrame << std::endl;
		return false;
	}
	else
	{
		this->setTextureRect(mRectsList[theFrame-1]);
		this->mSelectFrame = theFrame;
		return true;
	}
}

GGE::Uint32 Actor::GetSelectFrame() const
{
	return this->mSelectFrame;
}

void Actor::AddAnimation(const std::string theName, const GGE::Animation theAnim)
{
	mListAnim[theName] = theAnim;
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
		{
			mSelectFrameAnimation++;
		}
		else
		{
			mSelectFrameAnimation = this->GetActiveAnimation().firstFrame;
		}
	}
}

void Actor::FlipX(bool flipped)
{
	myIsFlippedX = flipped;
}

} // Namespace GGE