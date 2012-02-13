#include <GGE/Core/maps/Map.hpp>
#include <iostream>

namespace GGE
{

Map::Map(App* theApp) :
	mApp(theApp)
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
	// Obetenemos la posicion desde la que se mide el Scroll.
	sf::Vector2f pos;
	pos.x = mPlayer->GetPosition().x;
	pos.y = mPlayer->GetPosition().y;
	
	// Obtenemos las esquinas de la pantalla
	initial = MouseMap(0, 0);
	limit_bottom = MouseMap(0, mApp->mWindow.GetHeight());
	limit_right = MouseMap(mApp->mWindow.GetWidth(), 0);
	

	// Comprobamos si tenemos que añadir una linea mas de tiles al final de filas y columnas
	if (limit_right.x >= mWidth)
		correctionX = 0;
	else
		correctionX = 1;

	if (limit_bottom.y >= mHeight)
		correctionY = 0;
	else
		correctionY = 1;

	// Comprobamos los bordes de los mapas para detener el Scroll
	// Eje X
	if (pos.x < mApp->mWindow.GetWidth() / 2)
	{
		pos.x = mApp->mWindow.GetWidth() / 2;
	}
	else if (pos.x > mWidth * mTileWidth - mApp->mWindow.GetWidth() / 2)
	{
		pos.x = mWidth * mTileWidth - mApp->mWindow.GetWidth() / 2;
	}
	// Eje y
	if (pos.y < mApp->mWindow.GetHeight() / 2)
	{
		pos.y = mApp->mWindow.GetHeight() / 2;
	}
	else if (pos.y > mHeight * mTileHeight - mApp->mWindow.GetHeight() / 2)
	{
		pos.y = mHeight * mTileHeight - mApp->mWindow.GetHeight() / 2;
	}
	
	// Establecemos la nueva vista
	vis.SetCenter(pos);
}

void Map::Draw()
{
	for(int l = 0; l < mData.size(); l++)
	{
		for(int r = initial.y; r < limit_bottom.y+correctionY; r++)
		{
			for (int c = initial.x; c < limit_right.x+correctionX; c++)
			{
				if (mData[l][r][c] != 0)
					mTileset.Draw(mData[l][r][c], Plot(c, r));
			}
		}
	}
}

sf::Vector2f Map::Plot(int TheCol, int TheRow)
{
	sf::Vector2f vector;
	vector.x = TheCol * mTileWidth;
	vector.y = TheRow * mTileHeight;
	return vector;
}

sf::Vector2f Map::MouseMap(int x, int y)
{
	sf::Vector2f vector;
	vector = mApp->mWindow.ConvertCoords(x, y);
	vector.x = (int)(vector.x / mTileWidth);
	vector.y = (int)(vector.y / mTileHeight);
	return vector;
}

void Map::SetScrollParallax(GGE::Actor& thePlayer)
{
	mPlayer = &thePlayer;
	vis = mApp->mWindow.GetDefaultView();
	vis.SetCenter(mPlayer->GetPosition());
	mApp->mWindow.SetView(vis);
}

} // Namespace GGE