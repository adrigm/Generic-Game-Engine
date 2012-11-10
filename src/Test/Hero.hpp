#ifndef HERO_HPP
#define HERO_HPP

#include <GGE/Core.hpp>

enum Status {IDLE, RUN, JUMP, FALL, DEAD, WIN};

class Hero : public GGE::Actor
{
public:
	Hero();
	~Hero();

	void Update();

	void SetStatus(Status theStatus);

private:
	// Puntero a App
	GGE::App* mApp;
	// Estados
	Status mStatus;

}; // Hero

#endif // HERO_HPP