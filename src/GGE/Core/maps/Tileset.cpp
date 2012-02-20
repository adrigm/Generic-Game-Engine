#include <GGE/Core/maps/Tileset.hpp>
#include <iostream>

namespace GGE
{

Tileset::Tileset()
{
}

Tileset::~Tileset()
{
}

void Tileset::RegisterApp(App* theApp)
{
	mApp = theApp;
}

void Tileset::Init(TmxMap* TheTmx)
{
	// Insertamos un rect vacio en los Rects ya que se empieza a contar en el 1 el 0 es sin tile
	mRects.push_back(sf::IntRect(0, 0, 0, 0));

	int numTilesets = TheTmx->mTilesets.size();
	for (int i = 0; i < numTilesets; i++)
	{
		// Cargamos las imagenes de los Tilesets en el AssetManager
		std::string dir = TheTmx->mTilesets[i].GetFile();
		sf::Sprite* sprite = new sf::Sprite();
		sprite->SetImage(mApp->mAssetManager->GetImage(dir));
		mApp->mAssetManager->GetImage(dir).SetSmooth(false); // Mejor no suavizar los tiles
		mImages.push_back(sprite);

		// Almacenamos el Primer tile del tileset
		mFirstgid.push_back(TheTmx->mTilesets[i].GetFirstGid());

		// Almacenamos los rects de diferentes tiles
		int width = TheTmx->mTilesets[i].GetWidth();
		int height = TheTmx->mTilesets[i].GetHeight();
		int tileWidth = TheTmx->mTilesets[i].GetTileWidth();
		int tileHeight = TheTmx->mTilesets[i].GetTileHeight();
		int rows = height / tileHeight; // Numero de filas del tileset
		int cols = width / tileWidth; // Numero de columnas del tileset

		for (int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
			{
				unsigned int x1 = c * tileWidth;
				unsigned int y1 = r * tileHeight;
				unsigned int x2 = x1 + tileWidth;
				unsigned int y2 = y1 + tileHeight;
				sf::IntRect rect(x1, y1, x2, y2);
				mRects.push_back(rect);
			}
		}
	}
}

void Tileset::Draw(int theIndx, sf::Vector2i thePos)
{
	// Numero del tileset del indice indicado
	int numTileset = this->GetNumTileset(theIndx);
	if (numTileset > 1)
		std::cout << numTileset << std::endl;
	if (numTileset != -1 && theIndx != 0)
	{
		// Seleccionamos el tileset
		mImages[numTileset]->SetSubRect(mRects[theIndx]);
		// Establecemos la posicion en la que se dibuja
		mImages[numTileset]->SetPosition(thePos.x, thePos.y);
		// Dibujemos la imagen
		mApp->mWindow.Draw(*mImages[numTileset]);
	}
}

int Tileset::GetNumTileset(int theIndx) const
{
	 for (int i = mFirstgid.size()-1; i >= 0; i--)
	{
		if (theIndx >= mFirstgid[i])
		{
			return i;
		}
	}
	return -1;
}

} // Namespace GGE