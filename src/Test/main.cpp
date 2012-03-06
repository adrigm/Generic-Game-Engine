/**
 * Archivo de entrada al proyecto, carga y da el control al engine GGE
 * 
 * @file main.cpp
 * @author Adrián Guerra Marrero
 * @date 20110422 - Initial Release
 */

#include <GGE/Core/App.hpp>
#include "SceneMain.hpp"

int main(int argc, char* argv[])
{	
	// Establecemos el código de salida por defecto
	int anExitCode = GGE::StatusNoError;
	
	// Creamos la aplicación
	GGE::App* anApp = GGE::App::Instance();
	
	// Procesamos parámetros pasados por línea de comandos
	anApp->ProcessArguments(argc, argv);

	// Establecemos la escena inicial del juego
	anApp->SetFirstScene(new SceneMain("Main"));
	
	// Ejecutamos la aplicación
	anExitCode = anApp->Run();
	
	// Eliminamos la aplicación
	GGE::App::Release();
	anApp = 0;
	
	// Devolvemos el código de salida
	return anExitCode;
}