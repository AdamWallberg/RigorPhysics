#include "Plane.h"

namespace rg 
{

Plane::Plane(Vector3 position, Vector3 normal)
	: position(position)
	, normal(normal)
{
}

float Plane::relation(Vector3 position) const
{
	const Vector3 thisToPos = position - this->position;
	const Vector3 proj = glm::proj(thisToPos, normal);
	float dist = glm::length(proj);
	dist *= glm::sign(glm::dot(proj, normal));
	return dist;
}

}