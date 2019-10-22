#pragma once

#include "Constraint.h"
#include "Objects/Particle.h"
#include "Objects/ConvexHull.h"

namespace rg
{

class ParticleHullConstraint : public Constraint
{
public:
	ParticleHullConstraint(Particle* particle, ConvexHull* hull);
	void apply() override;
private:
	Particle* particle;
	ConvexHull* hull;
};

}