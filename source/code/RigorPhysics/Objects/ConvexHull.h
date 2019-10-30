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
	void sortByAngle(PointList& points, Vector3 center);
	void updateAABB();
	float angleBetween(Vector3 v0, Vector3 v1);

	PointList points;
	AABBox bounds;
};

}