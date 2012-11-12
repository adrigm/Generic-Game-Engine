#ifndef RECT_COLLISION_HPP
#define RECT_COLLISION_HPP

#include <SFML/Graphics.hpp>

namespace GGE
{

class RectCollision : public sf::FloatRect
{
public:
	RectCollision();
	RectCollision(float rectLeft, float rectTop, float rectWidth, float rectHeight);
	RectCollision(const sf::Vector2f &position, const sf::Vector2f &size);
	RectCollision(const sf::FloatRect &rect);
	RectCollision(const RectCollision &rectColl);

	~RectCollision();

	sf::Vector2f GetCenter() const;

	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	void SetCenter(float x, float y);
	void SetCenter(const sf::Vector2f &center);

	void Move(float offsetX, float offsetY);

}; // Class RectCollision

} // Namespace GGE

#endif // RECT_COLLISION_HPP