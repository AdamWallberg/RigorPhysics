#pragma once

#include "Math.hpp"
#include "AABBox.h"

#include <vector>

namespace rg
{

class ConvexHull
{
public:
	typedef std::vector<Vector3> PointList;
	
	ConvexHull(const PointList& points, Vector3 position);
	void normalizePosition();
	void generateConvexHull(PointList points);
	const PointList& getPoints() const { return points; }
	const Vector3 getCenterOfMass() const;
	const AABBox getBounds() const { return bounds; }

	Vector3 position;
private:
	void updateAABB();

	PointList points;
	AABBox bounds;
};

}