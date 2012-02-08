/**
 * Contiene la clase App base del engine, pone en funcionamiento el juego.
 *
 * @file app.h
 * @author Adrián Guerra Marrero
 * @date 20110422
 */

#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/classes/IScene.hpp>
#include <GGE/Core/classes/SceneManager.hpp>
#include <GGE/Core/classes/AssetManager.hpp>

namespace GGE
{
class App
{
public:
	// Constantes
	///////////////////////////////////////////////////////////////////////////
	static const unsigned int DEFAULT_VIDEO_WIDTH = 640;
	static const unsigned int DEFAULT_VIDEO_HEIGHT = 480;
	static const unsigned int DEFAULT_VIDEO_BPP = 32;

	// Variables
	///////////////////////////////////////////////////////////////////////////
	/// Título de la ventana
	std::string mTitle;
	/// Ventana de la aplicación
	sf::RenderWindow mWindow;
	/// Modo de video (Width, Height, Bpp)
	sf::VideoMode mVideoMode;
	/// Opciones de la ventana
	sf::WindowSettings mWindowSettings;
	/// Estilo de la ventana
	unsigned long mWindowStyle;
	/// Input manager de la ventana
	const sf::Input& mInput;
	/// Log de la aplicación
	std::ofstream mLog;
	/// Puntero a Scene inicial
	IScene* mScene;
	/// Puntero al SceneManager
	SceneManager* mSceneManager;
	/// Puntero al AssetManager
	AssetManager* mAssetManager;

	App(const std::string TheTitle = "GGE Application");

	virtual ~App();

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

	void SetFirstScene(IScene* theScene);

protected:
	/**
	 * Método llamado antes del Init() se encarga de establecer configuraciones
	 * de la aplicación
	 */
	void PreInit(void);
	
	/**
	 * Se encarga de inicializar la aplicación
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
	int mExitCode;
	/// Verdadero si la aplicación se está ejecutando
	bool mRunning;
	/// Archivo de log de la aplicación
	std::string mLogFile;
	/// Reloj que obtiene el tiempo pasado en cada loop
	sf::Clock mUpdateClock;
	/// Almacena el tiempo pasado en cada bucle
	float mUpdateTime;
	/// Almacena la ruta del ejecutable
	std::string mExecutableDir;

	/**
	 * App copy constructor is private because we do not allow copies of
	 * our Singleton class
	 */
	App(const App&);                 // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	App& operator=(const App&);      // Intentionally undefined

}; // Class App
} // namespace GGE
#endif // APP_H
