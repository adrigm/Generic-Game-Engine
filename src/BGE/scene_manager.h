#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <SFML/System.hpp>
#include "types.h"
#include "scene.h"

namespace BGE
{

class SceneManager
{
	static SceneManager* ms_instance;

public:
	// Guarda el id de la próxima escena actica
	SceneID next_scene;

	static SceneManager* Instance();
	static void Release();

	/**
	 * Añade una escena a la pila de escenas inactivas
	 *
	 * Solo añade una escena a la pila, no la inicializa
	 *
	 * @param a_scene Puntero a la escena que vamos a añadir
	 */
	void AddScene(Scene *a_scene);


	/**
	 * Establece la escena indicada como activa
	 *
	 * Establece la escena como activa si se encuentra en la pila y llama a su
	 * Init() si no ha sido llamado. Cambia la escena al final del ciclo
	 *
	 * @param id_scene Cadena única que identifica a la escena
	 */
	void SetActiveScene(SceneID id_scene);

	/**
	 * Elimina una escena de la pila, no puede ser la escena activa
	 *
	 * Se encarga de llamar a su método Cleanup y de eliminarla de la memoria
	 *
	 * @param id_scene Cadena única que identifica a la escena
	 */
	void RemoveScene(SceneID id_scene);

	/**
	 * Elimina todas las escenas inactivas
	 */
	void RemoveAllInactiveScene();


	/**
	 * Cambia la escena activa inmediatamente. USAR SetActiveScene() para
	 * cambiar de escena
	 *
	 * @param id_scene ID de la escena a cambiar
	 */
	void ChangeScene(SceneID id_scene);

	/**
	 * Llama el método Event() de la escena activa
	 *
	 * @param a_event representa a un evento del sistema
	 */
	void EventScene(sf::Event a_event);

	/**
	 * Llama el método Draw() de la escena activa
	 */
	void DrawScene();

	/**
	 * Llama al método Update() de la escena activa
	 */
	void UpdateScene();

	/**
	 * Registra la aplicación para acceder al log
	 */
	void RegisterApp(App* p_app)
	{
		app = p_app;
	}

private:
	friend class App;
	/// Escena actualmente activa
	Scene* active_scene;
	// Lista de escenas inacticas
	std::vector<Scene*> inactives_scenes;
	// Puntero a la aplicación
	App* app;

	SceneManager();
	~SceneManager();
	
	/**
	 * Elimina todas las escenas de la pila.
	 *
	 * Elimina todas las escenas incluso la escena activa, se encarga de llamar
	 * a los métodos Cleanup() de las escenas y de eleminarlas de la memoria
	 */
	void RemoveAllScene();

}; // Class SceneManager

} // Namespace BGE

#endif // SCENEMANAGER_H
