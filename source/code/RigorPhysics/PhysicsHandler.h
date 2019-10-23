#pragma once

#include <vector>
#include "Constraints/Constraint.h"
#include "Objects/Particle.h"
#include "Objects/Plane.h"
#include "Objects/ConvexHull.h"

namespace rg
{

class PhysicsHandler
{
public:
	typedef std::vector<Constraint*> ConstraintList;
	typedef std::vector<Particle*> ParticleList;
	typedef std::vector<Plane*> PlaneList;
	typedef std::vector<ConvexHull*> ConvexHullList;

	PhysicsHandler();
	~PhysicsHandler();
	void update();

	Constraint* addConstraint(Constraint* constraint);
	void destroyConstraint(Constraint* constraint);
	const ConstraintList& getConstraints() const { return constraints; }

	Particle* addParticle(Particle* particle);
	void destroyParticle(Particle* particle);
	const ParticleList& getParticles() const { return particles; }

	Plane* addPlane(Plane* plane);
	void destroyPlane(Plane* plane);
	const PlaneList& getPlanes() const { return planes; }

	ConvexHull* addConvexHull(ConvexHull* convexHull);
	void destroyConvexHull(ConvexHull* convexHull);
	const ConvexHullList& getConvexHulls() const { return convexHulls; }
private:
	template<class T> void destroyItem(T* item, std::vector<T*> list);
	ConstraintList constraints;
	ParticleList particles;
	PlaneList planes;
	ConvexHullList convexHulls;
	Vector3 gravity;
};

template<class T>
inline void PhysicsHandler::destroyItem(T* item, std::vector<T*> list)
{
	auto it = std::find(list.begin(), list.end(), item);
	if (it != list.end())
	{
		delete *it;
		list.erase(it);
	}
}

}