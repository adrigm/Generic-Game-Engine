#include "Player.hpp"
#include <iostream>

Player::Player() :
	mTime(0.0f),
	mFrame(1)
{
	mApp = GGE::App::Instance();

	struct anim idle = {12, 1, 1, 1};
	mAnim[IDLE] = idle;
	struct anim run = {12, 1, 2, 11};
	mAnim[RUN] = run;
	struct anim jump = {15.555, 2, 2, 11};
	mAnim[JUMP] = jump;
	struct anim fall = {15.555, 2, 8, 8};
	mAnim[FALL] = fall;

	ChangeStatus(IDLE);

	// Establecemos la zona de colisión
	SetRectCollision(sf::FloatRect(22, 0, 42, 64));
	// Establecemos la image
	SetImage(mApp->mAssetManager->GetImage("indiana.png"));
	// No suavizamos la imagen
	mApp->mAssetManager->GetImage("indiana.png").SetSmooth(false);
	// Establecemos la grilla de imágenes
	SetGrid(4, 12);
	// Cambiamos el centro
	SetCenter(GetWidth()/2, GetHeight());

	v_initial = 18.66666f;
	velocity.x = 8.0f;
	velocity.y = 0.0f;
	gravity = -41.48148f;
	t = 0.0f;
	SetPosition(100, 416);
}

Player::~Player()
{
}

void Player::Update()
{
	mTime += mApp->GetUpdateTime();

	switch (mStatus)
	{
	case IDLE:
		Idle();
		break;
	case RUN:
		Run();
		break;
	case JUMP:
		Jump();
		break;
	case FALL:
		Fall();
		break;
	}
}

void Player::ChangeStatus(status theStatus)
{
	mStatus = theStatus;
	mFrame = mAnim[theStatus].firstFrame;
}

bool Player::NextFrame()
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

void Player::Idle()
{
	this->NextFrame();

	if (this->Collision() == NULL)
	{
		this->ChangeStatus(FALL);
	}

	if (mApp->mInput.IsKeyDown(sf::Key::Space) || mApp->mInput.IsKeyDown(sf::Key::Up))
	{
		this->ChangeStatus(JUMP);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		if (velocity.x < 0.0)
			velocity.x *= -1;
		FlipX(true);
		this->ChangeStatus(RUN);
	}
	else if (mApp->mInput.IsKeyDown(sf::Key::Left))
	{
		if (velocity.x > 0.0)
			velocity.x *= -1;
		FlipX(false);
		this->ChangeStatus(RUN);
	}
}

void Player::Run()
{
	if (this->Collision() == NULL)
	{
		this->ChangeStatus(FALL);
	}
	else if (!mApp->mInput.IsKeyDown(sf::Key::Left) && !mApp->mInput.IsKeyDown(sf::Key::Right))
		this->ChangeStatus(IDLE);
	else if (mApp->mInput.IsKeyDown(sf::Key::Left) && mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		this->ChangeStatus(IDLE);
		return;
	}

	this->NextFrame();
	float d = this->mTOpx(velocity.x*mApp->GetUpdateTime());
	this->Move(d, 0);
	
	if (mApp->mInput.IsKeyDown(sf::Key::Space) || mApp->mInput.IsKeyDown(sf::Key::Up))
	{
		this->ChangeStatus(JUMP);
	}
}

void Player::Jump()
{
	t += mApp->GetUpdateTime();
	float v = gravity*t + v_initial;
	float y = v*mApp->GetUpdateTime();
	this->Move(0, -y*32);
	this->NextFrame();

	if (this->Collision() != NULL && v > 0.0f)
	{
		v = 0;
		t = 0;
		this->SetY(this->Collision()->Bottom + this->GetCenter().y + 1);
		if (this->Collision() != NULL)
			std::cout << "COLISIONA\n";
		this->ChangeStatus(FALL);
	}

	if(v <= 0.0)
	{
		t = 0;
		this->ChangeStatus(FALL);
	}

	if (mApp->mInput.IsKeyDown(sf::Key::Left))
	{
		if (velocity.x > 0.0)
			velocity.x *= -1;
		FlipX(false);
		float d = this->mTOpx(velocity.x*mApp->GetUpdateTime());
		this->Move(d, 0);
	}
	if (mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		if (velocity.x < 0.0)
			velocity.x *= -1;
		FlipX(true);
		float d = this->mTOpx(velocity.x*mApp->GetUpdateTime());
		this->Move(d, 0);
	}
}

void Player::Fall()
{
	t += mApp->GetUpdateTime();
	float v = gravity*t;
	float y = v*mApp->GetUpdateTime();
	this->Move(0, -y*32);
	this->NextFrame();
	if (this->Collision() != NULL)
	{
		this->ChangeStatus(IDLE);
		this->SetY(this->Collision()->Top+1);
	}
	if (mApp->mInput.IsKeyDown(sf::Key::Left))
	{
		if (velocity.x > 0.0)
			velocity.x *= -1;
		FlipX(false);
		float d = this->mTOpx(velocity.x*mApp->GetUpdateTime());
		this->Move(d, 0);
	}
	if (mApp->mInput.IsKeyDown(sf::Key::Right))
	{
		if (velocity.x < 0.0)
			velocity.x *= -1;
		FlipX(true);
		float d = this->mTOpx(velocity.x*mApp->GetUpdateTime());
		this->Move(d, 0);
	}
}

void Player::DefineCollisionsRects(std::vector<sf::FloatRect>& rects)
{
	mRectsCollision = rects;
}

float Player::mTOpx(float m)
{
	return m*32;
}

float Player::pxTOm(float px)
{
	return px/32;
}

sf::FloatRect* Player::Collision()
{
	for (int i = 0; i < mRectsCollision.size(); i++)
	{
		if (GetRectCollision().Intersects(mRectsCollision[i]))
			return &mRectsCollision[i];
	}
	return NULL;
}