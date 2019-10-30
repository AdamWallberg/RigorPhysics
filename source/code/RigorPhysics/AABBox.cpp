#include "AABBox.h"

namespace rg
{

AABBox::AABBox()
	: min(ZeroVector)
	, max(ZeroVector)
{
}

AABBox::AABBox(Vector3 min, Vector3 max)
	: min(min)
	, max(max)
{
}

bool AABBox::inside(const Vector3& position) const
{
	return
		position.x >= min.x && position.x <= max.x &&
		position.y >= min.y && position.y <= max.y &&
		position.z >= min.z && position.z <= max.z;
}

}