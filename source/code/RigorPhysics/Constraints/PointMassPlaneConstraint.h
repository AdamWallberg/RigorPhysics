#pragma once

#include "Constraint.h"
#include "Objects/PointMass.h"
#include "Objects/Plane.h"

namespace rg
{

class PointMassPlaneConstraint : public Constraint
{
public:
	PointMassPlaneConstraint(PointMass* pointMass, Plane* plane);
	void apply() override;
private:
	PointMass* pointMass;
	Plane* plane;
};

}