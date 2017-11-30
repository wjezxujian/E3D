#include "EPlayerController.h"
#include "EGameManager.h"

namespace E3D
{
	EPlayerController::EPlayerController(EGameManager* gameMgr)
		: mCurDir(0)
		, mGameMgr(gameMgr)
		, mScene(gameMgr->getSceneManager())
		, mFireDir(0)
	{
		mCamera = mScene->getCamera();
		mTank = new ETank("Player", "Green", gameMgr);
	}

	EPlayerController::~EPlayerController()
	{
		SafeDelete(mTank);
	}

	void EPlayerController::setPosition(const EVector3D& pos)
	{
		mTank->setPosition(pos);
		mCamera->setPosition(pos + EVector3D(0, 25, 30));
		mCamera->setTarget(pos);
	}

	void EPlayerController::keyPress(EInt key)
	{
		if (key == 'W')
		{
			mCurDir |= (int)DIRECTION::DIR_UP;
		}
		else if (key = 'S')
		{
			mCurDir |= (int)DIRECTION::DIR_DOWN;
		}
		else if (key == 'A')
		{
			mCurDir |= (int)DIRECTION::DIR_LEFT;
			mTank->turnLeft();
		}
		else if(key = 'D')
		{
			mCurDir |= (int)DIRECTION::DIR_RIGHT;
			mTank->turnRight();
		}
		else if (key == VK_SPACE)
		{
			mTank->fire();
		}
		else if (key == VK_LEFT)
		{
			mFireDir = -1;
		}
		else if (key == VK_RIGHT)
		{
			mFireDir = 1;
		}
		else if (key == 'F')
		{
			if (mCamera->getRenderMode() == RenderMode::RENDER_WIRE)
				mCamera->setRenderMode(RenderMode::RENDER_SOILD);
			else
				mCamera->setRenderMode(RenderMode::RENDER_WIRE);
		}
		else if (key == 'G')
		{
			mTank->setBulletType(mTank->getBulletType() == BulletType::BULLET_ROCKET ? BulletType::BULLET_BALL : BulletType::BULLET_ROCKET);
		}
	}

	void EPlayerController::keyRelease(EInt key)
	{
		if (key == 'W')
			mCurDir &= ~(int)DIRECTION::DIR_UP;
		else if (key == 'S')
			mCurDir &= ~(int)DIRECTION::DIR_DOWN;
		else if (key == 'A')
			mCurDir &= ~(int)DIRECTION::DIR_LEFT;
		else if (key == 'D')
			mCurDir &= ~(int)DIRECTION::DIR_RIGHT;
		else if (key == VK_LEFT || key == VK_RIGHT)
			mFireDir = 0;
	}

	void EPlayerController::update()
	{
		if (mCurDir & (int)DIRECTION::DIR_UP)
		{
			mTank->moveUp();
			mCamera->move(mTank->getCameraStep());
		}
		else if (mCurDir & (int)DIRECTION::DIR_DOWN)
		{
			mTank->moveDown();
			mCamera->move(mTank->getCameraStep());
		}

		if (mFireDir == -1)
			mTank->fireAimLeft();
		else if (mFireDir == 1)
			mTank->fireAimRight();

		mTank->update();
	}
}