#include "ELight.h"

namespace E3D
{
	ELight::ELight(EInt lightId, LIGHT_TYPE type)
		:id(lightId)
		,lightOn(true)
		,lightType(type)
		,ambient(255,255,255)
		,diffuse(255,255,255)
		,specular(255,255,255)
		,position(0,0,0)
		,direction(0,0,1)
		,kc(1.0f)
		,kl(1.0f)
		,kq(0.0f)
		,spot_inner(45.0f)
		,spot_outer(60.f)
		,power(1.0f)
		,shadowFactor(0.05f)
	{}

	std::vector<ELight*>* GLights = nullptr;
	//创建灯光
	EInt CreateLight(LIGHT_TYPE lightType)
	{
		if (GLights == nullptr)
			GLights = new std::vector<ELight*>;

		if ((EInt)GLights->size() > MAX_LIGHTS)
			return -1;

		EInt id = (EInt)GLights->size();
		GLights->push_back(new ELight(id, lightType));
		
		return id;
	}

	//获得一个灯光，如果灯光不存在，则创建一个新灯光并返回
	ELight* GetLight(EInt id)
	{
		if (GLights == nullptr || GetLightSize() > MAX_LIGHTS
			|| id < 0 || id >GetLightSize() - 1)
			return nullptr;
		return GLights->at(id);
	}

	//获取灯光大小
	EInt GetLightSize()
	{
		return (EInt)GLights->size();
	}

	//删除所有灯光
	void DestroyAllLights()
	{
		for (LightItr itr = GLights->begin(); itr != GLights->end(); ++itr)
			SafeDelete(*itr);

		GLights->clear();
		SafeDelete(GLights);
	}
}