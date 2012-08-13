#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <GGE/Core.hpp>

enum status
{
	IDLE,
	RUN,
	JUMP,
	CRASH,
	FALL
};

struct anim
{
	int fps, row, firstFrame, LastFrame;
};

class Player : public GGE::Actor
{
public:
	Player();
	~Player();

	float mTOpx(float m);
	float pxTOm(float px);

	void DefineCollisionsRects(std::vector<sf::FloatRect>& rects);
	sf::FloatRect* Collision();

	void Update();
	void ChangeStatus(status theStatus);
	bool NextFrame();

	void Idle();
	void Run();
	void Jump();
	void Fall();

private:
	GGE::App* mApp;
	std::vector<sf::FloatRect> mRectsCollision;
	status mStatus;
	std::map<status, struct anim, std::less<int> > mAnim;
	float mTime;
	int mFrame;
	float v_initial;
	float gravity;
	sf::Vector2f velocity;
	float t;

}; // Class Player

#endif // PLAYER_HPP