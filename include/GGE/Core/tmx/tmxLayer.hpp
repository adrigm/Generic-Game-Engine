#ifndef TMX_LAYER_HPP
#define TMX_LAYER_HPP

#include <vector>
#include <GGE/Config.hpp>
#include <GGE/Core/tmx/tmxPropertiesSet.hpp>

namespace GGE
{

class TmxLayer
{
public:
	/// Propiedades de la capa
	TmxProperties mProperties;
	/// Vector de tiles de la capa
	std::vector<std::vector<GGE::Uint32> > mTiles;

	TmxLayer();
	~TmxLayer();

	void DescompressData();

	void SetName(const std::string& theName);
	std::string GetName() const;

	void SetWidth(const int theWidth);
	int GetWidth() const;

	void SetHeight(const int theHeight);
	int GetHeight() const;

	void SetEncoding(const std::string& theEncoding);
	std::string GetEncoding() const;

	void SetCompression(const std::string& theCompression);
	std::string GetCompression() const;

	void SetData(const std::string& theData);
	std::string GetData() const;

	void SetVisible(bool theVisible = true);
	bool GetVisible() const;

	void SetOpacity(const double theOpacity = 1.0);
	double GetOpacity() const;

private:
	/// Nombre de la capa
	std::string mName;
	/// Ancho de la capa
	GGE::Uint32 mWidth;
	/// Alto de la capa
	GGE::Uint32 mHeight;
	/// Codificacion de la capa
	std::string mEncoding;
	/// Compresion de la capa
	std::string mCompression;
	/// Cadena de datos de tiles
	std::string mData;
	// Visibilidad
	bool mVisible;
	// Opacidad
	double mOpacity;

};

} // Namespace GGE

#endif // TMX_LAYER_HPP