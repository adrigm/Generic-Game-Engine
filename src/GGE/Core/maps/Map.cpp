#include <GGE/Core/maps/Map.hpp>
#include <iostream>

namespace GGE
{

Map::Map() :
	corRectionX(0),
	corRectionY(0)
{
	mApp = GGE::App::Instance();
}

Map::~Map()
{
	delete mTileset;
}

bool Map::Load(TmxMap& theTmx)
{
	mTmx = &theTmx;
	mTileset = new Tileset();
	mTileset->Init(mTmx);
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
		corRectionX = 0;
	else
		corRectionX = 1;

	if (limit_bottom.y >= mHeight)
		corRectionY = 0;
	else
		corRectionY = 1;

	// Dibujamos los tilesets
	for(int l = 0; l < mData.size(); l++)
	{
		// Comprobamos que la capa sea visible
		if (mTmx->mLayers[l].GetVisible())
		{
			for(int r = initial.y; r < limit_bottom.y+corRectionY; r++)
			{
				for (int c = initial.x; c < limit_right.x+corRectionX; c++)
				{
					if (r >= 0 && c >= 0 && r < mHeight && c < mWidth && mData[l][r][c] != 0)
						mTileset->Draw(mData[l][r][c], Plot(c, r));
				}
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

	sf::Vector2f vec = mApp->mWindow.ConvertCoords(x, y);
	vector.x = (int)(vec.x / mTileWidth);
	vector.y = (int)(vec.y / mTileHeight);
	return vector;
}

GGE::Uint32 Map::GetTile(int theLayer, int theRow, int theCol)
{
	return mData[theLayer][theRow][theCol];
}

void Map::SetTile(int theLayer, int theRow, int theCol, int theValue)
{
	mData[theLayer][theRow][theCol] = theValue;
}

GGE::Uint32 Map::GetWidth() const
{
	return mWidth;
}

GGE::Uint32 Map::GetHeight() const
{
	return mHeight;
}

GGE::Uint32 Map::GetTileWidth() const
{
	return mTileWidth;
}

GGE::Uint32 Map::GetTileHeight() const
{
	return mTileHeight;
}

std::vector<GGE::Actor*> Map::LayerToActors(const std::string theName)
{
	std::vector<GGE::Actor*> list;

	GGE::TmxLayer& layer = mTmx->GetTmxLayerbyName(theName);
	for (int r = 0; r < layer.mTiles.size(); r++)
	{
		for (int c = 0; c < layer.mTiles[0].size(); c++)
		{
			if (layer.mTiles[r][c] != 0)
			{
				GGE::Actor* actor = new Actor();
				const sf::Image* image = mTileset->GetImage(layer.mTiles[r][c])->GetImage();
				actor->SetImage(*image);
				actor->AddRects(mTileset->GetRect(layer.mTiles[r][c]));
				actor->SelectRect(0);
				actor->SetPosition(c*mTileWidth, r*mTileHeight);
				list.push_back(actor);
			}
		}
	}
	return list;
}

} // Namespace GGE
