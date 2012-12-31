#ifndef GGE_Asset_MANAGER_HPP
#define GGE_Asset_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <GGE/Core/Export.hpp>

namespace GGE
{

class GGE_CORE_API AssetManager
{
	static AssetManager* ms_instance;

public:
	static AssetManager* Instance();

	static void Release();

	bool AddDirectory(const std::string& directory);

	bool RemoveDirectory(const std::string& directory);

protected:
	GGE::App* m_app;

private:
	std::vector<std::string> m_directories;

	AssetManager();

	std::string GetAbsolutePath(const std::string& directory) const;

	virtual ~AssetManager();

}; // class AssetManager

} // namespace GGE

#endif // GGE_Asset_MANAGER_HPP