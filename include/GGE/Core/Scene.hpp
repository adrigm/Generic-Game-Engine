#ifndef GGE_SCENE_HPP
#define GGE_SCENE_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/Export.hpp>
#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/App.hpp>

namespace GGE
{

class GGE_CORE_API Scene
{
public:
	/**
	 * Scene Destructor
	 */
	virtual ~Scene();

	/**
	 * Devuelve el identificador único de la escena
	 *
	 * @return GGE::SceneID el ID de la escena
	 */
	const SceneID GetID() const;

	/**
	 * Devuelve true si el Init() ya ha sido llamado
	 */
	const bool IsInitComplete() const;

	void SetBackgroundColor(const sf::Color &theColor);

	/**
	 * Devuelve true si la escena está pausada
	 */
	const bool IsPaused() const;

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Event(sf::Event theEvent) = 0;

	virtual void Resume() = 0;

	virtual void Pause() = 0;

	virtual void Draw();

	virtual void Cleanup() = 0;

protected:
	/// Puntero a la aplicación padre
	GGE::App* m_app;

	/**
	 * Constructor de la escena
	 * 
	 * @param m_id Cadena de texto que establece un identificador único
	 */
	Scene(SceneID theID);


private:
	/// Representa el id único de la escena
	const SceneID m_ID;
	/// Comprueba si cleanup debe ser llamado
	bool m_cleanup;
	/// Comprueba si la escena está inicializada
	bool m_init;
	/// Comprueba si la escena está pausada
	bool m_paused;
	/// Color de fondo de la escena
	sf::Color m_colorBack;

}; // class Scene

} // namespace GGE

#endif // GGE_SCENE_HPP