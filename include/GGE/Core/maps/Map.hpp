#ifndef MAP_HPP
#define MAP_HPP

#include <GGE/Config.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/Actor.hpp>
#include <GGE/Core/tmx/tmx.hpp>
#include <GGE/Core/maps/Tileset.hpp>

namespace GGE
{

class Map
{
public:
	Map();
	~Map();

	bool Load(TmxMap& theTmx);
	void Update();
	void Draw();

	void SetScrollParallax(GGE::Actor& thePlayer);

	GGE::Uint32 GetTile(int theLayer, int theRow, int theCol);
	void SetTile(int theLayer, int theRow, int theCol, int theValue);

	GGE::Uint32 GetWidth() const;
	GGE::Uint32 GetHeight() const;

	GGE::Uint32 GetTileWidth() const;
	GGE::Uint32 GetTileHeight() const;

	sf::Vector2i Plot(int TheCol, int TheRow);
	sf::Vector2i MouseMap(int x, int y);
	
private:
	/// Puntero a la aplicacion
	App* mApp;
	/// Fichero TMX
	TmxMap* mTmx;
	/// Número de columnas de tiles del mapa
	GGE::Uint32 mWidth;
	/// Numero de filas de tiles del mapa
	GGE::Uint32 mHeight;
	/// Ancho de los tiles
	GGE::Uint32 mTileWidth;
	/// Alto de los tiles
	GGE::Uint32 mTileHeight;
	/// Objeto Tileset
	Tileset* mTileset;
	// Data
	std::vector<std::vector<std::vector<GGE::Uint32> > > mData;

	int correctionX;
	int correctionY;
};

} // Namespace GGE

#endif // MAP_HPP