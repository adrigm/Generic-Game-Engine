#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <GGE/Core/assets/ImageAsset.hpp>

class Actor
{
public:
	sf::Sprite sprite;
	std::vector<std::vector<sf::IntRect> > rects;

	Actor(void);
	Actor(GGE::ImageAsset* img, sf::Uint8 r = 1, sf::Uint8 c = 1);
	~Actor(void);

	void SetImage(GGE::ImageAsset* img, sf::Uint8 r = 1, sf::Uint8 c = 1);

	void SetFrames(sf::Uint8 r, sf::Uint8 c);
	void SetFramesRows(sf::Uint8 r);
	void SetFramesCols(sf::Uint8 c);

	sf::Uint8 GetFramesRows(void) const;
	sf::Uint8 GetFramesCols(void) const;

	sf::Vector2i GetSizeFrame(void) const;
	sf::Uint16 GetSizeFrameX(void) const;
	sf::Uint16 GetSizeFrameY(void) const;

private:
	GGE::ImageAsset* image;
	sf::Uint8 rows;
	sf::Uint8 cols;
	sf::Vector2i size_frame;

	void CreateRects(void);
};

#endif // ACTOR_H
