#include <GGE/Core/utils/zlib.hpp>
#include <GGE/Core/utils/base64.hpp>
#include <GGE/Core/tmx/tmxLayer.hpp>
#include <iostream>

namespace GGE
{

TmxLayer::TmxLayer()
{
}

TmxLayer::~TmxLayer()
{
}

void TmxLayer::DescompressData()
{
	// Creamos array auxuliar
	std::vector<unsigned int> values;

	// Descomprimimos y decodifamos la capa
	int len = strlen((const char*)mData.c_str()) + 1;
	unsigned char *charData = new unsigned char[len + 1];
	const char *charStart = (const char*) mData.c_str();
	unsigned char *charIndex = charData;

	while (*charStart)
	{
		if (*charStart != ' ' && *charStart != '\t' &&
				*charStart != '\n')
		{
			*charIndex = *charStart;
			charIndex++;
		}
		charStart++;
	}
	*charIndex = '\0';

	int binLen;
	unsigned char *binData = base64_decode(charData, strlen((char*)charData), &binLen);

	delete[] charData;

	if (binData)
	{
		if (mCompression == "gzip" || mCompression == "zlib")
		{
			// Inflate the gzipped layer data
			unsigned char *inflated;
			unsigned int inflatedSize = inflateMemory(binData, binLen, inflated);

			//free(binData);
			binData = inflated;
			binLen = inflatedSize;

			if (!inflated)
			{
				std::cerr << "Error: Could not decompress layer!" << std::endl;
				return;
			}
		}
		for (int i = 0; i < binLen - 3; i += 4)
		{
			const int gid = binData[i] | binData[i + 1] << 8 | binData[i + 2] << 16 | binData[i + 3] << 24;
			values.push_back(gid);
		}
		free(binData);
	}
			
	// Creamos un array bidimensional para los datos
	int cont = 0;
	for(int f=0; f < mHeight; f++)
	{
		std::vector<GGE::Uint32> aux;
		for(int c=0; c < mWidth; c++)
		{
			aux.push_back(values[cont]);
			cont++;
		}
		mTiles.push_back(aux);
	}
}


void TmxLayer::SetName(const std::string& theName)
{
	mName = theName;
}

std::string TmxLayer::GetName() const
{
	return mName;
}

void TmxLayer::SetWidth(const int theWidth)
{
	mWidth = theWidth;
}

int TmxLayer::GetWidth() const
{
	return mWidth;
}

void TmxLayer::SetHeight(const int theHeight)
{
	mHeight = theHeight;
}

int TmxLayer::GetHeight() const
{
	return mHeight;
}

void TmxLayer::SetEncoding(const std::string& theEncoding)
{
	mEncoding = theEncoding;
}

std::string TmxLayer::GetEncoding() const
{
	return mEncoding;
}

void TmxLayer::SetCompression(const std::string& theCompression)
{
	mCompression = theCompression;
}

std::string TmxLayer::GetCompression() const
{
	return mCompression;
}

void TmxLayer::SetData(const std::string& theData)
{
	mData = theData;
}

std::string TmxLayer::GetData() const
{
	return mData;
}

void TmxLayer::SetVisible(bool theVisible)
{
	mVisible = theVisible;
}

bool TmxLayer::GetVisible() const
{
	return mVisible;
}

void TmxLayer::SetOpacity(const double theOpacity)
{
	mOpacity = theOpacity;
}

double TmxLayer::GetOpacity() const
{
	return mOpacity;
}

} // Namespace GGE