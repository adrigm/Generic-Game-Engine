#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/System/Vector2.hpp>

namespace GGE
{

template <typename T>
class Circle
{
public:
	sf::Vector2<T> Center;
	T Radius;

	Circle();

	Circle(const sf::Vector2<T> theCenter, T theRadious);

	void Offset(T OffsetX, T OffsetY);

	T GetDiameter() const;

	bool Contains(T X, T Y);

	bool Intersects(const Circle<T> Circle);
};

#include <GGE/Core/utils/Circle.inl>

// Define the most common types
typedef Circle<int>   IntCircle;
typedef Circle<float> FloatCircle;

} // Namespace GGE

#endif // CIRCLE_HPP