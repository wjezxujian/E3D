#include "EMesh.h"
#include "EMeshUtil.h"
#include "EMatrix.h"

namespace E3D
{
	EMesh::EMesh()
		: mObject(nullptr)
		, mSubmeshNumber(1)
		, mCollsionType(COLLSION_TYPE::COLLSION_COLLSION)
		, mPolyonNumber(0)
		, mVertexNumber(0)
		, mRotate(0, 0, 0)
		, mIsVisible(true)
	{

	}

	EMesh::EMesh(const EString& name, const EString& meshName)
		: mSubmeshNumber(0)
		, mPolyonNumber(0)
		, mVertexNumber(0)
		, mRotate(0, 0, 0)
		, mCollsionType(COLLSION_TYPE::COLLSION_COLLSION)
		, mIsVisible(true)
	{
		mName = name;
		mObject = LoadOgreMesh(meshName);

		if (!mObject)
		{
			EString errorInfo = "Mesh #" + meshName + " Not Found";
			throw errorInfo;
		}

		EObject4D* obj = mObject;
		while (obj)
		{
			mSubmeshNumber++;
			mPolyonNumber += obj->polyonNumber;
			mVertexNumber += obj->vertexNumber;
			obj = obj->nextObject;
		}
	}

	EMesh::~EMesh()
	{
		SafeDelete(mObject);
	}

	void EMesh::setScale(const EVector3D& scale)
	{
		mObject->scale = EVector4D(scale.x, scale.y, scale.z);
	}

	void EMesh::setPosition(const EVector3D& pos)
	{
		mObject->worldPosition = EVector4D(pos.x, pos.y, pos.z, pos.z);
	}

	EVector3D EMesh::getPosition() const
	{
		EVector4D pos = mObject->worldPosition;
		return EVector3D(pos.x, pos.y, pos.z);
	}

	void EMesh::move(const EVector3D& mov)
	{
		mObject->worldPosition = mObject->worldPosition + EVector4D(mov.x, mov.y, mov.z);
	}

	//ÈÆyÖáÐý×ª
	void EMesh::yaw(EFloat yDegree)
	{
		mRotate.y = yDegree;
		EMatrix44 rotMat;
		GetRotateMatrix44Y(rotMat, yDegree);
		Tranform_Object4D(mObject, rotMat, TRANSFORM_LOCAL_TO_TRANS);
	}

	//ÈÆzÖáÐý×ª
	void EMesh::roll(EFloat rDegree)
	{
		mRotate.z = rDegree;
		EMatrix44 rotMat;
		GetRotateMatrix44Z(rotMat, rDegree);
		Tranform_Object4D(mObject, rotMat, TRANSFORM_LOCAL_TO_TRANS);
	}

	//ÈÆxÖáÐý×ª
	void EMesh::pitch(EFloat pDegree)
	{
		mRotate.x = pDegree;
		EMatrix44 rotMat;
		GetRotateMatrix44X(rotMat, pDegree);
		Tranform_Object4D(mObject, rotMat, TRANSFORM_LOCAL_TO_TRANS);
	}

	EMaterial* EMesh::getMaterial(EInt index)
	{
		if (index < 0 || index >= mSubmeshNumber)
			return nullptr;

		EObject4D* object = mObject;
		EInt temp = 0;
		while (temp < index)
		{
			temp++;
			object = object->nextObject;
		}

		if (object)
			return GetMaterial(object->materialName);

		return nullptr;
	}

	void EMesh::setMaterial(EInt index, EString matName)
	{
		if (index < 0 || index >= mSubmeshNumber)
			return;

		EObject4D* object = mObject;
		EInt temp = 0;
		while (temp < index)
		{
			temp++;
			object = object->nextObject;
		}

		if (object)
			object->materialName = matName;
	}

	EBool EMesh::intersect(const EVector3D& point)
	{
		EFloat x = Abs(mObject->maxBoundingBox.x) * mObject->scale.x / 2.0f;
		EFloat y = Abs(mObject->maxBoundingBox.y) * mObject->scale.y / 2.0f;
		EFloat z = Abs(mObject->maxBoundingBox.z) * mObject->scale.z / 2.0f;

		if (point.x < mObject->worldPosition.x - x || point.x > mObject->worldPosition.x + x)
			return false;

		//190Ò³
	}






}