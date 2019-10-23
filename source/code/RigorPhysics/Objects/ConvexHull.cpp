#include "ConvexHull.h"

#include <algorithm>
#include <assert.h>

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

void ConvexHull::generateConvexHull(PointList points)
{
	assert(points.size() >= 2);
	Vector3 center = getCenterOfMass();
	sortByAngle(points, center);

	// Compare angles, and only keep counterclockwise angles
	for(int curr = 0; curr < points.size(); curr++)
	{
		int n = points.size();
		int prev = (((curr - 1) % n) + n) % n;
		int next = (curr + 1) % points.size();

		Vector3 v0 = points[prev];
		Vector3 v1 = points[curr];
		Vector3 v2 = points[next];

		Vector3 reference = center - v0;
		float angle = angleBetween(v1 - v0, v2 - v0);
		if (angle < PI)
		{
			points.erase(points.begin() + curr);
			curr--;
		}
	}

	this->points = points;
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
