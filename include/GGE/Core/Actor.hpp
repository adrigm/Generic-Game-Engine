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
	void SelectGid(const GGE::Uint32 theRow = 1, const GGE::Uint32 theCol = 1);

	void AddRects(const std::vector<sf::IntRect> theListRects);
	void AddRects(const sf::IntRect theRect);
	void SelectRect(const GGE::Uint32 theNumRect);

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
	/// Vector de Rects del Actor en filas y columnas
	std::vector<std::vector<sf::IntRect> > mRects;
	/// Lista de Rects del Actor
	std::vector<sf::IntRect> mListRects;
	/// Si el Actor es visible o no
	bool mVisible;
	

}; // Class Actor

} // Namepace GGE

#endif // ACTOR_HPP