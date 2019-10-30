#pragma once

#include "Particle.h"
#include "ConvexHull.h"


namespace rg
{

class PointMass : public Particle
{
public:
	typedef std::vector<Vector3> PointList;
	PointMass(Vector3 position, float mass, float damp, PointList points);
	void update() override;
	const PointList& getPoints() const { return points; }
private:
	PointList points; // local space
	AABBox bounds;
};

}