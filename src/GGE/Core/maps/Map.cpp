#include <GGE/Core/maps/Map.hpp>
#include <iostream>

namespace GGE
{

Map::Map(App* theApp) :
	mApp(theApp),
	mScroll(false),
	correctionX(0),
	correctionY(0)
{
}

Map::~Map()
{
}

bool Map::Load(TmxMap& theTmx)
{
	mTmx = &theTmx;
	mTileset.RegisterApp(mApp);
	mTileset.Init(mTmx);
	mWidth = mTmx->GetWidth();
	mHeight = mTmx->GetHeight();
	mTileWidth = mTmx->GetTileWidth();
	mTileHeight = mTmx->GetTileHeight();

	for (int layer = 0; layer < mTmx->mLayers.size(); layer++)
	{
		mData.push_back(mTmx->mLayers[layer].mTiles);
	}

	return true;
}

void Map::Update()
{
}

void Map::Draw()
{
	// Obtenemos las esquinas de la pantalla
	sf::Vector2i initial = MouseMap(0, 0);
	sf::Vector2i limit_bottom = MouseMap(0, mApp->mWindow.GetHeight());
	sf::Vector2i limit_right = MouseMap(mApp->mWindow.GetWidth(), 0);

	// Comprobamos si tenemos que añadir una linea mas de tiles al final de filas y columnas
	if (limit_right.x >= mWidth)
		correctionX = 0;
	else
		correctionX = 1;

	if (limit_bottom.y >= mHeight)
		correctionY = 0;
	else
		correctionY = 1;

	if (mScroll)
	{
		// Obetenemos la posicion desde la que se mide el Scroll.
		sf::Vector2f pos;
		pos.x = mPlayer->GetPosition().x;
		pos.y = mPlayer->GetPosition().y;

		// Comprobamos los bordes de los mapas para detener el Scroll
		// Eje X
		if (pos.x < mApp->mWindow.GetWidth() / 2)
			pos.x = mApp->mWindow.GetWidth() / 2;
		else if (pos.x > mWidth * mTileWidth - mApp->mWindow.GetWidth() / 2)
			pos.x = mWidth * mTileWidth - mApp->mWindow.GetWidth() / 2;
		// Eje y
		if (pos.y < mApp->mWindow.GetHeight() / 2)
			pos.y = mApp->mWindow.GetHeight() / 2;
		else if (pos.y > mHeight * mTileHeight - mApp->mWindow.GetHeight() / 2)
			pos.y = mHeight * mTileHeight - mApp->mWindow.GetHeight() / 2;
	
		// Establecemos la nueva vista
		vis.SetCenter(pos);
	}

	// Dibujamos los tilesets
	for(int l = 0; l < mData.size(); l++)
	{
		for(int r = initial.y; r < limit_bottom.y+correctionY; r++)
		{
			for (int c = initial.x; c < limit_right.x+correctionX; c++)
			{
				if (r >= 0 && c >= 0 && r < mHeight && c < mWidth && mData[l][r][c] != 0)
					mTileset.Draw(mData[l][r][c], Plot(c, r));
			}
		}
	}
}

sf::Vector2i Map::Plot(int TheCol, int TheRow)
{
	sf::Vector2i vector;
	vector.x = TheCol * mTileWidth;
	vector.y = TheRow * mTileHeight;
	return vector;
}

sf::Vector2i Map::MouseMap(int x, int y)
{
	sf::Vector2i vector;

	if (mScroll)
	{
		sf::Vector2f vec = mApp->mWindow.ConvertCoords(x, y);
		vector.x = (int)(vec.x / mTileWidth);
		vector.y = (int)(vec.y / mTileHeight);
		return vector;
	}
	else
	{
		vector.x = (int)(x / mTileWidth);
		vector.y = (int)(y / mTileHeight);
		return vector;
	}
}

void Map::SetScrollParallax(GGE::Actor& thePlayer)
{
	mPlayer = &thePlayer;
	vis = sf::View(sf::FloatRect(0, 0, mApp->mWindow.GetWidth(), mApp->mWindow.GetHeight()));
	vis.SetCenter(mPlayer->GetPosition());
	mApp->mWindow.SetView(vis);
	mScroll = true;
}

GGE::Uint32 Map::GetTile(int theLayer, int theRow, int theCol)
{
	return mData[theLayer][theRow][theCol];
}

void Map::SetTile(int theLayer, int theRow, int theCol, int theValue)
{
	mData[theLayer][theRow][theCol] = theValue;
}

} // Namespace GGE
