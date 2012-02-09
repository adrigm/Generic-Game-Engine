/**
 * Clase abstracta que representa a una escena cualquierda de un juego todas
 * las escenas deben de heredar de ésta.
 *
 * @file scene.h
 * @author Adrián Guerra Marrero
 * @date 20110422 - Initial Release
 */

#ifndef SCENE_H
#define SCENE_H

#include <cassert>

#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/App.hpp>

namespace GGE
{
class IScene
{
public:
	/**
	 * Scene Destructor
	 */
	virtual ~IScene();

	/**
	 * Devuelve el identificador único de la escena
	 *
	 * @return GGE::SceneID el ID de la escena
	 */
	const SceneID GetID() const;
	
	/**
	 * Devuelve true si el Init() ya ha sido llamado
	 */
	const bool IsInitComplete() const;
	
	/**
	 * Devuelve true si la escena está pausada
	 */
	const bool IsPaused() const;
	
	/**
	 * Método llamado cuando se activa la escena
	 */
	virtual void Init();

	/**
	 * Método llamado para reiniciar la escena
	 */
	virtual void ReInit();

	/**
	 * Método llamano al pausar la escena
	 */
	virtual void Pause();
	
	/**
	 * Método llamado al salir del pause de la escena
	 */
	virtual void Resume();

	/**
	 * Comprueba si el método Cleanup(); debe ser llamado
	 */
	void HandleCleanup(void);
	
	/**
	 * Método que es llamado al eliminar la escena, se ecarga de la limpieza
	 */
	virtual void Cleanup();

	/**
	 * Método que recibe los eventos del sistema, llamado por cada evento que se
	 * produce en un ciclo de la aplicación
	 */
	virtual void Events(sf::Event TheEvent) = 0;
	
	/**
	 * Método que actualiza la escena, llamado al menos una vez por ciclo
	 */
	virtual void Update(void) = 0;

	/**
	 * Método encargado de dibujar en la escena, llamado en relación a los FPS
	 */
	virtual void Draw(void) = 0;

protected:
	/// Puntero a la aplicación padre
	App* mApp;

	/**
	 * Constructor de la escena
	 * 
	 * @param m_id Cadena de texto que establece un identificador único
	 * @param p_app Puntero a la aplicación App
	 */
	IScene(SceneID theID, App* theApp);

private:
	/// Representa el id único de la escena
	const SceneID mID;
	/// Comprueba si cleanup debe ser llamado
	bool mCleanup;
	/// Comprueba si la escena está inicializada
	bool mInit;
	/// Comprueba si la escena está pausada
	bool mPaused;

	/**
	 * Our copy constructor is private because we do not allow copies of
	 * our Singleton class
	 */
	IScene(const IScene&);  // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	IScene& operator=(const IScene&); // Intentionally undefined


}; // class Scene
} // Namespace GGE

#endif // SCENE_H
