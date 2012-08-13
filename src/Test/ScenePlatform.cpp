#include <iostream>
#include "ScenePlatform.hpp"

ScenePlatform::ScenePlatform(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

ScenePlatform::~ScenePlatform()
{
}

void ScenePlatform::Init()
{
	// Puntero al Asset Manager;
	AM = GGE::AssetManager::Instance();

	// Establecemos un direcorio de recursos
	AM->AddDirectory("Data/");

	// Cambiamos el color del fondo de la escena
	this->SetBackgroundColor(sf::Color(200, 220, 255)); // Celeste

	// Creamos el mapa
	anMap = new GGE::Map();
	// Cargamos el mapa
	anMap->Load(AM->GetTmxMap("plat.tmx"));
	// Lo añadimos a la escena
	this->AddMap(anMap);

	// Convertimos los diamantes en actores
	diamantes = anMap->LayerToActors("diamantes");
	// Añadimos los diamantes a la escena
	this->AddActors(diamantes);

	// Obtenemos los rectángulos de las plataformas del tmx del mapa
	std::vector<GGE::TmxObject> colisiones = AM->GetTmxMap("plat.tmx").GetTmxObjetGroupbyName("colisiones").mObjects;
	for (int i = 0; i != colisiones.size(); i++)
	{
		int x1 = colisiones[i].GetPosX();
		int y1 = colisiones[i].GetPosY();
		int x2 = colisiones[i].GetPosX() + colisiones[i].GetWidth();
		int y2 = colisiones[i].GetPosY() + colisiones[i].GetHeight();

		plataformas.push_back(sf::FloatRect(x1, y1, x2, y2));
	}

	// Creamos al jugador
	player = new Player();
	// Definimos las plataformas como coliones del jugador
	player->DefineCollisionsRects(plataformas);
	// Lo añadimos a la escena
	this->AddActor(player);

	// Conectamos la camara al player
	mApp->mCamera->ConnectToSprite(*player);
	// Bloqueamos la camara al mapa
	mApp->mCamera->LockToMap(*anMap);
}

void ScenePlatform::ReInit()
{
}

void ScenePlatform::Events(sf::Event theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed)
	{
		if (theEvent.Key.Code == sf::Key::Escape)
			mApp->Quit(GGE::StatusAppOK);
	}
}

void ScenePlatform::Update()
{
	player->Update();
}

void ScenePlatform::Cleanup()
{
	// Eliminamos el mapa
	delete anMap;
	anMap = NULL;

	// Eliminamos la joyas
	this->DeleteActors(diamantes);

	// Eliminamos el player
	this->DeleteActor(player);
	player = NULL;
}
