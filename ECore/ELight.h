#pragma once

#include "ECommon.h"
#include "EVector.h"
namespace E3D
{
	enum class LIGHT_TYPE
	{
		LIGHT_AMEIENT = 0,		//环境光
		LIGHT_DIRECTION = 1,	//平行光
		LIGHT_POINT = 2,		//点光源
	};

	struct ELight
	{
		EInt		id;				//灯光的分配ID，全局唯一
		EBool		lightOn;		//灯光是否启用

		LIGHT_TYPE	lightType;		//灯光类型
		EFloat		power;			//灯光的强度，默认为1.0f
		EFloat		shadowFactor;	//灯光背面强度，默认为0.05f
		EColor		ambient;		//灯光的环境色（环境光使用）
		EColor		diffuse;		//灯光漫反射颜色
		EColor		specular;		//灯光高光颜色

		EVector4D	position;		//灯光世界坐标位置
		EVector4D	direction;		//光源朝向，电灯光无效
		EVector4D	transPositon;	//灯光摄像机坐标系位置
		EVector4D	transDirection;	//摄像机坐标系光源朝向，电灯光无效

		EFloat		kc, kl, kq;		//衰减因子

		EFloat		spot_inner;		//聚光灯内锥角
		EFloat		

	};


}