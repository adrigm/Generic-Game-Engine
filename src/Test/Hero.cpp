#include "Hero.hpp"
#include <iostream>

Hero::Hero(GGE::App* theApp) :
	mStatus(QUIET_DOWN),
	mApp(theApp),
	mTime(0.0f),
	mFrame(1),
	pos_ant(0)
{
	struct anim left = {8, 2, 1, 4};
	mAnim[WALK_LEFT] = left;
	struct anim right = {8, 3, 1, 4};
	mAnim[WALK_RIGHT] = right;
	struct anim up = {8, 4, 1, 4};
	mAnim[WALK_UP] = up;
	struct anim down = {8, 1, 1, 4};
	mAnim[WALK_DOWN] = down;
	struct anim qleft = {8, 2, 1, 1};
	mAnim[QUIET_LEFT] = qleft;
	struct anim qright = {8, 3, 1, 1};
	mAnim[QUIET_RIGHT] = qright;
	struct anim qup = {8, 4, 1, 1};
	mAnim[QUIET_UP] = qup;
	struct anim qdown = {8, 1, 1, 1};
	mAnim[QUIET_DOWN] = qdown;
}


Hero::~Hero(void)
{
}

void Hero::Update()
{
	mTime += mApp->GetUpdateTime();

	switch (mStatus)
	{
	case WALK_LEFT:
		WalkLeft();
		break;
	case WALK_RIGHT:
		WalkRight();
		break;
	case WALK_UP:
		WalkUp();
		break;
	case WALK_DOWN:
		WalkDown();
		break;
	case QUIET_LEFT:
		Quiet();
		break;
	case QUIET_RIGHT:
		Quiet();
		break;
	case QUIET_UP:
		Quiet();
		break;
	case QUIET_DOWN:
		Quiet();
		break;
	}
}

void Hero::ChangeStatus(status theStatus)
{
	mStatus = theStatus;
	mFrame = mAnim[theStatus].firstFrame;
}

bool Hero::NextFrame()
{
	if (mTime >= 1.0f / mAnim[mStatus].fps)
	{
		mTime = 0.0f;
		this->SelectGid(mAnim[mStatus].row, mFrame);
		if (mFrame < mAnim[mStatus].LastFrame)
		{
			mFrame++;
		}
		else
		{
			mFrame = mAnim[mStatus].firstFrame;
			return true;
		}
	}
	return false;
}

void Hero::WalkLeft()
{
	if (pos_ant < 32)
	{
		pos_ant += 2;
		this->Move(-2, 0);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Left))
	{
		pos_ant = 0;
	}
	else
	{
		this->ChangeStatus(QUIET_LEFT);
		pos_ant = 0;
	}
	this->NextFrame();
}

void Hero::WalkRight()
{
	if (pos_ant < 32)
	{
		pos_ant += 2;
		this->Move(2, 0);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		pos_ant = 0;
	}
	else
	{
		this->ChangeStatus(QUIET_RIGHT);
		pos_ant = 0;
	}
	this->NextFrame();
}

void Hero::WalkUp()
{
	if (pos_ant < 32)
	{
		pos_ant += 2;
		this->Move(0, -2);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Up))
	{
		pos_ant = 0;
	}
	else
	{
		this->ChangeStatus(QUIET_UP);
		pos_ant = 0;
	}
	this->NextFrame();
}

void Hero::WalkDown()
{
	if (pos_ant < 32)
	{
		pos_ant += 2;
		this->Move(0, 2);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Down))
	{
		pos_ant = 0;
	}
	else
	{
		this->ChangeStatus(QUIET_DOWN);
		pos_ant = 0;
	}
	this->NextFrame();
}

void Hero::Quiet()
{
	if (mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		this->ChangeStatus(WALK_RIGHT);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Left))
	{
		this->ChangeStatus(WALK_LEFT);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Up))
	{
		this->ChangeStatus(WALK_UP);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Down))
	{
		this->ChangeStatus(WALK_DOWN);
	}
	this->NextFrame();
}