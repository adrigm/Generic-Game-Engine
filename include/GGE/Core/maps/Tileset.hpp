#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/tmx/tmx.hpp>
#include <GGE/Core/Actor.hpp>

namespace GGE
{

class Tileset
{
public:
	Tileset();
	~Tileset();

	/**
	 * Inicializa el tileset.
	 *
	 * @param [in,out]	TheTmx	Puntero al archivo tmx.
	 */
	void Init(TmxMap* TheTmx);

	/**
	 * Dibuja un tile en pantalla
	 *
	 * @param	theIndx	el indice del tile que se quiere dibujar.
	 * @param	thePos 	Vector con la posición en la que se dibujará.
	 */
	void Draw(int theIndx, sf::Vector2i thePos);

	/**
	 * Devuelve el Rect de un tile del tileset
	 *
	 * @param	theIndx	el indice del tile a devolver.
	 */
	sf::IntRect GetRect(const int theIndx);

	/**
	 * Devuelve un actor con la imagen de un tileset
	 *
	 * @param	theIndx	el indice del tile a devolver.
	 */
	GGE::Actor* GetImage(const int theIndx);

private:
	/// Puntero a APP
	App* mApp;
	/// Vector que contiene las imágenes
	std::vector<GGE::Actor*> mImages;
	/// Vector que contiene el número del primer tile del tileset
	std::vector<int> mFirstgid;
	/// Vector que contiene los rets de los tilesets
	std::vector<sf::IntRect> mRects;

	/**
	 * Devuelve el tileset al que pertenece un tile en concreto.
	 *
	 * @param	theIndx	the indx.
	 *
	 * @return	The number tileset.
	 */
	int GetNumTileset(int theIndx) const;


}; // Class Tileset

} // Namespace GGE

#endif // TILESET_HPP