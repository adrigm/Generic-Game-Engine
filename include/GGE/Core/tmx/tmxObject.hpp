#ifndef TMX_OBJECT_HPP
#define TMX_OBJECT_HPP

#include <string>
#include <map>
#include <GGE/Config.hpp>
#include <GGE/Core/tmx/tmxPropertiesSet.hpp>

namespace GGE
{

class TmxObject
{
public:
	/// Lista de propiedades
	TmxProperties mProperties;

	TmxObject();
	~TmxObject();

	void SetName(const std::string& theName);
	std::string GetName() const;

	void SetType(const std::string& theType);
	std::string GetType() const;

	void SetPosX(const int thePosX);
	GGE::Uint32 GetPosX() const;

	void SetPosY(const int thePosY);
	GGE::Uint32 GetPosY() const;

	void SetWidth(const int theWidth);
	GGE::Uint32 GetWidth() const;

	void SetHeight(const int theHeight);
	GGE::Uint32 GetHeight() const;

	void SetTile(const int theTile);
	GGE::Uint32 GetTile() const;

private:
	/// Nombre del objecto
	std::string mName;
	/// Tipo deo objeto
	std::string mType;
	/// Pos X del objeto
	GGE::Int32 mPosX;
	/// Pos Y del objeto
	GGE::Int32 mPosY;
	/// Ancho del objeto
	GGE::Uint32 mWidth;
	/// Alto del objeto
	GGE::Uint32 mHeight;
	/// Tile del objeto
	GGE::Uint32 mTile;

}; // Class TmxObject

} // Namespace GGE

#endif // TMX_OBJECT_HPP