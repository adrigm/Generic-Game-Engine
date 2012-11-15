#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <GGE/Config.hpp>
#include <GGE/Core/Core_types.hpp>
#include <GGE/Core/Sprite.hpp>

namespace GGE
{

class Actor : public GGE::Sprite
{
public:
	Actor();
	virtual ~Actor();

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
	void SetFramesByGrid(GGE::Uint32 theRows, GGE::Uint32 theCols);

	/**
	 * Selecciona un frame del Actor
	 *
	 * @param theFrame numero del frame seleccionado (comienza en 1)
	 */
	void SelectFrame(GGE::Uint32 theFrame);

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

	void FlipX(bool flippedX);
	void FlipY(bool flippedY);

	void SetLeftPosition(float x);
	void SetTopPosition(float y);
	void SetRightPosition(float x);
	void SetBottomPosition(float y);

	float GetLeftPosition() const;
	float GetTopPosition() const;
	float GetRightPosition() const;
	float GetBottomPosition() const;

private:
	/// Puntero a App
	GGE::App* mApp;
	/// Lista de rects del Sprite (frames)
	std::vector<sf::IntRect> mRectsList;
	/// Frame seleccionado (Rect)
	GGE::Uint32 mSelectFrame;
	GGE::Uint32 mSelectFrameAnimation;
	/// Lista de animaciones
	std::map<std::string, GGE::Animation> mListAnim;
	/// Animación activa
	GGE::Animation mActiveAnimation;
	/// Tiempo que transcurre entre cada frame
	float mElapsedTime;
	/// Verdadero si la imagen tiene Flip en el eje X
	bool mIsFlippedX;
	/// Verdadero si la imagen tiene Flip en el eje Y
	bool mIsFlippedY;

}; // Class Actor

} // Namepace GGE

#endif // ACTOR_HPP