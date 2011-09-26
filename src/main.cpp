/**
 * Archivo de entrada al proyecto, carga y da el control al engine BGE
 * 
 * @file main.cpp
 * @author Adrián Guerra Marrero
 * @date 20110422 - Initial Release
 */

#include "BGE/BGE.h"
#include "scene_start.h"

int main(int argc, char* argv[])
{	
	// Establecemos el código de salida por defecto
	int exit_code = BGE::StatusNoError;
	
	// Creamos la aplicación
	BGE::App* app = BGE::App::Instance();
	
	// Procesamos parámetros pasados por línea de comandos
	app->ProcessArguments(argc, argv);
	
	// Creamos la escena inicial
	BGE::Scene* a_scene = new SceneStart("Start", app);
	
	// La pasamos a la App como primera escena
	app->SetFirstScene(a_scene);
	
	// Ejecutamos la aplicación
	exit_code = app->Run();
	
	// Eliminamos la aplicación
	BGE::App::Release();
	
	// Devolvemos el código de salida
	return exit_code;
}