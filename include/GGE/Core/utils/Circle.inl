////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
template <typename T>
Circle<T>::Circle() :
	Center(0, 0),
	Radius(0)
{
}


////////////////////////////////////////////////////////////
/// Construct the color from its coordinates
////////////////////////////////////////////////////////////
template <typename T>
Circle<T>::Circle(const sf::Vector2<T> theCenter, T theRadious) :
	Center(theCenter),
	Radius(theRadious)
{

}


////////////////////////////////////////////////////////////
/// Get the diameter of the Circle
////////////////////////////////////////////////////////////
template <typename T>
T Circle<T>::GetDiameter() const
{
    return 2*Radius;
}


////////////////////////////////////////////////////////////
/// Move the whole Circleangle by the given offset
////////////////////////////////////////////////////////////
template <typename T>
void Circle<T>::Offset(T OffsetX, T OffsetY)
{
    Center.x   += OffsetX;
    Center.y    += OffsetY;
}

template <typename T>
bool Circle<T>::Contains(T X, T Y)
{
	if (abs(Center.x - X) <= Radius && abs(Center.y - Y) <= Radius)
		return true;
	return false;
}

template <typename T>
bool Circle<T>::Intersects(const Circle<T> Circle)
{
	T dis = pow(abs(Center.x - Circle.Center.x), 2) + pow(abs(Center.y - Circle.Center.y), 2);
	if (dis <= pow(Radius + Circle.Radius, 2))
		return true;
	return false;
}