#include "TestApp.hpp"
#include "SceneMain.hpp"

TestApp::TestApp(const std::string TheTitle) :
	GGE::App(TheTitle)
{
}

TestApp::~TestApp()
{
}

void TestApp::Init(void)
{
	GGE::App::Init();
	mSceneManager->AddScene(new SceneMain("Prueba", this));
	mSceneManager->ChangeScene("Prueba");
}