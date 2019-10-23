#include "SpringConstraint.h"

namespace rg
{

SpringConstraint::SpringConstraint(Particle* p0, Particle* p1, float constant)
	: p0(p0)
	, p1(p1)
	, constant(constant)
{
	restLength = glm::distance(p0->getPosition(), p1->getPosition());
}

void SpringConstraint::apply()
{
	Vector3 force = p1->getPosition() - p0->getPosition();
	float magnitude = (glm::length(force) - restLength) * constant;
	force = glm::normalize(force);
	force *= magnitude;
	p0->addForceUnscaled(force);
	p1->addForceUnscaled(-force);
}

}