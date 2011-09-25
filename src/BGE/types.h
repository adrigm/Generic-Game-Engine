/**
 * Definición de tipos del espacio de nombre BGE
 *
 * @file types.h
 * @author Adrián Guerra Marrero
 * @date 20110422 - Initial Release
 */

#ifndef TYPES_H
#define TYPES_H

#include <string>

namespace BGE
{
	
// Tipo de dato que representa el ID de una Escena
typedef std::string SceneID;

/// Status Enumeration for Status Return values
enum StatusType
{
	// Values from -99 to 99 are common Error and Good status responses
	StatusAppMissingAsset = -4, ///< Application failed due to missing asset file
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

// Forwards Declarations
class App;
class SceneManager;
class Scene;

} // Namespace BGE

#endif // TYPES_H
