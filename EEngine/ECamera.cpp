#include "ECamera.h"
#include "EFrustum.h"

namespace E3D
{
	ECamera::ECamera()
		: mLockTarget(false)
		, mNeedUpdate(true)
		, mRenderMode(RenderMode::RENDER_SOILD)
	{
		mFrustum = new EFrustum(CAMERA_MODLE_UVN, EVector4D::ZERO, EVector4D::ZERO, EVector4D::ZERO, 10, 1000, 75, SCREEN_WIDTH, SCREEN_HEIGHT);

		update();
	}

	ECamera::~ECamera()
	{
		SafeDelete(mFrustum);
	}

	void ECamera::update()
	{
		if (mNeedUpdate)
		{
			EMatrix44 mt_inv;
			GetTranslateMatrix44(mt_inv, -mFrustum->position.x, -mFrustum->position.y, -mFrustum->position.z);
			mFrustum->camLook = mFrustum->camTarget - mFrustum->position;
			mFrustum->camUp = EVector4D::UNIT_Y;
			mFrustum->camRight = mFrustum->camUp.crossProduct(mFrustum->camLook);
			mFrustum->camUp = mFrustum->camLook.crossProduct(mFrustum->camRight);

			mFrustum->camLook.normalize();
			mFrustum->camRight.normalize();
			mFrustum->camUp.normalize();

			EMatrix44 mt_uvn(	mFrustum->camRight.x, mFrustum->camUp.x, mFrustum->camLook.x, 0,
								mFrustum->camRight.y, mFrustum->camUp.y, mFrustum->camLook.y, 0,
								mFrustum->camRight.z, mFrustum->camUp.z, mFrustum->camLook.z, 0,
								0, 0, 0, 0);

			mFrustum->mWorldToCamera = mt_inv * mt_uvn;

			mNeedUpdate = true;
		}
	}

	void ECamera::setZNear(EFloat znear)
	{
		mFrustum->clip_z_near = znear;
		mNeedUpdate = true;
	}

	void ECamera::setZFar(EFloat zfar)
	{
		mFrustum->clip_z_far = zfar;
		mNeedUpdate = true;
	}

	void ECamera::setPosition(const EVector3D& pos)
	{
		mFrustum->position.x = pos.x;
		mFrustum->position.y = pos.y;
		mFrustum->position.z = pos.z;

		mNeedUpdate = true;
	}

	void ECamera::setTarget(const EVector3D& target, EBool lockTarget)
	{
		mFrustum->camTarget.x = target.x;
		mFrustum->camTarget.y = target.y;
		mFrustum->camTarget.z = target.z;

		mLockTarget = lockTarget;
		mNeedUpdate = true;
	}

	//基于世界坐标系移动
	void ECamera::move(const EVector3D& mov)
	{

	}
}