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

#define INFO_LEVEL   0  ///< Defines the value for GGE::SeverityInfo
#define WARN_LEVEL   1  ///< Defines the value for GGE::SeverityWarning
#define ERROR_LEVEL  2  ///< Defines the value for GGE::SeverityError
#define FATAL_LEVEL  3  ///< Defines the value for GGE::Severity
#define NO_LOG_LEVEL 4  ///< Defines the value for no logging

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
  class AssetManager;
  class SceneManager;
  class IScene;
  class Actor;
 
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