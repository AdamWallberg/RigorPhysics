#pragma once

#include "Constraint.h"
#include "Objects/PointMass.h"

namespace rg
{

class PointMassConstraint : public Constraint
{
public:
	PointMassConstraint(PointMass* p0, PointMass* p1);
	void apply() override;
private:
	PointMass* p0;
	PointMass* p1;
};

}