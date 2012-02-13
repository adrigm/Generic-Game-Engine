#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <GGE/Core/App.hpp>
#include <GGE/Core/tmx/tmx.hpp>

namespace GGE
{

class Tileset
{
public:
	Tileset();
	~Tileset();

	void RegisterApp(App* theApp);
	void Init(TmxMap* TheTmx);
	void Draw(int theIndx, sf::Vector2f thePos);

private:
	/// Puntero a APP
	App* mApp;
	std::vector<sf::Sprite*> mImages;
	std::vector<int> mFirstgid;
	std::vector<sf::IntRect> mRects;

	int GetNumTileset(int theIndx) const;


}; // Class Tileset

} // Namespace GGE

#endif // TILESET_HPP