/**
 * Provides the GGE Core typedef's and forward class declarations.
 *
 * @file include/GGE/Core/Core_types.hpp
 * @author Ryan Lindeman
 * @date 20100710 - Initial Release
 * @date 20110118 - Add types used by ConfigReader.
 * @date 20110125 - Fix string compare issues
 * @date 20110127 - Changed name from GGE_types.hpp to Core_types.hpp
 * @date 20110218 - Added ConfigAsset to forward declarations
 * @date 20110523 - Readded NameValue types
 * @date 20110611 - Add new logging classes and new Log macros
 * @date 20110627 - Removed extra , from enum and ; from namespace
 */
#ifndef   CORE_TYPES_HPP
#define   CORE_TYPES_HPP
 
#include <map>
#include <string>
#include <vector>
#include <GGE/Config.hpp>

namespace GGE
{
/// Status Enumeration for Status Return values
enum StatusType {
	// Values from -99 to 99 are common Error and Good status responses
	StatusAppMissingAsset = -4,  ///< Application failed due to missing asset file
	StatusAppStackEmpty   = -3,  ///< Application States stack is empty
	StatusAppInitFailed   = -2,  ///< Application initialization failed
	StatusError           = -1,  ///< General error status response
	StatusAppOK           =  0,  ///< Application quit without error
	StatusNoError         =  0,  ///< General no error status response
	StatusFalse           =  0,  ///< False status response
	StatusTrue            =  1,  ///< True status response
	StatusOK              =  1   ///< OK status response

	// Values from +-100 to +-199 are reserved for File status responses
};


// Forward declare GGE classes provided
class App;
class ConfigReader;
class Scene;
class SceneManager;
class AssetManager;
class Camera;
class Clock;
class ObjectScene;
class Sprite;
class Text;
class Shape;
class RectangleShape;
class CircleShape;
class ConvexShape;
class Actor;
class RectCollision;

/// Foward declare TmxMap
class TmxMap;
class TmxLayer;
class TmxObject;
class TmxObjectGroup;
class TmxProperties;
class TmxTileset;

// Foward declare Map


/// Animaciones
struct Animation
{
	GGE::Uint32 fps;
	GGE::Uint32 firstFrame;
	GGE::Uint32 lastFrame;
	bool flipX;
	bool flipY;
	Animation() { fps = 20; firstFrame = 1; lastFrame = 1; flipX = false; flipY = false; }
};
 
/// Declare Action ID typedef which is used for identifying Action objects
typedef std::string typeActionID;

/// Declare Asset ID typedef which is used for identifying Asset objects
typedef std::string typeAssetID;

/// Declare State ID typedef which is used for identifying State objects
typedef std::string SceneID;

/// Declare NameValue typedef which is used for config section maps
typedef std::map<const std::string, const std::string> typeNameValue;

/// Declare NameValueIter typedef which is used for name,value pair maps
typedef std::map<const std::string, const std::string>::iterator typeNameValueIter;

} // namespace GGE
#endif // CORE_TYPES_HPP
