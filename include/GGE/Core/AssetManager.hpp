#ifndef GGE_Asset_MANAGER_HPP
#define GGE_Asset_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GGE/Core/Tmx/Tmx.hpp>
#include <GGE/Core/ConfigReader.hpp>
#include <GGE/Core/Export.hpp>

namespace GGE
{

class GGE_CORE_API AssetManager
{
	static AssetManager* ms_instance;

public:
	static AssetManager* Instance();

	static void Release();

	void SetPath(const std::string& path);

	sf::Image* GetImage(const std::string& filename);
	void DeleteImage(const std::string& filename);

	sf::Texture* GetTexture(const std::string& filename);
	void DeleteTexture(const std::string& filename);

	sf::SoundBuffer* GetSoundBuffer(const std::string& filename);
	void DeleteSoundBuffer(const std::string& filename);

	sf::Music* GetMusic(const std::string& filename);
	void DeleteMusic(const std::string& filename);

	sf::Font* GetFont(const std::string& filename);
	void DeleteFont(const std::string& filename);

	GGE::Tmx::Map* GetTmxMap(const std::string& filename);
	void DeleteTmxMap(const std::string& filename);

	GGE::ConfigReader* GetConfigFile(const std::string& filename);
	void DeleteConfigFile(const std::string& filename);

protected:
	GGE::App* m_app;

private:
	/// Directorio de recursos
	std::string m_rootPath;
	/// Map que contiene todas las imágenes cargadas
	std::map<std::string, sf::Image*> m_images;
	/// Map que contiene todas las texturas cargadas
	std::map<std::string, sf::Texture*> m_textures;
	/// Map que contiene todas los sonidos cargados
	std::map<std::string, sf::SoundBuffer*> m_sounds;
	/// Map que contiene todas la música cargada
	std::map<std::string, sf::Music*> m_music;
	/// Map que contiene todas las fuentes cargadas
	std::map<std::string, sf::Font*> m_fonts;
	/// Map que contiene todas las tmx cargados
	std::map<std::string, GGE::Tmx::Map*> m_maps;
	/// Map que contiene todas las archivos de configuración cargados
	std::map<std::string, GGE::ConfigReader*> m_configs;

	AssetManager();

	std::string GetAbsolutePath(const std::string& directory) const;

	virtual ~AssetManager();

}; // class AssetManager

} // namespace GGE

#endif // GGE_Asset_MANAGER_HPP