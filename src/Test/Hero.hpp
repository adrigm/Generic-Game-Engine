#ifndef HERO_HPP
#define HERO_HPP

#include <vector>
#include <map>
#include <GGE/Core.hpp>
#include <GGE/Core/Actor.hpp>

enum status
{
	WALK_LEFT,
	WALK_RIGHT,
	WALK_UP,
	WALK_DOWN,
	QUIET_LEFT,
	QUIET_RIGHT,
	QUIET_UP,
	QUIET_DOWN
};

struct anim
{
	int fps, row, firstFrame, LastFrame;
};

class Hero : public GGE::Actor
{
public:
	Hero(GGE::App* theApp);
	~Hero();

	void Update();
	void ChangeStatus(status theStatus);
	bool NextFrame();

	void WalkLeft();
	void WalkRight();
	void WalkUp();
	void WalkDown();
	void Quiet();

private:
	GGE::App* mApp;
	status mStatus;
	std::map<status, struct anim> mAnim;
	float mTime;
	int mFrame;
	int pos_ant;

}; // Class Hero

#endif // HERO_HPP

