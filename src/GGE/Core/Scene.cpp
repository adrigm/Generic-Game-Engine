#include <GGE/Core/Scene.hpp>

namespace GGE
{

Scene::Scene(SceneID theID) :
	m_ID(theID),
	m_init(false),
	m_paused(false),
	m_cleanup(false),
	m_colorBack(0, 0, 0)
{
	m_app = GGE::App::Instance();
	m_app->log << "Scene::ctor() con ID: " << theID << " creada" << std::endl;
}

Scene::~Scene()
{
	m_app->log << "Scene::dtor() con ID: " << GetID() << " eliminada" << std::endl;
}

const SceneID Scene::GetID() const
{
	return m_ID;
}

const bool Scene::IsInitComplete() const
{
	return m_init;
}

const bool Scene::IsPaused() const
{
	return m_paused;
}

void Scene::SetBackgroundColor(const sf::Color &theColor)
{
	m_colorBack = theColor;
}

void Scene::Draw()
{
	m_app->window.clear(m_colorBack);
}



}; // namespace GGE