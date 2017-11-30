#include "EGameManager.h"
#include "EBullet.h"
#include "ETank.h"
#include "EPlayerController.h"
#include "ESceneManager.h"
#include "EAITank.h"

namespace E3D
{
	const EString Bullet_Ball = "BallBullet.mesh";
	const EString Bullet_Rocket = "RocketBullet.mesh";

	const EVector3D InitPosition(-20.f, 1.0f, 15.0f);

	const EVector3D RandomPos[3] = { EVector3D(10, 1.5f, 10), EVector3D(45, 1.5f, -5), EVector3D(-20, 1.5f, 45) };

	EGameManager::EGameManager(ESceneManager* scene)
		: mScene(scene)
		, mBlockSize(0.0f)
		, mX(0)
		, mZ(0)
		, mTerrainMesh(nullptr)
		, mCurrentEnemyNumber(0)
		, mMaxEnemyNumber(0)
		, mVisibleEnemyNumber(3)
	{
		mMainPlayer = new EPlayerController(this);
		mMainPlayer->setPosition(InitPosition);

		EBullet* bullet = new EBullet(nullptr, "RocketBullet.mesh", this);
		bullet->setVisible(false);
		bullet = new EBullet(nullptr, "BallBullet.mesh", this);
		bullet->setVisible(false);
	}

	EGameManager::~EGameManager()
	{
		SafeDelete(mMainPlayer);
		for (BulletIter itr = mBullets.begin(); itr != mBullets.end(); ++itr)
		{
			SafeDelete(*itr);
		}

		for (TankIter itr == mTanks.begin(); itr != mTanks.end(); ++itr)
		{
			SafeDelete(*itr);
		}

		mBullets.clear();
		mTanks.clear();
	}

	void EGameManager::startGame(EInt maxEnemyNumber)
	{
		//清理当前的子弹和坦克
		for (BulletIter itr = mBullets.begin(); itr != mBullets.end(); ++itr)
		{
			(*itr)->mCurrentLive = (*itr)->mMaxLive + 1;
		}

		for (TankIter itr = mTanks.begin(); itr != mTanks.end(); ++itr)
		{
			(*itr)->mCurrentLive = (*itr)->mMaxLive + 1;
		}

		mMaxEnemyNumber = maxEnemyNumber;
		mCurrentEnemyNumber = 0;
	}

	EBool EGameManager::finishGame() const
	{
		return mCurrentEnemyNumber == mMaxEnemyNumber;
	}

	EBullet* EGameManager::createBullet(ETank* owner)
	{
		EString meshname = (owner->getBulletType() == BulletType::BULLET_ROCKET ? Bullet_Rocket : Bullet_Ball);
		EBullet* bullet = new EBullet(owner, meshname, this);
		if (meshname == Bullet_Rocket)
		{
			//268页面
		}
	}





}