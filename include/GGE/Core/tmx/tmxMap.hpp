
#ifndef TMX_MAP_HPP
#define TMX_MAP_HPP

#include <vector>
#include <string>
#include <GGE/Config.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/tmx/tmxPropertiesSet.hpp>
#include <GGE/Core/tmx/tmxTileset.hpp>
#include <GGE/Core/tmx/tmxLayer.hpp>

namespace GGE
{

class TmxMap
{
public:
	/// Set de propiedades
	TmxProperties mProperties;
	/// Lista de tilesets
	std::vector<TmxTileset> mTilesets;
	/// Lista de capas
	std::vector<TmxLayer> mLayers;

	TmxMap();
	~TmxMap();
	void RegisterApp(App* theApp);
	bool LoadFromFile(std::string& theFilename);

private:
	/// Puntero a la App
	App* mApp;
	/// Version del mapa
	double mVersion;
	/// Orientacion del mapa
	std::string mOrientation;
	/// Ancho del mapa
	GGE::Uint32 mWidth;
	/// Alto del mapa
	GGE::Uint32 mHeight;
	/// Ancho del tile
	GGE::Uint32 mTileWidth;
	/// Alto del tile
	GGE::Uint32 mTileHeight;

}; // class TmxMap

} // Namespace GGE

#endif // TMX_MAP_HPP