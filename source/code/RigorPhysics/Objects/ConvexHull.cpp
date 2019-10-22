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

void ConvexHull::generateConvexHull(PointList points) // WARNING: Not finished!
{
	assert(points.size() >= 4);

	PointList closedList;

	fillInitialClosedList(closedList, points);

	int i = 0;
	while (closedList.size() > 0)
	{
		Vector3 p0 = closedList[i];
		Vector3 p1 = closedList[i + 1]; //TODO: this won't work for last element
		Vector3 diff = p1 - p0;
		Vector3 normal = glm::cross(glm::normalize(diff), Vector3(0.0f, 0.0f, -1.0f));

		// Get the points that are above
		PointList abovePoints;
		for (unsigned int j = 0; j < points.size(); j++)
		{
			if (j == i || j == i + 1) continue;
			Vector3 to = points[j] - p0;
			if (glm::cross(to, diff).z < 0.0f)
			{
				abovePoints.push_back(points[j]);
			}
		}

		auto nextPoint = getPointWithGreatesAngle(p0, closedList.begin() + i + 1, closedList);
		closedList[i + 1] = *nextPoint;
	}
}

void ConvexHull::generatePositionFromCenterOfMass()
{
	position = ZeroVector;
	for(const Vector3& p : points)
	{
		position += p;
	}
	position /= points.size();
}

void ConvexHull::fillInitialClosedList(PointList& closedList, const PointList& points)
{
	Vector3 minX, maxX, minY, maxY;

	// Find min and max of x and y respectively
#define COMP_VEC3(c) \
	[](const Vector3& v0, const Vector3& v1) -> bool { \
	return v0.c < v1.c;}

#define GET_EXTREME(val, comp, func) \
	it = std::func(points.begin(), points.end(), comp); \
	val = *it;

	PointList::const_iterator it;
	GET_EXTREME(minX, COMP_VEC3(x), min_element);
	GET_EXTREME(maxX, COMP_VEC3(x), max_element);
	GET_EXTREME(minY, COMP_VEC3(y), min_element);
	GET_EXTREME(maxY, COMP_VEC3(y), max_element);
#undef GET_EXTREME
#undef COMP_VEC3

	closedList.push_back(minY);
	closedList.push_back(maxX);
	closedList.push_back(maxY);
	closedList.push_back(minX);
}

// O(N)
ConvexHull::PointList::const_iterator ConvexHull::getPointWithGreatesAngle(
	Vector3 p0, PointList::iterator p1, const PointList& points)
{
	Vector3 to0 = *p1 - p0;
	PointList::const_iterator greatestPoint = p1;
	float greatestDifference = 1.0f;
	for (auto it = points.begin(); it < points.end(); it++)
	{
		Vector3 to1 = *it - p0;
		float d = glm::dot(to0, to1);
		if (d < greatestDifference)
		{
			greatestDifference = d;
			greatestPoint = it;
		}
	}
	return greatestPoint;
}

}
