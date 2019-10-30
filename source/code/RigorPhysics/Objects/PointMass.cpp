#include "PointMass.h"

namespace rg
{

PointMass::PointMass(Vector3 position, float mass, float damp, PointList points)
	: Particle(position, mass, damp)
	, points(points)
{
}

void PointMass::update()
{
	Particle::update();
}

}
