#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SFML/Graphics.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/Actor.hpp>

namespace GGE
{

class Cursor
{

	static Cursor* ms_instance;

public:
	static Cursor* Instance();
	static void Release();

	void SetImage(sf::Image& theImage);

	void GetPosition();
	void SetPosition();

private:
	/// Imagen del cursor
	sf::Image* mImage;
	/// Actor que representa al cursor
	GGE::Actor mActor;

	Cursor();
	virtual ~Cursor();

}; // Class Cursor

} // Namespace GGE

#endif // CURSOR_HPP