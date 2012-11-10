#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <GGE/Config.hpp>
#include <GGE/Core/Core_types.hpp>

namespace GGE
{

class Actor : public sf::Sprite
{
public:
	/// Orden de prioridad de dibujado
	GGE::Int32 mZOrder;

	Actor();
	virtual ~Actor();

	/**
	 * Devuelve true si el actor es visible y por tanto
	 * se dibuja en pantalla
	 *
	 * @return true si es visible
	 */
	bool IsVisible() const;

	/**
	 * Hace visible al actor (se renderiza si está en pantalla)
	 */
	void Show();

	/**
	 * Oculta el actor (evita que se renderice en pantalla)
	 */
	void Hide();

	/**
	 * Define el número de frames del Actor en base al tamaño de cada
	 * frame.
	 *
	 * @param theWidth Ancho de cada frame
	 * @param theHeight Alto de cada frame
	 */
	void SetFramesBySize(GGE::Uint32 theWidth, GGE::Uint32 theHeight);


	/**
	 * Define el número de frames del Actor en base al número de
	 * filas y columnas.
	 *
	 * @param theRows Filas de la imagen
	 * @param theCols Columnas de la imagen
	 */
	void SetFramesByNum(GGE::Uint32 theRows, GGE::Uint32 theCols);

	/**
	 * Selecciona un frame del Actor
	 *
	 * @param theFrame numero del frame seleccionado (comienza en 1)
	 */
	bool SelectFrame(GGE::Uint32 theFrame);

	/**
	 * Devuelve el frame seleccionado
	 *
	 * @return Devuelve el frame seleccionado
	 */
	GGE::Uint32 GetSelectFrame() const;

	void AddAnimation(const std::string theName, const GGE::Animation theAnim);
	GGE::Animation GetAnimation(std::string theName) const;

	void SetActiveAnimation(const std::string theName, bool reset = true);
	GGE::Animation GetActiveAnimation() const;

	virtual void Animate();

	void FlipX(bool flipped);
	void FlipY();

private:
	/// Puntero a App
	GGE::App* mApp;
	/// Si el Actor es visible o no
	bool mVisible;
	/// Lista de rects del Sprite (frames)
	std::vector<sf::IntRect> mRectsList;
	/// Frame seleccionado (Rect)
	GGE::Uint32 mSelectFrame;
	GGE::Uint32 mSelectFrameAnimation;
	/// Liste de animaciones
	std::map<std::string, GGE::Animation> mListAnim;
	/// Animación activa
	GGE::Animation mActiveAnimation;
	/// Tiempo que transcurre entre cada frame
	float mElapsedTime;
	// Flip
	bool myIsFlippedX;

}; // Class Actor

} // Namepace GGE

#endif // ACTOR_HPP