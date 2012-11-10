#include <GGE/Core/Clock.hpp>

namespace GGE
{

Clock::Clock() :
	clock()
{
	clock.restart();
}

Clock::~Clock()
{
}

void Clock::Reset()
{
	clock.restart();
}

sf::Time Clock::GetElapsedTime() const
{
	return clock.getElapsedTime();
}

}

