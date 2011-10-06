/**
 * Contiene la clase App base del engine, pone en funcionamiento el juego.
 *
 * @file app.h
 * @author Adrián Guerra Marrero
 * @date 20110422
 */

#ifndef APP_H
#define APP_H

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <BGE/Core/Core_types.hpp>
#include <BGE/Core/classes/SceneManager.hpp>
#include <BGE/Core/classes/Scene.hpp>
#include <BGE/Core/classes/AssetManager.hpp>

namespace BGE
{
class App
{
	static App* ms_instance;

public:
	// Constantes
	///////////////////////////////////////////////////////////////////////////
	static const unsigned int DEFAULT_VIDEO_WIDTH = 640;
	static const unsigned int DEFAULT_VIDEO_HEIGHT = 480;
	static const unsigned int DEFAULT_VIDEO_BPP = 32;

	// Variables
	///////////////////////////////////////////////////////////////////////////
	/// Título de la ventana
	std::string title;
	/// Ventana de la aplicación
	sf::RenderWindow window;
	/// Modo de video (Width, Height, Bpp)
	sf::VideoMode video_mode;
	/// Opciones de la ventana
	sf::WindowSettings window_settings;
	/// Estilo de la ventana
	unsigned long window_style;
	/// Input manager de la ventana
	const sf::Input& input;
	/// Log de la aplicación
	std::ofstream log;
	/// Puntero a Scene inicial
	Scene* scene;
	/// Puntero al SceneManager
	SceneManager* scene_manager;
	/// Puntero al AssetManager
	AssetManager* asset_manager;

	/**
	 * @brief Devuelve la Instancia única de la clase App
	 */
	static App* Instance();

	/**
	 * @brief Elimina la Instancia de la clase App
	 */
	static void Release();

	/**
	 * Procesa los parámetros pasados por línea de comandos
	 *
	 * @param argc Número de parámetros
	 * @param argv[] Lista de parámetros
	 */
	virtual void ProcessArguments(int argc, char* argv[]);

	/**
	 * Pone en funcionamiento la aplicación. Se encarga de llamar a los métodos
	 * Preinit, Init, loop y CleanUp
	 *
	 * @return Devuel el código de salida de la aplicación
	 */
	int Run(void);

	/**
	 * Devuelve verdadero si la aplicación se está ejecutando
	 *
	 * @return true si la apicación se está ejecutando
	 */
	bool IsRunning(void) const;
	
	void SetFirstScene(Scene* first);
	
	float GetUpdateTime(void) const;

	/**
	 * Para la aplicacion con el código de salida indicado
	 *
	 * @param the_exit_code Código de salida de la aplicación
	 */
	void Quit(int the_exit_code);

	/**
	 * Devuelve la ruta del ejecutable
	 * 
	 * @return devuelve la ruta completa del ejecutable
	 */
	std::string GetExecutableDir(void) const;

protected:
	/**
	 * Método llamado antes del Init() se encarga de establecer configuraciones
	 * de la aplicación
	 */
	void PreInit(void);
	
	/**
	 * Se encarga de inicializar la aplicación
	 * 
	 * @brief Devuelve true si se inicializa correctamente
	 */
	virtual void Init(void);
	
	/**
	 * Lleva el bucle de la aplicación se encarga de mantenerla en ejecución
	 */
	virtual void Loop(void);
	
	/**
	 * Se encarga de la limpieza andes de salir de la aplicacion
	 */
	virtual void Cleanup(void);
	
private:
	/// Código de salida de la aplicación
	int exit_code;
	/// Verdadero si la aplicación se está ejecutando
	bool running;
	/// Archivo de log de la aplicación
	std::string log_file;
	/// Reloj que obtiene el tiempo pasado en cada loop
	sf::Clock update_clock;
	/// Almacena el tiempo pasado en cada bucle
	float update_time;
	/// Almacena la ruta del ejecutable
	std::string executable_dir;

	/**
	 * App Constructor
	 */
	App();

	/**
	 * App Destructor
	 */
	~App();

}; // Class App
} // namespace BGE
#endif // APP_H
