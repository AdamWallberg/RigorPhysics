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
	Vector3 center = getCenterOfMass();
	position = center;
	for (auto& p : points)
	{
		p -= center;
	}
}

int orientation(Vector3 p, Vector3 q, Vector3 r)
{
	Vector3 cross = glm::cross(q - p, r - p);
	if (cross.z == 0.0f) return 0;
	return cross.z < 0.0f ? 1 : 2;
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

void ConvexHull::sortByAngle(PointList& points, Vector3 center)
{
	Vector3 reference = Vector3(0.0f, -1.0f, 0.0f);
	std::sort(points.begin(), points.end(),
		[this, center, reference](const Vector3& v0, const Vector3& v1) -> bool {
		return angleBetween(reference, v0 - center) > angleBetween(reference, v1 - center);
	});
}

float ConvexHull::angleBetween(Vector3 v0, Vector3 v1)
{
	const float dot = v0.x * v1.x + v0.y * v1.y;
	const float det = v0.x * v1.y - v0.y * v1.x;
	float angle = std::atan2(det, dot);
	if (angle < 0.0f)
	{
		angle += PI * 2.0f;
	}
	return angle;
}

}
