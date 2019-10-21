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
}

void PhysicsHandler::update()
{
	for (auto& p : particles)
	{
		p->addForceIgnoreMass(gravity * timeStep);
		p->update();
	}
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

}