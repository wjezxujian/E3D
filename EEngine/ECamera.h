#pragma once
#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D
{
	class EFrustum;

	enum class RenderMode
	{
		RENDER_WIRE,	//线框渲染
		RENDER_SOILD,	//实体渲染
	};

	class ECamera
	{
	public:
		~ECamera();

		void update();

		//设置近裁剪面距离
		void setZNear(EFloat znear);
		//设置远裁剪面距离
		void setZFar(EFloat zfar);

		//设置相机世界坐标
		void setPosition(const EVector3D& pos);
		//设置摄像机观察点，当lockTarget为true时，锁定观察点
		void setTarget(const EVector3D& target, EBool lockTarget = false);
		void releaseTarget() { mLockTarget = false; }

		//基于世界坐标系移动
		void move(const EVector3D& mov);
		//基于摄像机自身坐标移动
		void moveRelative(const EVector3D& mov);

		//绕y轴旋转
		void yaw(EFloat yDegree);
		//绕x轴旋转
		void pitch(EFloat pDegree);

		//设置渲染模式，线框或实体
		void setRenderMode(RenderMode mode) { mRenderMode = mode; }
		RenderMode getRenderMode() const { return mRenderMode; }

		EFrustum* getFrustum() const { return mFrustum; }

	protected:
		friend class ESceneManager;
		ECamera();

	protected:
		EFrustum* mFrustum;

		EBool mLockTarget;
		EBool mNeedUpdate;

		RenderMode mRenderMode;
	};

}