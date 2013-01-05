#include <algorithm>
#include <boost/filesystem.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/AssetManager.hpp>
#include <iostream> // Quitar

namespace GGE
{

AssetManager* AssetManager::ms_instance = 0;

AssetManager::AssetManager() :
	m_rootPath("")
{
	m_app = GGE::App::Instance();
}

AssetManager::~AssetManager()
{
}

AssetManager* AssetManager::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new AssetManager();
	}
	return ms_instance;
}

void AssetManager::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

std::string AssetManager::GetAbsolutePath(const std::string& directory) const
{
	namespace fs = boost::filesystem;

	fs::path path = directory;

	if (!path.is_absolute())
	{
		fs::path root = m_app->GetExecutableDir();
		path = root / path;
	}

	path = fs::system_complete(path);
	
	if (fs::exists(path) && fs::is_directory(path))
	{
		path = fs::canonical(path);
		path = path.generic_string();
		std::string path_s = path.string();
		path_s.append("/");

		return path_s;
	}

	m_app->log << "[warn] AssetManager::GetAbsolutePath() no existe dir=\"" 
		<< path.string() << "\"" << std::endl;
	return "";
}

void AssetManager::SetPath(const std::string& path)
{
	m_rootPath = this->GetAbsolutePath(path);
}

sf::Image* AssetManager::GetImage(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, sf::Image*>::const_iterator it =  m_images.find(filename);
	if (it != m_images.end())
	{
		m_app->log << "AssetManager::GetImage() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetImage()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	sf::Image* image = new sf::Image();
	if (!image->loadFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetImage() " << filename << " no se ha podido cargar" << std::endl;
		return image;
	}

	m_app->log << "AssetManager::GetImage() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_images[filename] = image;

	// Se la damos al usuario
	return image;
}

void AssetManager::DeleteImage(const std::string& filename)
{
	std::map<std::string, sf::Image*>::const_iterator it = m_images.find(filename);
	if (it != m_images.end())
	{
		delete it->second;
		m_images.erase(it);
		m_app->log << "AssetManager::DeleteImage() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteImage() " << filename << "no está cargado" << std::endl;
}

sf::Texture* AssetManager::GetTexture(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, sf::Texture*>::const_iterator it =  m_textures.find(filename);
	if (it != m_textures.end())
	{
		m_app->log << "AssetManager::GetTexture() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetTexture()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	sf::Texture* Texture = new sf::Texture();
	if (!Texture->loadFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetTexture() " << filename << " no se ha podido cargar" << std::endl;
		return Texture;
	}

	m_app->log << "AssetManager::GetTexture() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_textures[filename] = Texture;

	// Se la damos al usuario
	return Texture;
}

void AssetManager::DeleteTexture(const std::string& filename)
{
	std::map<std::string, sf::Texture*>::const_iterator it = m_textures.find(filename);
	if (it != m_textures.end())
	{
		delete it->second;
		m_textures.erase(it);
		m_app->log << "AssetManager::DeleteTexture() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteTexture() " << filename << "no está cargado" << std::endl;
}

sf::SoundBuffer* AssetManager::GetSoundBuffer(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, sf::SoundBuffer*>::const_iterator it =  m_sounds.find(filename);
	if (it != m_sounds.end())
	{
		m_app->log << "AssetManager::GetSoundBuffer() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetSoundBuffer()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	if (!soundBuffer->loadFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetSoundBuffer() " << filename << " no se ha podido cargar" << std::endl;
		return soundBuffer;
	}

	m_app->log << "AssetManager::GetSoundBuffer() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_sounds[filename] = soundBuffer;

	// Se la damos al usuario
	return soundBuffer;
}

void AssetManager::DeleteSoundBuffer(const std::string& filename)
{
	std::map<std::string, sf::SoundBuffer*>::const_iterator it = m_sounds.find(filename);
	if (it != m_sounds.end())
	{
		delete it->second;
		m_sounds.erase(it);
		m_app->log << "AssetManager::DeleteSoundBuffer() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteSoundBuffer() " << filename << "no está cargado" << std::endl;
}

sf::Music* AssetManager::GetMusic(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, sf::Music*>::const_iterator it =  m_music.find(filename);
	if (it != m_music.end())
	{
		m_app->log << "AssetManager::GetMusic() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetMusic()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetMusic() " << filename << " no se ha podido cargar" << std::endl;
		return music;
	}

	m_app->log << "AssetManager::GetMusic() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_music[filename] = music;

	// Se la damos al usuario
	return music;
}

void AssetManager::DeleteMusic(const std::string& filename)
{
	std::map<std::string, sf::Music*>::const_iterator it = m_music.find(filename);
	if (it != m_music.end())
	{
		delete it->second;
		m_music.erase(it);
		m_app->log << "AssetManager::DeleteMusic() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteMusic() " << filename << "no está cargado" << std::endl;
}

sf::Font* AssetManager::GetFont(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, sf::Font*>::const_iterator it =  m_fonts.find(filename);
	if (it != m_fonts.end())
	{
		m_app->log << "AssetManager::GetFont() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetFont()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetFont() " << filename << " no se ha podido cargar" << std::endl;
		return font;
	}

	m_app->log << "AssetManager::GetFont() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_fonts[filename] = font;

	// Se la damos al usuario
	return font;
}

void AssetManager::DeleteFont(const std::string& filename)
{
	std::map<std::string, sf::Font*>::const_iterator it = m_fonts.find(filename);
	if (it != m_fonts.end())
	{
		delete it->second;
		m_fonts.erase(it);
		m_app->log << "AssetManager::DeleteFont() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteFont() " << filename << "no está cargado" << std::endl;
}

GGE::Tmx::Map* AssetManager::GetTmxMap(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, GGE::Tmx::Map*>::const_iterator it =  m_maps.find(filename);
	if (it != m_maps.end())
	{
		m_app->log << "AssetManager::GetTmxMap() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetTmxMap()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	GGE::Tmx::Map* map = new GGE::Tmx::Map();
	map->ParseFile(m_rootPath + filename);
	if (map->HasError())
	{
		m_app->log << "[error] AssetManager::GetTmxMap() " << filename << " "
			<< map->GetErrorText() << " no se ha podido cargar" << std::endl;
		return map;
	}

	m_app->log << "AssetManager::GetTmxMap() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_maps[filename] = map;

	// Se la damos al usuario
	return map;
}

void AssetManager::DeleteTmxMap(const std::string& filename)
{
	std::map<std::string, GGE::Tmx::Map*>::const_iterator it = m_maps.find(filename);
	if (it != m_maps.end())
	{
		delete it->second;
		m_maps.erase(it);
		m_app->log << "AssetManager::DeleteTmxMap() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteTmxMap() " << filename << "no está cargado" << std::endl;
}

GGE::ConfigReader* AssetManager::GetConfigFile(const std::string& filename)
{
	// Comprobamos si existe el recurso
	std::map<std::string, GGE::ConfigReader*>::const_iterator it =  m_configs.find(filename);
	if (it != m_configs.end())
	{
		m_app->log << "AssetManager::GetConfigFile() " << filename << " usando archivo existente" << std::endl;
		return it->second;
	}

	if (m_rootPath == "")
	{
		m_app->log << "[warn] AssetManager::GetConfigFile()  no se han definido rutas de búsqueda."
			<< "Se buscan rutas relativas al directorio actual" << std::endl;
	}

	// Si no existe lo intentamos cargar
	GGE::ConfigReader* config = new GGE::ConfigReader();
	if (!config->LoadFromFile(m_rootPath + filename))
	{
		m_app->log << "[error] AssetManager::GetConfigFile() " << filename << " no se ha podido cargar" << std::endl;
		return config;
	}

	m_app->log << "AssetManager::GetConfigFile() " << filename << " archivo cargado" << std::endl;

	// Si se carga la registramos
	m_configs[filename] = config;

	// Se la damos al usuario
	return config;
}

void AssetManager::DeleteConfigFile(const std::string& filename)
{
	std::map<std::string, GGE::ConfigReader*>::const_iterator it = m_configs.find(filename);
	if (it != m_configs.end())
	{
		delete it->second;
		m_configs.erase(it);
		m_app->log << "AssetManager::DeleteConfigFile() " << filename << "archivo eliminado" << std::endl;
		return;
	}

	m_app->log << "AssetManager::DeleteConfigFile() " << filename << "no está cargado" << std::endl;
}

} // namespace GGE