#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID, GGE::App* theApp) :
	GGE::IScene(theID, theApp),
	heroe(theApp),
	mapa(theApp)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// Creamos un directorio donde buscar recursos
	mApp->mAssetManager->AddDirectory("resources/");
	// Establecemos la imagen de nuestro heroe
	heroe.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	// Nuestro heroe es un Sprite Sheet!! Definamos la grilla de imagenes
	heroe.SetGrid(4, 4); // 4 filas y 4 columnas
	// Cambiemos la posición del heroe
	heroe.SetPosition(432, 416);
	// Vamos a cargar el mapa que acabamos de crear
	mapa.Load(mApp->mAssetManager->GetTmxMap("pueblo.tmx"));
	// Vamos a conectar nuestro mapa a nuestro heroe para que la camara lo siga
	mapa.SetScrollParallax(heroe);
}

void SceneMain::ReInit()
{
}

void SceneMain::Events(sf::Event theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed)
	{
		if (theEvent.Key.Code == sf::Key::Escape)
			mApp->Quit(GGE::StatusAppOK);
	}
}

void SceneMain::Update()
{
	// Demosle algo de movilidad
	heroe.Update();
	sf::Vector2f pos;
}

void SceneMain::Draw()
{
	// Color de Fondo
	mApp->mWindow.Clear(sf::Color(200, 200, 200));

	// Lo dibujamos en pantalla
	mapa.Draw();

	// Dibujamos a nuestro heroe
	mApp->mWindow.Draw(heroe);
}

void SceneMain::Cleanup()
{
}