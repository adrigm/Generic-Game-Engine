/**
 * Provides the AssetManager class in the GGE namespace which is responsible
 * for providing the Asset management facilities to the App base class used in
 * the GGE core library.
 *
 */
#ifndef   ASSET_MANAGER_HPP
#define   ASSET_MANAGER_HPP
 
#include <map>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/classes/App.hpp>
#include <GGE/Core/classes/ConfigReader.hpp>
 
namespace GGE
{

class AssetManager
{
public:
	AssetManager(App* theApp);
	~AssetManager();

	void AddDirectory(const std::string& theDitectory);

	void RemoveDirectory(const std::string& theDitectory);

	const sf::Image& GetImage(const std::string& theFilename);

	void DeleteImage(const sf::Image& theImage);

	void DeleteImage(const std::string& theFilename);

	const sf::Font& GetFont(const std::string& theFilename);

	void DeleteFont(const std::string& theFilename);

	const sf::SoundBuffer& GetSoundBuffer(const std::string& theFilename);

	void DeleteSoundBuffer(const std::string& theFilename);

	const ConfigReader& GetConfigFile(const std::string& theFilename);

	void DeleteConfigFile(const std::string& theFilename);

	void Cleanup();

private:
	/// Puntero a App
	App* mApp;
	/// Contenedor de direcorios
	std::vector< std::string > mDirectories;
	/// Contenedor de imagenes
	std::map<std::string, sf::Image> mImages;
	/// Contenedor de tipografias
	std::map<std::string, sf::Font> mFonts;
	/// Contenedor de Sonidos
	std::map<std::string, sf::SoundBuffer> mSounds;
	/// Contenedor de archivos de configuración
	std::map<std::string, ConfigReader*> mConfigFiles;

	AssetManager(const AssetManager&);
	AssetManager& operator =( const AssetManager&);
};

} // namespace GGE

#endif // ASSET_MANAGER_HPP