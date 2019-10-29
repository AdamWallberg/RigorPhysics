#pragma once

#include "Constraint.h"
#include "Objects/Particle.h"

namespace rg
{

class SpringConstraint : public Constraint
{
public:
	SpringConstraint(Particle* p0, Particle* p1, float constant);
	void apply() override;
	Particle* getP0() const { return p0; }
	Particle* getP1() const { return p1; }
private:
	Particle* p0;
	Particle* p1;
	float restLength;
	float constant;
};

}