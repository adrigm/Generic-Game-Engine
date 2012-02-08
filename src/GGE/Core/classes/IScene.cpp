#include <GGE/Core/classes/IScene.hpp>

namespace GGE
{

IScene::IScene(SceneID theID, App* theApp) :
	mApp(theApp),
	mID(theID),
	mInit(false),
	mPaused(false),
	mCleanup(false)
{
}

IScene::~IScene()
{
}

const SceneID IScene::GetID() const
{
	return mID;
}
	
const bool IScene::IsInitComplete() const
{
	return mInit;
}
	
const bool IScene::IsPaused() const
{
	return mPaused;
}
	

void IScene::Init()
{
	mApp->mLog << "ISCENE::Init(" << mID << ") llamado" << std::endl;

	if (!mInit)
	{
		mInit = true;
		mPaused = false;
	}
}

void IScene::ReInit()
{
	mApp->mLog << "ISCENE::ReInit(" << mID << ") llamado" << std::endl;
}

void IScene::Pause()
{
	mApp->mLog << "ISCENE::Pause(" << mID << ") llamado" << std::endl;

	mPaused = true;
}
	
void IScene::Resume()
{
	mApp->mLog << "ISCENE::Resume(" << mID << ") llamado" << std::endl;

	mPaused = false;
}

void IScene::HandleCleanup(void)
{
	if(mCleanup)
	{
		Cleanup();
		mCleanup = false;
	}
}
	

void IScene::Cleanup()
{
	mApp->mLog << "ISCENE::Cleanup(" << mID << ") llamado" << std::endl;
}

void IScene::Events(sf::Event TheEvent)
{
}
	
void IScene::Update(void)
{
}

void IScene::Draw(void)
{
}

} // Namespace GGE
