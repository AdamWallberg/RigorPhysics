#pragma once

#include <vector>
#include "Constraints/Constraint.h"
#include "Objects/Particle.h"
#include "Objects/Plane.h"

namespace rg
{

class PhysicsHandler
{
public:
	typedef std::vector<Constraint*> ConstraintList;
	typedef std::vector<Particle*> ParticleList;
	typedef std::vector<Plane*> PlaneList;

	PhysicsHandler();
	~PhysicsHandler();
	void update();

	Constraint* addConstraint(Constraint* constraint);
	void destroyConstraint(Constraint* constraint);

	Particle* addParticle(Particle* particle);
	void destroyParticle(Particle* particle);
	const ParticleList& getParticles() const { return particles; }

	Plane* addPlane(Plane* plane);
	void destroyPlane(Plane* plane);
	const PlaneList& getPlanes() const { return planes; }
private:
	template<class T> void destroyItem(T* item, std::vector<T*> list);
	ConstraintList constraints;
	ParticleList particles;
	PlaneList planes;
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