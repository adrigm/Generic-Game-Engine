#include "actor.h"


Actor::Actor(void)
{
}

Actor::Actor(GGE::ImageAsset* img, sf::Uint8 r, sf::Uint8 c)
{
	image = img;
	rows = r;
	cols = c;
}

void Actor::SetImage(GGE::ImageAsset* img, sf::Uint8 r, sf::Uint8 c)
{
	image = img;
	rows = r;
	cols = c;
}

void Actor::SetFrames(sf::Uint8 r, sf::Uint8 c)
{
	rows = r;
	cols = c;
}

void Actor::SetFramesRows(sf::Uint8 r)
{
	rows = r;
}

void Actor::SetFramesCols(sf::Uint8 c)
{
	cols = c;
}

sf::Uint8 Actor::GetFramesCols(void) const
{
	return cols;
}

sf::Uint8 Actor::GetFramesRows(void) const
{
	return rows;
}

sf::Vector2i Actor::GetSizeFrame(void) const
{
	return size_frame;
}

sf::Uint16 Actor::GetSizeFrameX(void) const
{
	return size_frame.x;
}

sf::Uint16 Actor::GetSizeFrameY(void) const
{
	return size_frame.y;
}

Actor::~Actor(void)
{
}
