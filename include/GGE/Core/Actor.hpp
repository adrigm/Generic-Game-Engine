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
	/// Orden de prioridad de dibujado
	GGE::Int32 mZOrder;

	Actor();
	~Actor();
	
	void SetImage(const sf::Image& Img);

	void SetGrid(const GGE::Uint32 theRows = 1, const GGE::Uint32 theCols = 1);
	void SelectGid(const GGE::Uint32 theRows = 1, const GGE::Uint32 theCols = 1);

	bool IsVisible() const;
	void Show();
	void Hide();

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
	bool mVisible;
	

}; // Class Actor

} // Namepace GGE

#endif // ACTOR_HPP