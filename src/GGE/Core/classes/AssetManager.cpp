#include <GGE/Core/classes/AssetManager.hpp>

 
namespace GGE
{

AssetManager::AssetManager(App* theApp) :
	mApp(theApp),
	mDirectories(),
	mImages(),
	mConfigFiles()
{
}

AssetManager::~AssetManager()
{
	mImages.clear();
	mConfigFiles.clear();
	mDirectories.clear();
}

const sf::Image& AssetManager::GetImage( const std::string& theFilename )
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::Image>::const_iterator it = mImages.begin();
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
	for( std::map<std::string, sf::Image>::const_iterator it = mImages.begin();
		 it != mImages.end(); 
		 ++it)
	{
		if( &image == &it->second )
		{
			mImages.erase( it );
						return;
		}
	}
}

void AssetManager::DeleteImage( const std::string& theFilename )
{
	std::map<std::string, sf::Image>::const_iterator it = mImages.find( theFilename );
	if( it != mImages.end() )
		mImages.erase( it );
}

void AssetManager::AddDirectory( const std::string& directory )
{
	// Check whether the path already exists
	for( std::vector<std::string>::const_iterator it  = mDirectories.begin();
		 it != mDirectories.end();
		++it )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			return;
	}

	// insert the directory
	mDirectories.push_back( directory );
}

void AssetManager::RemoveDirectory( const std::string& directory )
{
	for( std::vector<std::string>::const_iterator it  = mDirectories.begin();
		 it != mDirectories.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = mDirectories.erase( it );
		else
			++it;
	}
}

const ConfigReader& AssetManager::GetConfigFile(const std::string& theFilename)
{
	// Check, whether the image already exists
	for( std::map<std::string, ConfigReader*>::const_iterator it = mConfigFiles.begin();
		 it != mConfigFiles.end(); 
		 ++it)
	{
		if( theFilename == it->first )
		{
			mApp->mLog << "AssetManager::GetConfigFile(): " << theFilename << " ya existe" << std::endl;
			return *it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	ConfigReader* anConfigFile = new ConfigReader();
	anConfigFile->RegisterApp(mApp);

	// Search project's main directory
	if( anConfigFile->Read(theFilename))
	{
		mConfigFiles[theFilename] = anConfigFile;
		mApp->mLog << "AssetManager::GetConfigFile(): " << theFilename << std::endl;
		return *mConfigFiles[theFilename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = mDirectories.begin();
		 it != mDirectories.end();
		 ++it )
	{
		if( anConfigFile->Read( (*it) + theFilename ) )
		{
			mConfigFiles[theFilename] = anConfigFile;
			mApp->mLog << "AssetManager::GetConfigFile(): " << theFilename << std::endl;
			return *mConfigFiles[theFilename];
		}

	}

	mApp->mLog << "AssetManager::GetConfigFile() "<< theFilename 
		<< " No Encontrado, se crea uno vacío" << std::endl;
	mConfigFiles[theFilename] = anConfigFile;
	return *mConfigFiles[theFilename];
}

void AssetManager::DeleteConfigFile(const std::string& theFilename)
{
	std::map<std::string, ConfigReader*>::const_iterator it = mConfigFiles.find(theFilename);
	if(it != mConfigFiles.end())
	{
		delete it->second;
		mConfigFiles.erase(it);
		mApp->mLog << "AssetManager::DeleteConfigFile() " << theFilename << std::endl;
	}
}


} // namespace GGE