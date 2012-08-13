#include <GGE/Core/AssetManager.hpp>

 
namespace GGE
{

AssetManager* AssetManager::ms_instance = 0;

AssetManager::AssetManager() :
	mApp(NULL),
	mDirectories(),
	mImages(),
	mConfigFiles()
{
	mApp = GGE::App::Instance();
	mApp->mLog << "AssetManager::ctor()" << std::endl;
}

AssetManager::~AssetManager()
{
	mImages.clear();
	mConfigFiles.clear();
	mDirectories.clear();

	mApp->mLog << "AssetManager::dtor()" << std::endl;
}

AssetManager* AssetManager::Instance()
{
	if(ms_instance == 0){
		ms_instance = new AssetManager();
	}
	return ms_instance;
}

void AssetManager::Release()
{
	if(ms_instance){
		delete ms_instance;
	}
	ms_instance = 0;
}

void AssetManager::AddDirectory(const std::string& directory)
{
	// Check whether the path already exists
	for( std::vector<std::string>::iterator it  = mDirectories.begin();
		 it != mDirectories.end();
		++it )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			return;
	}
	
	// TODO: Comprobar si el último caracter del directorio es / o \

	// insert the directory
	mDirectories.push_back( directory );
	mApp->mLog << "AssetManager::AddDirectory() Dir=" << directory << std::endl;
}

void AssetManager::RemoveDirectory( const std::string& directory )
{
	for( std::vector<std::string>::iterator it  = mDirectories.begin();
		 it != mDirectories.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = mDirectories.erase( it );
		else
			++it;
	}
}

sf::Image& AssetManager::GetImage( const std::string& theFilename )
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::Image>::iterator it = mImages.begin();
		 it != mImages.end(); 
		 ++it)
	{
		if(theFilename == it->first)
		{
			mApp->mLog << "AssetManager::GetImage() " << theFilename << " using existing image.\n";
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	sf::Image image;

	// Search project's main directory
	if( image.LoadFromFile(mApp->GetExecutableDir() + theFilename ) )
	{
		mImages[theFilename] = image;
		mApp->mLog << "AssetManager::GetImage() " << theFilename << " loading image.\n";
		return mImages[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( image.LoadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mImages[theFilename] = image;
			mApp->mLog << "AssetManager::GetImage() " << theFilename << " loading image.\n";
			return mImages[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetImage(): Image was not found. It is filled with an empty image.\n";
	mImages[theFilename] = image;
	return mImages[theFilename];
}

void AssetManager::DeleteImage( const sf::Image& image )
{
	for(std::map<std::string, sf::Image>::iterator it = mImages.begin();
		 it != mImages.end(); 
		 ++it)
	{
		if( &image == &it->second )
		{
			mImages.erase(it);
			return;
		}
	}
}

void AssetManager::DeleteImage(const std::string& theFilename)
{
	std::map<std::string, sf::Image>::iterator it = mImages.find( theFilename );
	if( it != mImages.end() )
		mImages.erase( it );
}

sf::Font& AssetManager::GetFont(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::Font>::iterator it = mFonts.begin();
		 it != mFonts.end(); 
		 ++it)
	{
		if(theFilename == it->first)
		{
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " using existing Font.\n";
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	sf::Font font;

	// Search project's main directory
	if( font.LoadFromFile(mApp->GetExecutableDir() + theFilename ) )
	{
		mFonts[theFilename] = font;
		mApp->mLog << "AssetManager::GetFont() " << theFilename << " loading Font.\n";
		return mFonts[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( font.LoadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mFonts[theFilename] = font;
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " loading Font.\n";
			return mFonts[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetFont(): Font was not found. It is filled with an empty image.\n";
	mFonts[theFilename] = sf::Font::GetDefaultFont();
	return mFonts[theFilename];
}

void AssetManager::DeleteFont(const std::string& theFilename)
{
	std::map<std::string, sf::Font>::iterator it = mFonts.find( theFilename );
	if( it != mFonts.end() )
		mFonts.erase( it );
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::SoundBuffer>::iterator it = mSounds.begin();
		 it != mSounds.end(); 
		 ++it)
	{
		if(theFilename == it->first)
		{
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " using existing Font.\n";
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	sf::SoundBuffer sound;

	// Search project's main directory
	if( sound.LoadFromFile(mApp->GetExecutableDir() + theFilename ) )
	{
		mSounds[theFilename] = sound;
		mApp->mLog << "AssetManager::GetFont() " << theFilename << " loading Font.\n";
		return mSounds[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( sound.LoadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mSounds[theFilename] = sound;
			mApp->mLog << "AssetManager::GetFont() " << theFilename << " loading Font.\n";
			return mSounds[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetFont(): Font was not found. It is filled with an empty image.\n";
	mSounds[theFilename] = sound;
	return mSounds[theFilename];
}

void AssetManager::DeleteSoundBuffer(const std::string& theFilename)
{
	std::map<std::string, sf::SoundBuffer>::iterator it = mSounds.find( theFilename );
	if( it != mSounds.end() )
		mSounds.erase( it );
}

sf::Music* AssetManager::GetMusic(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::Music*>::iterator it = mMusic.begin();
		 it != mMusic.end(); 
		 ++it)
	{
		if(theFilename == it->first)
		{
			mApp->mLog << "AssetManager::GetMusic() " << theFilename << " using existing Music.\n";
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	sf::Music* music = new sf::Music();

	// Search project's main directory
	if( music->OpenFromFile(mApp->GetExecutableDir() + theFilename ) )
	{
		mMusic[theFilename] = music;
		mApp->mLog << "AssetManager::GetMusic() " << theFilename << " loading Music.\n";
		return mMusic[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( music->OpenFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mMusic[theFilename] = music;
			mApp->mLog << "AssetManager::GetMusic() " << theFilename << " loading Music.\n";
			return mMusic[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetMusic(): Font was not found. It is filled with an empty music.\n";
	mMusic[theFilename] = music;
	return mMusic[theFilename];
}

void AssetManager::DeleteMusic(const std::string& theFilename)
{
	std::map<std::string, sf::Music*>::iterator it = mMusic.find(theFilename);
	if(it != mMusic.end())
	{
		delete it->second;
		mMusic.erase(it);
		mApp->mLog << "AssetManager::DeleteConfigFile() ID=" << theFilename << std::endl;
	}
}

ConfigReader& AssetManager::GetConfigFile(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, ConfigReader*>::iterator it = mConfigFiles.begin();
		 it != mConfigFiles.end(); 
		 ++it)
	{
		if( theFilename == it->first )
		{
			mApp->mLog << "AssetManager::GetConfigFile() ID=" << theFilename << " ya existe" << std::endl;
			return *it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	ConfigReader* anConfigFile = new ConfigReader();

	// Search project's main directory
	if( anConfigFile->Read(mApp->GetExecutableDir() + theFilename))
	{
		mConfigFiles[theFilename] = anConfigFile;
		mApp->mLog << "AssetManager::GetConfigFile() ID=" << theFilename << std::endl;
		return *mConfigFiles[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( anConfigFile->Read(mApp->GetExecutableDir() + (*it) + theFilename ) )
		{
			mConfigFiles[theFilename] = anConfigFile;
			mApp->mLog << "AssetManager::GetConfigFile() ID=" << theFilename << std::endl;
			return *mConfigFiles[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetConfigFile() ID="<< theFilename 
		<< " No Encontrado, se crea uno vacío" << std::endl;
	mConfigFiles[theFilename] = anConfigFile;
	return *mConfigFiles[theFilename];
}

void AssetManager::DeleteConfigFile(const std::string& theFilename)
{
	std::map<std::string, ConfigReader*>::iterator it = mConfigFiles.find(theFilename);
	if(it != mConfigFiles.end())
	{
		delete it->second;
		mConfigFiles.erase(it);
		mApp->mLog << "AssetManager::DeleteConfigFile() ID=" << theFilename << std::endl;
	}
}

void AssetManager::Cleanup()
{
	// Eliminamos todas las imagenes
	std::map<std::string, sf::Image>::iterator itImages = mImages.begin();
	while (itImages != mImages.end())
	{
		mApp->mLog << "AssetManager::Cleanup() Eliminada imagen con ID=" << itImages->first << std::endl;
		mImages.erase(itImages++);
	}

	// Eliminamos todas las tipografias
	std::map<std::string, sf::Font>::iterator itFonts = mFonts.begin();
	while (itFonts != mFonts.end())
	{
		mApp->mLog << "AssetManager::Cleanup() Eliminada Font con ID=" << itFonts->first << std::endl;
		mFonts.erase(itFonts++);
	}

	// Eliminamos todos los sonidos
	std::map<std::string, sf::SoundBuffer>::iterator itSounds = mSounds.begin();
	while (itSounds != mSounds.end())
	{
		mApp->mLog << "AssetManager::Cleanup() Eliminado Sonido con ID=" << itSounds->first << std::endl;
		mSounds.erase(itSounds++);
	}

	// Eliminamos todas las Configuraciones
	std::map<std::string, ConfigReader*>::iterator itConfig = mConfigFiles.begin();
	while (itConfig != mConfigFiles.end())
	{
		//delete itConfig->second;
		mApp->mLog << "AssetManager::Cleanup() Eliminado ConfigFile con ID=" 
			<< itConfig->first << std::endl;
		mConfigFiles.erase(itConfig++);
	}

	// Eliminamos todas la Musica
	std::map<std::string, sf::Music*>::iterator itMusic = mMusic.begin();
	while (itMusic != mMusic.end())
	{
		//delete itConfig->second;
		mApp->mLog << "AssetManager::Cleanup() Eliminado ConfigFile con ID=" 
			<< itMusic->first << std::endl;
		mMusic.erase(itMusic++);
	}

	mApp->mLog << "AssetManager::Cleanup() Terminado" << std::endl;
}

GGE::TmxMap& AssetManager::GetTmxMap(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, GGE::TmxMap>::iterator it = mTmxMap.begin();
		 it != mTmxMap.end(); 
		 ++it)
	{
		if(theFilename == it->first)
		{
			mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " using existing TmxMap.\n";
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	GGE::TmxMap map;

	// Search project's main directory
	if( map.LoadFromFile(mApp->GetExecutableDir() + theFilename ) )
	{
		mTmxMap[theFilename] = map;
		mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " loading TmxMap.\n";
		return mTmxMap[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( map.LoadFromFile(mApp->GetExecutableDir() + (*it) + theFilename))
		{
			mTmxMap[theFilename] = map;
			mApp->mLog << "AssetManager::GetTmxMap() " << theFilename << " loading TmxMap.\n";
			return mTmxMap[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetTmxMap(): TmxMap was not found. It is filled with an empty image.\n";
	mTmxMap[theFilename] = map;
	return mTmxMap[theFilename];
}

void AssetManager::DeleteTmxMap(const std::string& theFilename)
{
	std::map<std::string, GGE::TmxMap>::iterator it = mTmxMap.find( theFilename );
	if( it != mTmxMap.end() )
		mTmxMap.erase( it );
}


} // namespace GGE
