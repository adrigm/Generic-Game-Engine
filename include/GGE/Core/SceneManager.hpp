#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/IScene.hpp>

namespace GGE
{

class SceneManager
{

public:
	SceneManager(App* theApp);
	~SceneManager();

	/**
	 * Añade una escena a la pila de escenas inactivas
	 *
	 * Solo añade una escena a la pila, no la inicializa
	 *
	 * @param a_scene Puntero a la escena que vamos a añadir
	 */
	void AddScene(IScene* theScene);


	/**
	 * Establece la escena indicada como activa
	 *
	 * Establece la escena como activa si se encuentra en la pila y llama a su
	 * Init() si no ha sido llamado. Cambia la escena al final del ciclo
	 *
	 * @param id_scene Cadena única que identifica a la escena
	 */
	void SetActiveScene(SceneID theSceneID);

	/**
	 * Elimina una escena de la pila, no puede ser la escena activa
	 *
	 * Se encarga de llamar a su método Cleanup y de eliminarla de la memoria
	 *
	 * @param id_scene Cadena única que identifica a la escena
	 */
	void RemoveScene(SceneID theSceneID);

	/**
	 * Elimina todas las escenas inactivas
	 */
	void RemoveAllInactiveScene();

	/**
	 * Llama el método Event() de la escena activa
	 *
	 * @param a_event representa a un evento del sistema
	 */
	void EventScene(sf::Event theEvent);

	/**
	 * Llama el método Draw() de la escena activa
	 */
	void DrawScene();

	/**
	 * Llama al método Update() de la escena activa
	 */
	void UpdateScene();

	bool HandleChangeScene();

protected:
	// Puntero a la aplicación
	App* mApp;

private:
	// Declaramos la clase App friend
	friend class App;
	/// Escena actualmente activa
	IScene* mActiveScene;
	/// Próxima escena actica
	SceneID mNextScene;
	// Lista de escenas inacticas
	std::map<SceneID, IScene*> mInactivesScenes;
	
	/**
	 * Cambia la escena activa inmediatamente. USAR SetActiveScene() para
	 * cambiar de escena
	 *
	 * @param id_scene ID de la escena a cambiar
	 */
	void ChangeScene(SceneID theSceneID);
	
	/**
	 * Elimina todas las escenas de la pila.
	 *
	 * Elimina todas las escenas incluso la escena activa, se encarga de llamar
	 * a los métodos Cleanup() de las escenas y de eleminarlas de la memoria
	 */
	void RemoveAllScene();

	/**
	 * App copy constructor is private because we do not allow copies of
	 * our Singleton class
	 */
	SceneManager(const SceneManager&);                 // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	SceneManager& operator=(const SceneManager&);      // Intentionally undefined

}; // Class SceneManager

} // Namespace GGE

#endif // SCENEMANAGER_H
