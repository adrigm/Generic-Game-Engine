#ifndef TMX_OBJECTGROUP_HPP
#define TMX_OBJECTGROUP_HPP

#include <vector>
#include <GGE/Config.hpp>
#include <GGE/Core/tmx/tmxPropertiesSet.hpp>
#include <GGE/Core/tmx/tmxObject.hpp>

namespace GGE
{

class TmxObjectGroup
{
public:
	/// Lista de propiedades
	TmxProperties mProperties;
	/// Lista de objetos
	std::vector<TmxObject> mObjects;

	TmxObjectGroup();
	~TmxObjectGroup();

	void SetName(const std::string& theName);
	std::string GetName() const;

	void SetWidth(const int theWidth);
	int GetWidth() const;

	void SetHeight(const int theHeight);
	int GetHeight() const;

	void SetColor(const std::string& theColor);
	std::string GetColor() const;

	void SetVisible(bool theVisible = true);
	bool GetVisible() const;

	void SetOpacity(const double theOpacity = 1.0);
	double GetOpacity() const;

private:
	// Nombre del Objectgroup
	std::string mName;
	/// Ancho
	GGE::Uint32 mWidth;
	/// Alto
	GGE::Uint32 mHeight;
	// Color
	std::string mColor;
	// Opacity
	double mOpacity;
	// visible
	bool mVisible;


}; // Class TmxObjectGroup

} // Namespace GGE

#endif // TMX_OBJECTGROUP_HPP