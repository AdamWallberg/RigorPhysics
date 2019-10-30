#include "ConvexHull.h"

#include <algorithm>
#include <assert.h>
#include <stack>

namespace rg
{

ConvexHull::ConvexHull(const PointList& points, Vector3 position)
	: points(points)
	, position(position)
{
}

void ConvexHull::normalizePosition()
{
	updateAABB();
	Vector3 center = getCenterOfMass();
	position = center;
	for (auto& p : points)
	{
		p -= center;
	}
}

void ConvexHull::generateConvexHull(PointList points)
{
	// Gift Wrapping, or Jarvis's Algorithm
	assert(points.size() >= 3);
	PointList hull;

	int l = 0;
	for (unsigned int i = 1; i < points.size(); i++)
		if (points[i].x < points[l].x)
			l = i;
	
	int p = l;
	int q;
	do
	{
		hull.push_back(points[p]);
		q = (p + 1) % points.size();
		for (unsigned int i = 0; i < points.size(); i++)
		{
			if (orientation(points[p], points[i], points[q]) == 1)
				q = i;
		}
		p = q;
	} while (p != l);

	this->points = hull;
	normalizePosition();
}

const Vector3 ConvexHull::getCenterOfMass() const
{
	Vector3 center = ZeroVector;
	for (const Vector3& p : points)
	{
		center += p;
	}
	center /= points.size();
	center += position;
	return center;
}

void ConvexHull::updateAABB()
{
	float inf = std::numeric_limits<float>::infinity();
	Vector3 min(inf, inf, inf);
	Vector3 max(-inf, -inf, -inf);
	for (const Vector3& p : points)
	{
		if (p.x < min.x) min.x = p.x;
		if (p.x > max.x) max.x = p.x;
		if (p.y < min.y) min.y = p.y;
		if (p.y > max.y) max.y = p.y;
		if (p.z < min.z) min.z = p.z;
		if (p.z > max.z) max.z = p.z;
	}
	bounds = AABBox(min, max);
}

}
