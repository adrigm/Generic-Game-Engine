#include <GGE/Core/collision/RectCollision.hpp>

namespace GGE
{

RectCollision::RectCollision() :
	sf::FloatRect()
{
}

RectCollision::RectCollision(float rectLeft, float rectTop, float rectWidth, float rectHeight) :
	sf::FloatRect(rectLeft, rectTop, rectWidth, rectHeight)
{
}

RectCollision::RectCollision(const sf::Vector2f &position, const sf::Vector2f &size) :
	sf::FloatRect(position, size)
{
}

RectCollision::RectCollision(const sf::FloatRect &rect) :
	sf::FloatRect(rect)
{
}

RectCollision::RectCollision(const RectCollision &rectColl) :
	sf::FloatRect(rectColl.left, rectColl.top, rectColl.width, rectColl.height)
{
}

RectCollision::~RectCollision()
{
}

sf::Vector2f RectCollision::GetCenter() const
{
	sf::Vector2f center;
	center.x = this->left + this->width / 2.0f;
	center.y = this->top + this->height / 2.0f;
	return center;
}

float RectCollision::GetLeft() const
{
	return left;
}

float RectCollision::GetTop() const
{
	return top;
}

float RectCollision::GetRight() const
{
	return left + width;
}

float RectCollision::GetBottom() const
{
	return top + height;
}

void RectCollision::SetCenter(float x, float y)
{
	left = x - width / 2.0f;
	top = y - height / 2.0f;
}

void RectCollision::SetCenter(const sf::Vector2f &center)
{
	left = center.x - width / 2.0f;
	top = center.y - height / 2.0f;
}

void RectCollision::Move(float offsetX, float offsetY)
{
	left += offsetX;
	top += offsetY;
}

} // Namespace GGE