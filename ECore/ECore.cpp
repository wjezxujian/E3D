#include "ECore.h"
#include "EFrustum.h"
#include "EGraphics.h"
#include "ELight.h"
#include "EMaterial.h"

namespace E3D
{
	EVertex4D::EVertex4D()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(1.0f)
		, u(0.0f)
		, v(0.0f)
	{
	}

	EVertex4D::EVertex4D(const EVector4D& v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(v.w)
		, u(0.0f)
		, v(0.0f)
	{
	}

	EVertex4D::EVertex4D(EFloat xf, EFloat yf, EFloat zf)
		:x(xf)
		, y(yf)
		, z(zf)
		, w(1)
		, u(0.0f)
		, v(0.0f)
	{
	}

	EVertex4D EVertex4D::operator*(const EVector4D& right)
	{
		EVertex4D temp = *this;
		temp.x *= right.x;
		temp.y *= right.y;
		temp.z *= right.z;
		return temp;
	}

	EVertex4D EVertex4D::operator-(const EVertex4D& right)
	{
		EVertex4D temp = *this;
		temp.x -= right.x;
		temp.y -= right.y;
		temp.z -= right.z;
		return temp;
	}

	EVertex4D EVertex4D::operator+(const EVector4D& right)
	{
		EVertex4D temp = *this;
		temp.x += right.x;
		temp.y += right.y;
		temp.z += right.z;
		return temp;
	}

	EVertex4D EVertex4D::operator+(const EVertex4D& right)
	{

		EVertex4D temp = *this;
		temp.x += right.x;
		temp.y += right.y;
		temp.z += right.z;
		return temp;
	}

	EVertex4D EVertex4D::operator/(EFloat factor)
	{
		EVertex4D temp = *this;
		temp.x /= factor;
		temp.y /= factor;
		temp.z /= factor;
		return temp;
	}

	EVertex4D& EVertex4D::operator=(const EVertex4D& right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
		w = right.w;
		u = right.u;
		v = right.v;
		return *this;
	}

	EVector4D EVertex4D::toVector4D() const
	{
		return EVector4D(x, y, z, w);
	}

	EPlane3D::EPlane3D(const EVector4D& p, const EVector4D& nor)
		: point(p)
	{
		normal = nor;
		normal.normalize();
	}

	EPlane3D& EPlane3D::operator=(const EPlane3D& right)
	{
		point = right.point;
		normal = right.normal;
		return *this;
	}

	EPolyon4D::EPolyon4D()
		:state(0)
		,attribute(0)
		,color(0xffffff)
		,verList(nullptr)
	{}

	EPolyonF4D::EPolyonF4D()
		:state(0)
		,attribute(0)
		,color(0xfffff)
		/*,pre(nullptr), next(nullptr)*/
	{}

	EObject4D::EObject4D()
		:nextObject(nullptr)
		,materialName(DEFAULT_NAME)
		,scale(1, 1, 1)
		,direction(EVector4D::UNIT_X)
		,needCull(true)
	{}

	void Tranform_Object4D(EObject4D* object, const EMatrix44& mat, OBJ_TRANSFORM_TYPE transformType /*, EBool transformBasis*/)
	{
		EObject4D* obj = object;
		switch (transformType)
		{
		case TRANSFORM_LOCAL:
			{
				while (obj)
				{
					//只对局部坐标进行变换
					for (EInt i = 0; i < obj->vertexNumber; ++i)
					{
						GetVertex4DMulMatrix44(obj->localList[i], mat, obj->localList[i]);
					}
					obj = obj->nextObject;
				}
			}
			break;
		case TRANSFORM_TRANS:
			{
				while (obj)
				{
					//将局部坐标变换后存储至变换后的坐标顶点列表
					for (EInt i = 0; i < obj->vertexNumber; ++i)
					{
						GetVertex4DMulMatrix44(obj->transformList[i], mat, obj->transformList[i]);
					}
					obj = obj->nextObject;
				}
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			{
				while (obj)
				{
					//将局部坐标变换后存储至变换后的坐标顶点列表
					for (EInt i = 0; i < obj->vertexNumber; ++i)
					{
						GetVertex4DMulMatrix44(obj->localList[i], mat, obj->transformList[i]);
					}
					obj = obj->nextObject;
				}
			}
			break;
		}
	}

	void Transform_Renderlist4D(ERenderList4D* renderList, const EMatrix44& mat, OBJ_TRANSFORM_TYPE transformType)
	{
		EPolyonF4D* poly = nullptr;
		switch (transformType)
		{
		case TRANSFORM_LOCAL:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);
				
					GetVertex4DMulMatrix44(poly->localList[0], mat, poly->localList[0]);
					GetVertex4DMulMatrix44(poly->localList[1], mat, poly->localList[1]);
					GetVertex4DMulMatrix44(poly->localList[2], mat, poly->localList[2]);
				}
			}
			break;
		case TRANSFORM_TRANS:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);

					GetVertex4DMulMatrix44(poly->transformList[0], mat, poly->transformList[0]);
					GetVertex4DMulMatrix44(poly->transformList[1], mat, poly->transformList[1]);
					GetVertex4DMulMatrix44(poly->transformList[2], mat, poly->transformList[2]);
				}
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);
					GetVertex4DMulMatrix44(poly->localList[0], mat, poly->transformList[0]);
					GetVertex4DMulMatrix44(poly->localList[1], mat, poly->transformList[1]);
					GetVertex4DMulMatrix44(poly->localList[2], mat, poly->transformList[2]);
				}
			}
			break;	
		}
	}

	void Inert_Object4D_To_RenderList4D(ERenderList4D* renderList, EObject4D* object, OBJ_TRANSFORM_TYPE transformType, bool transformScaleAndPosition)
	{
		if (!object)
			return;

		EVector4D scale(1, 1, 1);
		EVector4D pos(0, 0, 0);

		if (transformScaleAndPosition)
		{
			scale = object->scale;
			pos = object->worldPosition;

		}

		//这里备份灯光的数据
		ELight* light = nullptr;
		for (LightItr itr = GLights->begin(); itr != GLights->end(); ++itr)
		{
			light = *itr;
			light->transPosition = light->position;
			light->transDirection = light->direction;
		}

		EObject4D* obj = object;
		EPolyon4D* base;
		EPolyonF4D poly;
		switch (transformType)
		{
		case TRANSFORM_LOCAL:
			while (obj)
			{
				for (EInt i = 0; i < obj->polyonNumber; ++i)
				{
					base = &obj->polyonList[i];

					poly.attribute = base->attribute;
					poly.state = EPOLY_STATE_ACTIVE;
					poly.color = base->color;

					poly.localList[0] = obj->localList[base->verIndex[0]];
					poly.localList[1] = obj->localList[base->verIndex[1]];
					poly.localList[2] = obj->localList[base->verIndex[2]];

					//材质设置
					poly.material = GetMaterial(obj->materialName);

					renderList->polyData.push_back(poly);
				}
				obj = obj->nextObject;
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			while (obj)
			{
				for (EInt i = 0; i < obj->polyonNumber; ++i)
				{
					base = &obj->polyonList[i];

					poly.attribute = base->attribute;
					poly.state = EPOLY_STATE_ACTIVE;
					poly.color = base->color;

					poly.transformList[0] = obj->localList[base->verIndex[0]] * scale + pos;
					poly.transformList[1] = obj->localList[base->verIndex[1]] * scale + pos;
					poly.transformList[2] = obj->localList[base->verIndex[2]] * scale + pos;

					//设置材质
					poly.material = GetMaterial(obj->materialName);

					renderList->polyData.push_back(poly);
				}
				obj = obj->nextObject;
			}
			break;
		case TRANSFORM_TRANS:
			while (obj)
			{
				for (EInt i = 0; i < obj->polyonNumber; ++i)
				{
					base = &obj->polyonList[i];

					poly.attribute = base->attribute;
					poly.state = EPOLY_STATE_ACTIVE;
					poly.color = base->color;

					poly.transformList[0] = obj->transformList[base->verIndex[0]] * scale + pos;
					poly.transformList[1] = obj->transformList[base->verIndex[1]] * scale + pos;
					poly.transformList[2] = obj->transformList[base->verIndex[2]] * scale + pos;

					//设置材质
					poly.material = GetMaterial(obj->materialName);

					renderList->polyData.push_back(poly);
				}
				obj = obj->nextObject;
			}
			break;
		}
	}

	void Local_To_World_Object4D(EObject4D* object, OBJ_TRANSFORM_TYPE transformType)
	{
		if (!object)
			return;

		EObject4D* obj = object;
		EVector4D pos = obj->worldPosition;
		if (TRANSFORM_LOCAL_TO_TRANS == transformType)
		{
			while (obj)
			{
				for (EInt i = 0; i < obj->vertexNumber; ++i)
				{
					//设置顶点的缩放值，不在保留坐标设置
					GetVertex4DAddVector4D(obj->localList[i] * obj->scale, pos, obj->transformList[i]);
				}
				obj = obj->nextObject;
			}
		}
		else if (TRANSFORM_TRANS == transformType)
		{
			while (obj)
			{
				for (EInt i = 0; i < obj->vertexNumber; ++i)
				{
					GetVertex4DAddVector4D(obj->transformList[i], pos, obj->transformList[i]);
				}
				obj = obj->nextObject;
			}
		}
	}

	void Local_To_World_RenderList4D(ERenderList4D* renderList, const EVector4D& pos, OBJ_TRANSFORM_TYPE transformType)
	{
		EPolyonF4D* poly = nullptr;
		switch (transformType)
		{
		case TRANSFORM_LOCAL:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);

					GetVertex4DAddVector4D(poly->localList[0], pos, poly->localList[0]);
					GetVertex4DAddVector4D(poly->localList[1], pos, poly->localList[1]);
					GetVertex4DAddVector4D(poly->localList[2], pos, poly->localList[2]);
				}
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);
					GetVertex4DAddVector4D(poly->localList[0], pos, poly->transformList[0]);
					GetVertex4DAddVector4D(poly->localList[1], pos, poly->transformList[1]);
					GetVertex4DAddVector4D(poly->localList[2], pos, poly->transformList[2]);
				}
			}
			break;
		case TRANSFORM_TRANS:
			{
				for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(); ++itr)
				{
					poly = &(*itr);
					GetVertex4DAddVector4D(poly->transformList[0], pos, poly->transformList[0]);
					GetVertex4DAddVector4D(poly->transformList[1], pos, poly->transformList[1]);
					GetVertex4DAddVector4D(poly->transformList[2], pos, poly->transformList[2]);
				}
			}
			break;

		}
	}

	bool Cull_Object4D(EObject4D* object, EFrustum* camera, CULL_TYPE cullType /* = CULL_SPHERE */)
	{
		if (!object)
			return true;

		if (!object->needCull)
			return false;

		//先把当前物体的坐标变换成相机坐标
		EVector4D centerPos;
		GetVector4DMulMatrix44(object->worldPosition, camera->mWorldToCamera, centerPos);
		
		//首先把半径进行缩放
		EFloat scaleRadiusZ;
		EFloat scaleRadiusX;
		EFloat scaleRadiusY;

		if (cullType == CULL_SPHERE)
		{
			scaleRadiusZ = object->maxRadius * object->scale.z;
			scaleRadiusX = object->maxRadius * object->scale.x;
			scaleRadiusY = object->maxRadius * object->scale.y;
		}
		else if (cullType == CULL_BOX)
		{
			//各剔除偏移以做大顶点的各值为基准
			scaleRadiusZ = object->maxBoundingBox.z * object->scale.z;
			scaleRadiusX = object->maxBoundingBox.x * object->scale.x;
			scaleRadiusY = object->maxBoundingBox.y * object->scale.y;
		}
		else
			return true;

		//远近绵剔除
		if ((centerPos.z + scaleRadiusZ) < camera->clip_z_near || (centerPos.z - scaleRadiusZ) > camera->clip_z_far)
		{
			return true;
		}

		//左右面剔除
		//这里的测试基于在xz平面的投影来计算的
		EFloat x_test = 0.5f * camera->viewplane_width * centerPos.z / camera->view_dist;
		if ((centerPos.x - scaleRadiusZ) > x_test || (centerPos.x + scaleRadiusX) < -x_test)
			return true;

		//上下面剔除
		//这里的测试是基于在zy平面的投影来计算的
		EFloat y_test = 0.5f * camera->viewplane_height * centerPos.z / camera->view_dist;
		if ((centerPos.y - scaleRadiusY) > y_test || (centerPos.y + scaleRadiusY) < -y_test)
			return true;
		return false;
	}

	void World_To_Camera_Object4D(EObject4D* object, EFrustum* camera)
	{
		EObject4D* obj = object;
		while (obj)
		{
			for (EInt i = 0; i < obj->vertexNumber; i++)
			{
				GetVertex4DMulMatrix44(obj->transformList[i], camera->mWorldToCamera, obj->transformList[i]);
			}
			obj = obj->nextObject;
		}
	}

	void World_To_Camera_RenderList4D(ERenderList4D* renderList, EFrustum* camera)
	{
		//这里对灯光位置进行变换，将其变换到相机坐标系下面
		EMatrix44 mat = camera->mWorldToCamera;
		//这里只保留旋转变换，而不进行平移变换，否则会出现灯光跟随摄像机移动的效果
		mat.m[3][0] = mat.m[3][1] = mat.m[3][2] = 0;

		ELight* light = nullptr;
		for (LightItr itr = GLights->begin(); itr != GLights->end(); ++itr)
		{
			light = *itr;
			GetVector4DMulMatrix44(light->position, mat, light->transPosition);
			GetVector4DMulMatrix44(light->direction, mat, light->transDirection);
		}

		EPolyonF4D* poly = nullptr;
		for (ERenderList4D::Itr itr = renderList->polyData.begin(); itr != renderList->polyData.end(), ++itr)
		{
			poly = &(*itr);

			GetVertex4DMulMatrix44(poly->transformList[0], camera->mWorldToCamera, poly->transformList[0]);
			GetVertex4DMulMatrix44(poly->transformList[1], camera->mWorldToCamera, poly->transformList[1]);
			GetVertex4DMulMatrix44(poly->transformList[2], camera->mWorldToCamera, poly->transformList[2])
		}
	}



	
}