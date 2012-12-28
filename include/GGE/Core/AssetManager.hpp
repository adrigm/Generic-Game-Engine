#ifndef GGE_Asset_MANAGER_HPP
#define GGE_Asset_MANAGER_HPP

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

	/**
	 * AssetManager copy constructor is private because we do not allow copies of
	 * our Singleton class
	*/
	AssetManager(const AssetManager&);               // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	AssetManager& operator=(const AssetManager&);    // Intentionally undefined
}; // class AssetManager

} // namespace GGE

#endif // GGE_Asset_MANAGER_HPP