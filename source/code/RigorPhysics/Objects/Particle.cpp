#include "Particle.h"
#include "Physics.hpp"

namespace rg
{

Particle::Particle(Vector3 position, float mass, float damp)
	: position(position)
	, oldPosition(position)
	, force(ZeroVector)
	, mass(mass)
	, damp(damp)
{
	setMass(mass);
}

void Particle::addForce(Vector3 force)
{
	this->force += force * inverseMass / timeStep;
}

void Particle::addForceUnscaled(Vector3 force)
{
	this->force += (force * timeStep) * inverseMass / timeStep;
}

void Particle::addForceIgnoreMass(Vector3 force)
{
	if (inverseMass == 0.0f) return;
	this->force += force / timeStep;
}

void Particle::setMass(float mass)
{
	if (mass == 0.0f)
	{
		inverseMass = 0.0f;
	}
	else
	{
		this->mass = mass;
		inverseMass = 1.0f / mass;
	}
}

void Particle::update()
{
	Vector3 newPosition =
		position * (2.0f - damp * timeStep) -
		oldPosition * (1.0f - damp * timeStep) +
		getForce() * (timeStep * timeStep * inverseMass);
	oldPosition = position;
	position = newPosition;
	clearForce();
}

void Particle::move(Vector3 position)
{
	this->position += position;
}

const Vector3 Particle::getVelocity() const
{
	return (position - oldPosition) * (1.0f / timeStep);
}

void Particle::setVelocity(Vector3 velocity)
{
	oldPosition = position - velocity * timeStep;
}

void Particle::clearForce()
{
	force = ZeroVector;
}

}