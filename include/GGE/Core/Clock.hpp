#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/System.hpp>

namespace GGE
{

class Clock
{

public:
	Clock();
	~Clock();
	
	void Reset();
	sf::Time GetElapsedTime() const;
	
private:
	sf::Clock clock;
};

}

#endif // CLOCK_H
