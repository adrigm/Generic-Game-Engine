#include <iostream> // Quitar
#include "Hero.hpp"

Hero::Hero() :
	mStatus(IDLE)
{
	mApp = GGE::App::Instance();
	this->FlipX(true);
}

Hero::~Hero()
{
}

void Hero::Update()
{
	this->Animate();

	switch (mStatus)
	{
	case IDLE:
		//std::cout << "Quieto\n";
		break;
	case JUMP:
		//std::cout << "Saltando\n";
		break;
	case RUN:
		//std::cout << "Corriendo\n";
		break;
	case FALL:
		//std::cout << "Callendo\n";
		break;
	case DEAD:
		//std::cout << "Muriendo\n";
		break;
	case WIN:
		//std::cout << "Ganando\n";
		break;
	}
}

void Hero::SetStatus(Status theStatus)
{
	mStatus = theStatus;
}