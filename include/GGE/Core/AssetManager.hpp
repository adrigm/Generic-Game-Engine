#ifndef GGE_Asset_MANAGER_HPP
#define GGE_Asset_MANAGER_HPP

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

private:


	AssetManager();
	virtual ~AssetManager();

}; // class AssetManager

} // namespace GGE

#endif // GGE_Asset_MANAGER_HPP