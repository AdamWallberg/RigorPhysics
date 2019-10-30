#pragma once

#include "Math.hpp"

#include <vector>

namespace rg
{

typedef std::vector<Vector3> PointList;

static float timeStep = 1.0f / 60.0f;

inline PointList generateConvexHull(PointList points)
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

	return hull;
}

inline Vector3 getCenterOfMass(PointList points)
{
	Vector3 center = ZeroVector;
	for (const Vector3& p : points)
	{
		center += p;
	}
	center /= points.size();
	return center;
}

}