#include "ParticleHullConstraint.h"

#include "Objects/Plane.h"

namespace rg
{

ParticleHullConstraint::ParticleHullConstraint(
	Particle* particle, ConvexHull* hull)
	: particle(particle)
	, hull(hull)
{
}

void ParticleHullConstraint::apply()
{
	bool insideAABB = hull->getBounds().inside(particle->getPosition());
	if (!insideAABB)
		return;

	bool intersects = true;
	Vector3 intersection = ZeroVector;
	float minOverlap = std::numeric_limits<float>::infinity();

	const Vector3 particlePos = particle->getPosition() - hull->position;
	const ConvexHull::PointList& points = hull->getPoints();
	for (unsigned int i = 0; i < points.size(); i++)
	{
		const Vector3 current = points[i];
		const Vector3 next = points[(i + 1) % points.size()];
		const Vector3 edge = next - current;
		const Vector3 axis = Vector3(edge.y, -edge.x, 0.0f);

		float min = std::numeric_limits<float>::infinity();
		float max = -std::numeric_limits<float>::infinity();
		for (const auto& v : points)
		{
			float proj = glm::dot(axis, v);
			if (proj < min) min = proj;
			if (proj > max) max = proj;
		}

		float pos = glm::dot(axis, particlePos);
		if (pos < min || pos > max)
		{
			intersects = false;
			break;
		}

		Plane p(current, axis);
		float overlap = p.relation(particlePos);
		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			intersection = glm::normalize(axis) * -overlap;
		}
	}

	if (intersects)
	{
		particle->move(intersection);
	}
}

}