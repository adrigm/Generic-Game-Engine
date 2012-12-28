////////////////////////////////////////////////////////////
//
// GGE - Generic Game Engine
// Copyright (C) 2011-2012 Adrián Guerra (adrigm@razonartificial.com)
//
////////////////////////////////////////////////////////////

#include <GGE/Core/App.hpp>
#include "SceneMain.hpp"

int main(int argc, char** argv)
{
	// Establecemos un código de error
	GGE::Uint32 anExitCode = GGE::StatusNoError;

	// Creamos la aplicación
	GGE::App *anApp = GGE::App::Instance();

	// Registramos la ruta del ejecutable
	anApp->RegisterExecutableDir(argc, argv);

	// Establecemos la escena inicial
	anApp->SetFirstScene(new SceneMain("Main"));

	// Cambiamos el título a la ventana
	anApp->SetTitle("Test GGE");

	// Ponemos en marcha la aplicación
	anExitCode = anApp->Run();

	// Eliminamos la aplicación
	GGE::App::Release();

	// Anulamos el puntero
	anApp = 0;

	// Retornamos el código devuelto por la aplicación
	return anExitCode;
}