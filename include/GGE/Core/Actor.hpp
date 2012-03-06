#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <GGE/Config.hpp>

namespace GGE
{

class Actor : public sf::Sprite
{
public:
	Actor();
	~Actor();
	

	void SetGrid(const GGE::Uint32 theRows = 1, const GGE::Uint32 theCols = 1);
	void SelectGid(const GGE::Uint32 theRows = 1, const GGE::Uint32 theCols = 1);

	GGE::Uint32 GetWidth() const;
	GGE::Uint32 GetHeight() const;

private:
	/// Filas del Actor
	GGE::Uint32 mRows;
	/// Columnas del Actor
	GGE::Uint32 mCols;
	/// Ancho del Actor
	GGE::Uint32 mWidth;
	/// Alto del Actor
	GGE::Uint32 mHeight;
	/// Vector de Rects del Actor
	std::vector<std::vector<sf::IntRect> > mRects;
	/// Si el Actor es visible o no
	bool mShow;
	

}; // Class Actor

} // Namepace GGE

#endif // ACTOR_HPP