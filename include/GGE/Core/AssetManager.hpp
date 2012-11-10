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
#include <GGE/Core/App.hpp>
#include <GGE/Core/ConfigReader.hpp>
#include <GGE/Core/tmx/tmx.hpp>

namespace GGE
{
class AssetManager
{
	/// Puntero a la instancia única
	static AssetManager* ms_instance;

public:
	static AssetManager* Instance();
	static void Release();

	void AddDirectory(const std::string& theDitectory);

	void RemoveDirectory(const std::string& theDitectory);

	sf::Texture* GetTexture(const std::string& theFilename);
	void DeleteTexture(const std::string& theFilename);

	sf::Font* GetFont(const std::string& theFilename);
	void DeleteFont(const std::string& theFilename);

	sf::SoundBuffer* GetSoundBuffer(const std::string& theFilename);
	void DeleteSoundBuffer(const std::string& theFilename);

	sf::Music* GetMusic(const std::string& theFilenme);
	void DeleteMusic(const std::string& theFilename);

	GGE::ConfigReader* GetConfig(const std::string& theFilename);
	void DeleteConfig(const std::string& theFilename);

	TmxMap* GetTmxMap(const std::string& theFilename);
	void DeleteTmxMap(const std::string& theFilename);

private:
	/// Puntero a App
	GGE::App* mApp;
	/// Contenedor de direcorios
	std::vector< std::string > mDirectories;
	/// Contenedor de imagenes
	std::map<std::string, sf::Image> mImages;
	/// Contenedor de texturas
	std::map<std::string, sf::Texture*> mTextures;
	/// Contenedor de tipografias
	std::map<std::string, sf::Font*> mFonts;
	/// Contenedor de Sonidos
	std::map<std::string, sf::SoundBuffer*> mSoundBuffers;
	/// Contenedor de Musica
	std::map<std::string, sf::Music*> mMusic;
	/// Contenedor de archivos de configuración
	std::map<std::string, GGE::ConfigReader*> mConfigFiles;
	/// Contenedor de archivos TMX
	std::map<std::string, TmxMap*> mTmxMaps;

	AssetManager();
	~AssetManager();
}; // Class AssetManager
} // Namespace GGE

#endif // ASSET_MANAGER_HPP