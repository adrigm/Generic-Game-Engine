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

bool AssetManager::AddDirectory(const std::string& directory)
{
	std::string dir = GetAbsolutePath(directory);

	if (dir != "")
	{
		std::vector<std::string>::const_iterator it;
		for (it = m_directories.begin(); it != m_directories.end(); it++)
		{
			if (dir == (*it))
			{
				m_app->log << "AssetManager::AddDirectory() ya existe dir=\"" << dir
					<< "\"" << std::endl;
				return false;
			}
		}

		m_directories.push_back(dir);
		m_app->log << "AssetManager::AddDirectory() add dir=\"" << dir
			<< "\"" << std::endl;

		return true;
	}
	else
	{
		return false;
	}
}

bool AssetManager::RemoveDirectory(const std::string& directory)
{
	std::string dir = this->GetAbsolutePath(directory);

	if (dir != "")
	{
		std::vector<std::string>::iterator it;
		for (it = m_directories.begin(); it != m_directories.end(); it++)
		{
			if (dir == (*it))
			{
				m_directories.erase(it);
				m_app->log << "AssetManager::RemoveDirectory() eliminado  dir=\"" << dir
					<< "\"" << std::endl;
				return true;
			}
		}

		m_app->log << "AssetManager::RemoveDirectory() no registrado  dir=\"" << dir
			<< "\"" << std::endl;
		return false;
	}
	else
	{
		return false;
	}
}

} // namespace GGE