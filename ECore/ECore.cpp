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


	
}