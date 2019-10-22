#pragma once

#include "Math.hpp"

#include <vector>

namespace rg
{

class ConvexHull
{
public:
	typedef std::vector<Vector3> PointList;
	typedef std::vector<int> IndexList;
	
	ConvexHull(const PointList& points, Vector3 position);
	void generateConvexHull(PointList points);
	const PointList& getPoints() const { return points; }
	const Vector3 getPosition() const { return position; }
private:
	void generatePositionFromCenterOfMass();
	void fillInitialClosedList(PointList& closedList, const PointList& points);
	PointList::const_iterator getPointWithGreatesAngle(
		Vector3 p0, PointList::iterator p1, const PointList& points);
	PointList points;
	Vector3 position;
};

}