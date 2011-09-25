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
#include <SFML/Graphics.hpp>

#include "types.h"
#include "app.h"

namespace BGE
{
class Scene
{
public:
	/**
	 * Scene Destructor
	 */
	virtual ~Scene();

	/**
	 * Devuelve el identificador único de la escena
	 *
	 * @return BGE::SceneID el ID de la escena
	 */
	SceneID GetID() const;
	
	/**
	 * Devuelve true si el Init() ya ha sido llamado
	 */
	bool IsInitComplete() const;
	
	/**
	 * Devuelve true si la escena está pausada
	 */
	bool IsPaused() const;
	
	/**
	 * Método llamado cuando se activa la escena
	 */
	virtual void Init();
	
	/**
	 * Método virtual que hace un reinicio de la escena
	 */
	virtual void ReInit() = 0;
	
	/**
	 * Método llamado al destruir la escena
	 */
	virtual void DeInit();
	
	/**
	 * Método llamano al pausar la escena
	 */
	virtual void Pause();
	
	/**
	 * Método llamado al salir del pause de la escena
	 */
	virtual void Resume();
	
	/**
	 * Método que recibe los eventos del sistema, llamado por cada evento que se
	 * produce en un ciclo de la aplicación
	 */
	virtual void Events(sf::Event theEvent) = 0;
	
	/**
	 * Método que actualiza la escena, llamado al menos una vez por ciclo
	 */
	virtual void Update(void) = 0;

	/**
	 * Método encargado de dibujar en la escena, llamado en relación a los FPS
	 */
	virtual void Draw(void) = 0;
	
	/**
	 * Devuelve el tiempo pasado desde que se llamo al Init() o desde la última
	 * pausa.
	 */
	float GetElapsedTime() const;
	
	/**
	 * Método que es llamado al eliminar la escena, se ecarga de la limpieza
	 */
	virtual void Cleanup();

protected:
	/// Puntero a la aplicación padre
	App* app;

	/**
	 * Constructor de la escena
	 * 
	 * @param m_id Cadena de texto que establece un identificador único
	 * @param p_app Puntero a la aplicación App
	 */
	Scene(SceneID m_id, App* p_app);

private:
	/// Representa el id único de la escena
	SceneID id;
	/// Comprueba si cleanup debe ser llamado
	bool m_cleanup;
	/// Comprueba si la escena está inicializada
	bool m_init;
	/// Comprueba si la escena está pausada
	bool m_paused;
	/// Reloj para calcular el tiempo pasado
	sf::Clock elapsed_clock;
	/// Total del tiempo pasado desde que el Init() es llamdo
	float elapsed_time;
	/// Reloj para calcular el tiempo em pausa
	sf::Clock paused_clock;
	/// Total del tiempo pausado desde que Init() se llamo
	float paused_time;

	/**
	 * Our copy constructor is private because we do not allow copies of
	 * our Singleton class
	 */
	Scene(const Scene&);  // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	Scene& operator=(const Scene&); // Intentionally undefined


}; // class Scene
} // Namespace BGE

#endif // SCENE_H
