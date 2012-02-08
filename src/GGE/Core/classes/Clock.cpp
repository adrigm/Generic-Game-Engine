#include <GGE/Core/classes/Clock.hpp>

namespace GGE
{

Clock::Clock() :
	clock()
{
	clock.Reset();
}

Clock::~Clock()
{
}

void Clock::Reset()
{
	clock.Reset();
}

float Clock::GetElapsedTime() const
{
	return clock.GetElapsedTime();
}

}

