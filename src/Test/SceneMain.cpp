#include <iostream>
#include "SceneMain.hpp"
#include "SceneMenu.hpp"

SceneMain::SceneMain(GGE::SceneID theID) :
	GGE::Scene(theID)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	AM = GGE::AssetManager::Instance();
	mApp->mAssetManager->AddDirectory("Data/");
	hero.SetImage(mApp->mAssetManager->GetImage("sprite.png"));
	hero.SetGrid(4, 4);
	hero.SetCenter(hero.GetWidth()/2, hero.GetHeight());
	hero.SetPosition(160, 320);
	mapa.Load(mApp->mAssetManager->GetTmxMap("plat.tmx"));
	mApp->mCamera->ConnectToSprite(hero);
	mApp->mCamera->LockToMap(mapa);
	this->AddActor(&hero);
	this->SetBackgroundColor(sf::Color(200, 200, 200));
	this->AddMap(&mapa);

	std::vector<GGE::Actor*> joyas = mapa.LayerToActors("diamantes");
	this->AddActors(joyas);
	cir = sf::Shape::Circle(100, 100, 50, sf::Color(0,0,0,0), -1, sf::Color(0,255,0));

	GGE::FloatCircle m = GGE::FloatCircle(sf::Vector2f(20, 20), 50.0f);
	m.Offset(50, 35.4f);
	std::cout << m.Center.x << ", " << m.Center.y << std::endl;
	std::cout << m.Radius << std::endl;
	std::cout << m.GetDiameter() << std::endl;
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
		if (theEvent.Key.Code == sf::Key::Space)
			this->QuitActor(&hero);
	}
}

void SceneMain::Update()
{
	hero.Update();
}

void SceneMain::Cleanup()
{
}
