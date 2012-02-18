#include <GGE/Core/Cursor.hpp>

namespace GGE
{

Cursor* Cursor::ms_instance = 0;

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::SetImage(sf::Image& theImage)
{
	mActor.SetImage(theImage);
}

Cursor* Cursor::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new Cursor();
	}
	return ms_instance;
}

void Cursor::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

} // Namespacr GGE