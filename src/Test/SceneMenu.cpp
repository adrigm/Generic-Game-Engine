#include <iostream>
#include "SceneMenu.hpp"

SceneMenu::SceneMenu(GGE::SceneID theID, GGE::App* theApp) :
	GGE::IScene(theID, theApp)
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Init()
{
	this->text.SetText("Scene Menu");
	text.SetPosition(200, 200);
	text.SetSize(20);
}

void SceneMenu::ReInit()
{
}

void SceneMenu::Events(sf::Event theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed && theEvent.Key.Code == sf::Key::Space)
	{
		mApp->mSceneManager->SetActiveScene("Main");
	}
}

void SceneMenu::Update()
{
	/*if (mApp->mInput.IsKeyDown(sf::Key::Space))
	{
		mApp->mSceneManager->SetActiveScene("Main");
	}*/
}

void SceneMenu::Draw()
{
	mApp->mWindow.Clear(sf::Color(220, 255, 190));
	mApp->mWindow.Draw(text);
}

void SceneMenu::Cleanup()
{
}