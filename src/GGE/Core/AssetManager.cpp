#include <algorithm>
#include <boost/filesystem.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/AssetManager.hpp>
#include <iostream> // Quitar

namespace GGE
{

AssetManager* AssetManager::ms_instance = 0;

AssetManager::AssetManager()
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

bool AssetManager::AddDirectory(const std::string& directory)
{
	namespace fs = boost::filesystem;

	std::string dir = directory;
	
	if (!(*dir.rbegin() == '/' || *dir.rbegin() == '\\'))
	{
		dir.append("/");
	}

	fs::path path = dir;


	if (!path.is_absolute())
	{
		fs::path root = m_app->GetExecutableDir();
		path = root / path;
	}

	path = fs::system_complete(path);
	
	if (fs::exists(path) && fs::is_directory(path))
	{
		path = fs::canonical(path);
		std::string path_s = path.string();
		std::replace(path_s.begin(), path_s.end(), '\\', '/');

		std::vector<std::string>::const_iterator it;
		for (it = m_directories.begin(); it != m_directories.end(); it++)
		{
			if (path_s == (*it))
			{
				m_app->log << "AssetManager::AddDirectory() Ya existe Dir=\"" << path_s << "\"" << std::endl;
				return false;
			}
		}

		m_app->log << "AssetManager::AddDirectory() Add Dir=\"" << path.string() << "\"" << std::endl;
		m_directories.push_back(path_s);
		return true;
	}
	else
	{
		m_app->log << "[WARN] AssetManager::AddDirectory() No Existe Dir=\"" 
			<< path.string() << "\"" << std::endl;
		return false;
	}
}

void AssetManager::RemoveDirectory(const std::string& directory)
{

}

} // namespace GGE