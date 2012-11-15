#include <GGE/Core/AssetManager.hpp>

namespace GGE
{

AssetManager* AssetManager::ms_instance = 0;

AssetManager::AssetManager() :
	mApp(NULL)
{
	mApp = GGE::App::Instance();
	mApp->mLog << "AssetManager::ctor() Constructor llmado" << std::endl;
}

AssetManager::~AssetManager()
{
	mDirectories.clear();
	mApp->mLog << "AssetManager::dtor() Destructor llamado" << std::endl;
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

void AssetManager::AddDirectory(const std::string& directory)
{
	// Comprobamos si existe el directorio
	for(std::vector<std::string>::iterator it  = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		// Si existe no es necesario hacer nada más
		if(directory == (*it))
			return;
	}

	// TODO: Comprobar si el último caracter del directorio es / o \

	// Añadimos el directorio a la lista
	mDirectories.push_back( directory );
	mApp->mLog << "AssetManager::AddDirectory() Dir=" << directory << std::endl;
}

void AssetManager::RemoveDirectory(const std::string& directory)
{
	for(std::vector<std::string>::iterator it  = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		// The path exists. So it isn't necessary to add id once more.
		if(directory == (*it))
		{
			it = mDirectories.erase(it);
			mApp->mLog << "AssetManager::RemoveDirectory() Dir=" << directory << std::endl;
			return;
		}
	}
	mApp->mLog << "AssetManager::RemoveDirectory() No existe el directorio " << directory << std::endl;
}

sf::Texture* AssetManager::GetTexture(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, sf::Texture*>::iterator it = mTextures.begin();
		it != mTextures.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetTexture() " << theFilename << " usando textura existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	sf::Texture* anTexture = new sf::Texture();

	// Buscamos en la lista de directorios
	for (std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anTexture->loadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mTextures[theFilename] = anTexture;
			mApp->mLog << "AssetManager::GetImage() " << theFilename << " textura cargada.\n";
			return mTextures[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anTexture->loadFromFile(mApp->GetExecutableDir() + theFilename))
	{
		mTextures[theFilename] = anTexture;
		mApp->mLog << "AssetManager::GetImage() " << theFilename << " textura cargada.\n";
		return mTextures[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetTexture() No existe el archivo " << theFilename << ". Se devuelve una textura vacía" << std::endl;
	return anTexture;
}

void AssetManager::DeleteTexture(const std::string& theFilename)
{
	std::map<std::string, sf::Texture*>::iterator it = mTextures.find(theFilename);
	if(it != mTextures.end())
	{
		mApp->mLog << "AssetManager::DeleteTexture() Eliminada textura: " << it->first << std::endl;
		delete it->second;
		mTextures.erase(it); 
	}
}

sf::Font* AssetManager::GetFont(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, sf::Font*>::iterator it = mFonts.begin();
		it != mFonts.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " usando fuente existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	sf::Font* anFont = new sf::Font();

	// Buscamos en la lista de directorios
	for (std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anFont->loadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mFonts[theFilename] = anFont;
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " fuente cargada.\n";
			return mFonts[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anFont->loadFromFile(mApp->GetExecutableDir() + theFilename))
	{
		mFonts[theFilename] = anFont;
		mApp->mLog << "AssetManager::GetFont() " << theFilename << " fuente cargada.\n";
		return mFonts[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetFont() No existe el archivo " << theFilename << ". Se devuelve la fuente por defecto" << std::endl;
	return anFont;
}

void AssetManager::DeleteFont(const std::string& theFilename)
{
	std::map<std::string, sf::Font*>::iterator it = mFonts.find(theFilename);
	if(it != mFonts.end())
	{
		mApp->mLog << "AssetManager::DeleteFont() Eliminada fuente: " << it->first << std::endl;
		delete it->second;
		mFonts.erase(it); 
	}
}

sf::SoundBuffer* AssetManager::GetSoundBuffer(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, sf::SoundBuffer*>::iterator it = mSoundBuffers.begin();
		it != mSoundBuffers.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetSoundBuffer() " << theFilename << " usando sonido existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	sf::SoundBuffer* anSoundBuffer = new sf::SoundBuffer();

	// Buscamos en la lista de directorios
	for (std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anSoundBuffer->loadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mSoundBuffers[theFilename] = anSoundBuffer;
			mApp->mLog << "AssetManager::GetSoundBuffer() " << theFilename << " sonido cargado.\n";
			return mSoundBuffers[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anSoundBuffer->loadFromFile(mApp->GetExecutableDir() + theFilename))
	{
		mSoundBuffers[theFilename] = anSoundBuffer;
		mApp->mLog << "AssetManager::GetSoundBuffer() " << theFilename << " sonido cargado.\n";
		return mSoundBuffers[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetSoundBuffer() No existe el archivo " << theFilename << ". Se devuelve un sonido vacío" << std::endl;
	return anSoundBuffer;
}

void AssetManager::DeleteSoundBuffer(const std::string& theFilename)
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = mSoundBuffers.find(theFilename);
	if(it != mSoundBuffers.end())
	{
		mApp->mLog << "AssetManager::DeleteSoundBuffer() Eliminado sonido: " << it->first << std::endl;
		delete it->second;
		mSoundBuffers.erase(it); 
	}
}

GGE::ConfigReader* AssetManager::GetConfig(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, GGE::ConfigReader*>::iterator it = mConfigFiles.begin();
		it != mConfigFiles.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetConfig() " << theFilename << " usando archivo existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	GGE::ConfigReader* anConfig = new GGE::ConfigReader();

	// Buscamos en la lista de directorios
	for (std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anConfig->Read(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mConfigFiles[theFilename] = anConfig;
			mApp->mLog << "AssetManager::GetConfig() " << theFilename << " archivo cargado.\n";
			return mConfigFiles[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anConfig->Read(mApp->GetExecutableDir() + theFilename))
	{
		mConfigFiles[theFilename] = anConfig;
		mApp->mLog << "AssetManager::GetConfig() " << theFilename << " archivo cargado.\n";
		return mConfigFiles[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetConfig() No existe el archivo " << theFilename << ". Se devuelve una archivo vacío" << std::endl;
	return anConfig;
}

void AssetManager::DeleteConfig(const std::string& theFilename)
{
	std::map<std::string, GGE::ConfigReader*>::iterator it = mConfigFiles.find(theFilename);
	if(it != mConfigFiles.end())
	{
		mApp->mLog << "AssetManager::DeleteConfig() Eliminado archivo: " << it->first << std::endl;
		delete it->second;
		mConfigFiles.erase(it); 
	}
}

sf::Music* AssetManager::GetMusic(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, sf::Music*>::iterator it = mMusic.begin();
		it != mMusic.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetMusic() " << theFilename << " usando archivo existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	sf::Music* anMusic = new sf::Music();

	// Buscamos en la lista de directorios
	for (std::vector<std::string>::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anMusic->openFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mMusic[theFilename] = anMusic;
			mApp->mLog << "AssetManager::GetMusic() " << theFilename << " archivo cargado.\n";
			return mMusic[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anMusic->openFromFile(mApp->GetExecutableDir() + theFilename))
	{
		mMusic[theFilename] = anMusic;
		mApp->mLog << "AssetManager::GetMusic() " << theFilename << " archivo cargado.\n";
		return mMusic[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetMusic() No existe el archivo " << theFilename << ". Se devuelve uno vacío" << std::endl;
	return anMusic;
}

void AssetManager::DeleteMusic(const std::string& theFilename)
{
	std::map<std::string, sf::Music*>::iterator it = mMusic.find(theFilename);
	if(it != mMusic.end())
	{
		mApp->mLog << "AssetManager::DeleteMusic() Eliminada textura: " << it->first << std::endl;
		delete it->second;
		mMusic.erase(it); 
	}
}

GGE::TmxMap* AssetManager::GetTmxMap(const std::string& theFilename)
{
	// Comprobamos si existe el recurso
	for (std::map<std::string, GGE::TmxMap*>::iterator it = mTmxMaps.begin();
		it != mTmxMaps.end(); it++)
	{
		if (it->first == theFilename)
		{
			mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " usando tmx existente" << std::endl;
			return it->second;
		}
	}

	// Si no existe lo cargamos
	GGE::TmxMap* anTmxMap = new GGE::TmxMap();

	// Buscamos en la lista de directorios
	for (std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end(); ++it)
	{
		if(anTmxMap->LoadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mTmxMaps[theFilename] = anTmxMap;
			mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " tmx cargado.\n";
			return mTmxMaps[theFilename];
		}

	}

	// Buscamos en el directorio del ejecutable
	if (anTmxMap->LoadFromFile(mApp->GetExecutableDir() + theFilename))
	{
		mTmxMaps[theFilename] = anTmxMap;
		mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " tmx cargado.\n";
		return mTmxMaps[theFilename];
	}

	// Si no se encuentra la textura devolvemos la dirección de una vacía
	mApp->mLog << "AssetManager::GetTmxMap() No existe el archivo " << theFilename << ". Se devuelve uno vacío" << std::endl;
	return anTmxMap;
}

void AssetManager::DeleteTmxMap(const std::string& theFilename)
{
	std::map<std::string, GGE::TmxMap*>::iterator it = mTmxMaps.find(theFilename);
	if(it != mTmxMaps.end())
	{
		mApp->mLog << "AssetManager::DeleteTmxMap() Eliminado tmx: " << it->first << std::endl;
		delete it->second;
		mTmxMaps.erase(it); 
	}
}

} // Namespace GGE