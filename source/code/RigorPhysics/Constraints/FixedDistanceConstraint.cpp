#include "FixedDistanceConstraint.h"

namespace rg
{

FixedDistanceConstraint::FixedDistanceConstraint(Particle * p0, Particle * p1)
	: p0(p0)
	, p1(p1)
{
	distance = glm::distance(p0->getPosition(), p1->getPosition());
}

void FixedDistanceConstraint::apply()
{
	Vector3 dir = p1->getPosition() - p0->getPosition();
	float currentDistance = glm::length(dir);
	dir = glm::normalize(dir);
	dir *= (distance - currentDistance) * 0.5f;
	p0->move(-dir);
	p1->move(dir);
}

}