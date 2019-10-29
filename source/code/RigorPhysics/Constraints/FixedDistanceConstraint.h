#pragma once

#include "Constraint.h"
#include "Objects/Particle.h"

namespace rg
{

class FixedDistanceConstraint : public Constraint
{
public:
	FixedDistanceConstraint(Particle* p0, Particle* p1);
	void apply() override;
	Particle* getP0() const { return p0; }
	Particle* getP1() const { return p1; }
private:
	Particle* p0;
	Particle* p1;
	float distance;
};

}