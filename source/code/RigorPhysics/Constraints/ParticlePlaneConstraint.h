#pragma once

#include "Constraint.h"
#include "Objects/Particle.h"
#include "Objects/Plane.h"

namespace rg
{

class ParticlePlaneConstraint : public Constraint
{
public:
	ParticlePlaneConstraint(Particle* particle, Plane* plane);
	void apply() override;
private:
	Particle* particle;
	Plane* plane;
};

}