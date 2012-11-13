#ifndef OBJECT_SCENE_HPP
#define OBJECT_SCENE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <GGE/Core/Core_types.hpp>

namespace GGE
{

class ObjectScene : public sf::Drawable, public sf::Transformable
{
public:
	ObjectScene();
	virtual ~ObjectScene();

	GGE::Int32 GetZOrder() const;
	void SetZOrder(GGE::Int32 z);

	bool IsVisible() const;
	void Show();
	void Hide();

	virtual sf::FloatRect getLocalBounds() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;

private:
	/// Representa el orden de dibujado entre mayor más cerca de la cámara
	GGE::Int32 mZOrder;
	/// Verdadero si el Objeto es visible
	bool mVisible;
}; // Class ObjectScene

} // Namespace GGE

#endif // OBJECT_SCENE_HPP