#ifndef TMX_TILESET_HPP
#define TMX_TILESET_HPP

#include <map>
#include <string>
#include <GGE/Config.hpp>
#include <GGE/Core/tmx/tmxPropertiesSet.hpp>

namespace GGE
{

class TmxTileset
{
public:
	TmxTileset();
	~TmxTileset();

	void SetName(const std::string& theName = "");
	std::string GetName() const;

	void SetFirstGid(const int theFirstGid);
	int GetFirstGid() const;

	void SetTileWidth(const int width);
	int GetTileWidth() const;

	void SetTileHeight(const int height);
	int GetTileHeight() const;

	void SetFile(const std::string& theFile);
	std::string GetFile() const;

	void SetColorkey(const std::string& theTrans);
	std::string GetColorkey() const;

	void SetWidth(const int theWidth);
	int GetWidth() const;

	void SetHeight(const int theHeight);
	int GetHeight() const;

	void SetTileProperty(const int theTile, const std::string& theName, const std::string& theValue);
	std::string GetTileProperty(const int theTile, const std::string& theName) const;

private:
	/// Nombre del tileset
	std::string mName;
	/// Numero del primer tile
	GGE::Uint32 mFirstGid;
	/// Ancho de los tiles
	GGE::Uint32 mTileWidth;
	/// Alto de los tiles
	GGE::Uint32 mTileHeight;
	/// Nombre del archivo
	std::string mFile;
	/// Color key
	std::string mTrans;
	/// Ancho del tileset
	GGE::Uint32 mWidth;
	/// Alto del tileset
	GGE::Uint32 mHeight;
	/// Mapa de propiedades de los tiles
	std::map<int, TmxProperties> mTiles;

}; // Class TmxTileset

} // Namespace GGE

#endif // TMX_TILESET_HPP