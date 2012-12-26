////////////////////////////////////////////////////////////
//
// GGE - Generic Game Engine
// Copyright (C) 2011-2012 Adrián Guerra (adrigm@razonartificial.com)
//
////////////////////////////////////////////////////////////

#include <GGE/Core/App.hpp>

int main(int argc, char** argv)
{
	// Establecemos un código de error
	GGE::Uint32 anExitCode = GGE::StatusNoError;

	// Creamos la aplicación
	GGE::App *anApp = GGE::App::Instance();

	// Procesamos los argumentos
	anApp->RegisterExecutableDir(argc, argv);

	// Ponemos en marcha la aplicación
	anExitCode = anApp->Run();

	// Eliminamos la aplicación
	GGE::App::Release();

	// Anulamos el puntero
	anApp = 0;

	// Retornamos el código devuelto por la aplicación
	return anExitCode;
}