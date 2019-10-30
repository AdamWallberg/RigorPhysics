#pragma once

#include "Math.hpp"

namespace rg
{

class AABBox
{
public:
	AABBox();
	AABBox(Vector3 min, Vector3 max);
	const Vector3 getMin() const { return min; }
	const Vector3 getMax() const { return max; }

	bool inside(const Vector3& position) const;
private:
	Vector3 min;
	Vector3 max;
};

}
