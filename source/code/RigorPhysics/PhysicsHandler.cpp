#include "PhysicsHandler.h"
#include "Physics.hpp"

namespace rg
{

const Vector3 GRAVITY = Vector3(0.0f, -9.8f, 0.0f);

PhysicsHandler::PhysicsHandler()
	: gravity(GRAVITY)
{
}

PhysicsHandler::~PhysicsHandler()
{
	for (auto& p : particles) delete p;
	for (auto& p : planes) delete p;
}

void PhysicsHandler::update()
{
	for (auto& p : particles)
	{
		p->addForceIgnoreMass(gravity * timeStep);
		p->update();
	}

	for (auto& c : constraints)
	{
		c->apply();
	}
}

Constraint* PhysicsHandler::addConstraint(Constraint* constraint)
{
	constraints.push_back(constraint);
	return constraint;
}

void PhysicsHandler::destroyConstraint(Constraint* constraint)
{
	destroyItem(constraint, constraints);
}

Particle* PhysicsHandler::addParticle(Particle* particle)
{
	particles.push_back(particle);
	return particle;
}

void PhysicsHandler::destroyParticle(Particle* particle)
{
	destroyItem(particle, particles);
}

Plane* PhysicsHandler::addPlane(Plane* plane)
{
	planes.push_back(plane);
	return plane;
}

void PhysicsHandler::destroyPlane(Plane* plane)
{
	destroyItem(plane, planes);
}

}