#pragma once

#include "EObject.h"
#include "ESceneManager.h"
#include <list>

namespace E3D
{
	//子弹类型
	enum class BulletType
	{
		BULLET_BALL,	//球形子弹
		BULLET_ROCKET,	//火箭型子弹
	};

	//坦克类型
	enum class TankType
	{
		TANK_AI, 
		TANK_PLAYER,
	};

	//Tank的基类，Tank分两部分，一部分是脑袋，一部分是车身，脑袋可以旋转
	//脑袋是基于车身移动的
	class EBullet;
	class ECamera;
	class EGameManeger;
	class ETank : public EObject
	{
		typedef std::list<EBullet*>::iterator BulletIter;

	public:
		virtual ~ETank();

		//移动Tank
		void move(const EVector3D& mov);
		//向前移动Tank,按照当前Tank的朝向为前
		EBool moveUp();

		//向左转Tank车体
		void turnLeft();
		//向右转turnRight();

		//瞄准器向左转
		void fireAimLeft();
		//瞄准器向右转
		void fireAimRight();

		//获得当前Tank的世界坐标
		EVector3D getPosition() const { return mBody->getPosition(); }
		void setPosition(const EVector3D& pos);

		//Tank沿轴旋转，参数为角度
		void yaw(EFloat degree);
	};
}