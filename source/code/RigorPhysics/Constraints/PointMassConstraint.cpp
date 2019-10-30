#include "PointMassConstraint.h"

namespace rg
{

PointMassConstraint::PointMassConstraint(PointMass* p0, PointMass* p1)
	: p0(p0)
	, p1(p1)
{
}

void populateWithAxes(std::vector<Vector3>& axes, const std::vector<Vector3>& points)
{
	for (unsigned int i = 0; i < points.size(); i++)
	{
		const Vector3 current = points[i];
		const Vector3 next = points[(i + 1) % points.size()];
		const Vector3 edge = next - current;
		const Vector3 axis = Vector3(edge.y, -edge.x, 0.0f);
		axes.push_back(glm::normalize(axis));
	}
}

void PointMassConstraint::apply()
{
	bool intersects = true;
	float minOverlap = std::numeric_limits<float>::infinity();
	Vector3 moveDir;

	std::vector<Vector3> axes;
	populateWithAxes(axes, p0->getPoints());
	populateWithAxes(axes, p1->getPoints());

	for (unsigned int i = 0; i < axes.size(); i++)
	{
		const Vector3 axis = axes[i];
		float p0min = std::numeric_limits<float>::infinity();
		float p0max = -std::numeric_limits<float>::infinity();
		float p1min = std::numeric_limits<float>::infinity();
		float p1max = -std::numeric_limits<float>::infinity();

		for (const auto& v : p0->getPoints())
		{
			float proj = glm::dot(axis, v + p0->getPosition());
			if (proj < p0min) p0min = proj;
			if (proj > p0max) p0max = proj;
		}

		for (const auto& v : p1->getPoints())
		{
			float proj = glm::dot(axis, v + p1->getPosition());
			if (proj < p1min) p1min = proj;
			if (proj > p1max) p1max = proj;
		}

		if (p0max < p1min || p0min > p1max)
		{
			intersects = false;
			break;
		}

		float overlap = glm::min(p0max, p1max) - glm::max(p0min, p1min);
		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			moveDir = axis * overlap;
		}
	}

	if (intersects)
	{
		if (glm::dot(p0->getPosition() - p1->getPosition(), moveDir) < 0.0f)
			moveDir *= -1.0f;
		p0->move(moveDir * 0.5f);
		p1->move(moveDir * -0.5f);
	}
}

}