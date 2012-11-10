#include <GGE/Core.hpp>
#include "SceneMain.hpp"

int main(int argc, char* argv[])
{
	// Establecemos el código de salida por defecto
	GGE::Int16 anExitCode = GGE::StatusNoError;

	// Creamos la aplicación
	GGE::App *anApp = GGE::App::Instance();

	// Procesamos los argumentos
	anApp->ProcessArguments(argc, argv);

	// Establecemos la escena inicial
	anApp->SetFirstScene(new SceneMain("Main"));

	//Ejecutamos la aplicación
	anExitCode = anApp->Run();

	// Eliminamos la aplicación
	GGE::App::Release();
	anApp = 0;

	// Devolvemos el código de salida
	return anExitCode;
}