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
	Map(App* theApp);
	~Map();

	bool Load(TmxMap& theTmx);
	void Update();
	void Draw();

	void SetScrollParallax(GGE::Actor& thePlayer);

	sf::Vector2f Plot(int TheCol, int TheRow);
	sf::Vector2f MouseMap(int x, int y);
	
private:
	/// Puntero a la aplicacion
	App* mApp;
	/// Fichero TMX
	TmxMap* mTmx;
	/// Ancho del mapa
	GGE::Uint32 mWidth;
	/// Alto del mapa;
	GGE::Uint32 mHeight;
	/// Ancho de los tiles
	GGE::Uint32 mTileWidth;
	/// Alto de los tiles
	GGE::Uint32 mTileHeight;
	/// Objeto Tileset
	Tileset mTileset;
	// Data
	std::vector<std::vector<std::vector<GGE::Uint32> > > mData;
	/// Puntero al Objeto Player
	GGE::Actor* mPlayer;
	// Scroll
	sf::Vector2f mScroll;
	// view
	sf::View vis;
	sf::Vector2f initial;
	sf::Vector2f limit_bottom;
	sf::Vector2f limit_right;
	int correctionX;
	int correctionY;
};

} // Namespace GGE

#endif // MAP_HPP