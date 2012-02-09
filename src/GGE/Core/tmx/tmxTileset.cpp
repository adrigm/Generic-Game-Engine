
#include <GGE/Core/tmx/tmxTileset.hpp>

namespace GGE
{

TmxTileset::TmxTileset()
{
}

TmxTileset::~TmxTileset()
{
}

void TmxTileset::SetName(const std::string& theName)
{
	mName = theName;
}

std::string TmxTileset::GetName() const
{
	return mName;
}

void TmxTileset::SetFirstGid(const int theFirstGid)
{
	mFirstGid = theFirstGid;
}

int TmxTileset::GetFirstGid() const
{
	return mFirstGid;
}

void TmxTileset::SetTileWidth(const int width)
{
	mTileWidth = width;
}

int TmxTileset::GetTileWidth() const
{
	return mTileWidth;
}

void TmxTileset::SetTileHeight(const int height)
{
	mTileHeight = height;
}

int TmxTileset::GetTileHeight() const
{
	return mTileHeight;
}

void TmxTileset::SetFile(const std::string& theFile)
{
	mFile = theFile;
}

std::string TmxTileset::GetFile() const
{
	return mFile;
}

void TmxTileset::SetColorkey(const std::string& theTrans)
{
	mTrans = theTrans;
}

std::string TmxTileset::GetColorkey() const
{
	return mTrans;
}

void TmxTileset::SetWidth(const int theWidth)
{
	mWidth = theWidth;
}

int TmxTileset::GetWidth() const
{
	return mWidth;
}

void TmxTileset::SetHeight(const int theHeight)
{
	mHeight = theHeight;
}

int TmxTileset::GetHeight() const
{
	return mHeight;
}

void TmxTileset::SetTileProperty(const int theTile, const std::string& theName, const std::string& theValue)
{
	mTiles[theTile].SetProperty(theName, theValue);
}

std::string TmxTileset::GetTileProperty(const int theTile, const std::string& theName) const
{
	std::map<int, TmxProperties>::const_iterator itmTiles = mTiles.find(theTile);
	if (itmTiles != mTiles.end())
	{
		return itmTiles->second.GetProperty(theName);
	}

	return "";
}

} // Namespace GGE