#include "PointMassPlaneConstraint.h"

namespace rg
{

PointMassPlaneConstraint::PointMassPlaneConstraint(
	PointMass* pointMass, Plane* plane)
	: pointMass(pointMass)
	, plane(plane)
{
}

void PointMassPlaneConstraint::apply()
{
	Vector3 normal = plane->normal;
	float planeProj = glm::dot(normal, plane->position);

	float min = std::numeric_limits<float>::infinity();
	Vector3 minPos;
	for (const Vector3& p : pointMass->getPoints())
	{
		float proj = glm::dot(normal, p + pointMass->getPosition());
		if (proj < min)
		{
			min = proj;
			minPos = p;
		}
	}

	if (min < planeProj)
	{
		float overlap = plane->relation(minPos + pointMass->getPosition());
		pointMass->move(plane->normal * -overlap);
	}
}

}