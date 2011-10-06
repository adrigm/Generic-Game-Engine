#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/System.hpp>

namespace BGE
{

class Clock
{

public:
	Clock();
	~Clock();
	
	void Reset();
	float GetElapsedTime() const;
	
private:
	sf::Clock clock;
};

}

#endif // CLOCK_H
