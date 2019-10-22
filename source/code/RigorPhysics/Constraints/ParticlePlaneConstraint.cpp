#include "ParticlePlaneConstraint.h"

namespace rg
{

ParticlePlaneConstraint::ParticlePlaneConstraint(Particle* particle, Plane* plane)
	: particle(particle)
	, plane(plane)
{
}

void ParticlePlaneConstraint::apply()
{
	float relation = plane->relation(particle->getPosition());
	if (relation < 0.0f)
	{
		particle->move(plane->normal * -relation);
	}
}

}