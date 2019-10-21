#include "Particle.h"

namespace rg
{

Particle::Particle(Vector3 position, float mass, float damp, float deltaTime)
	: position(position)
	, oldPosition(position)
	, force(ZeroVector)
	, mass(mass)
	, damp(damp)
	, deltaTime(deltaTime)
{
	setMass(mass);
}

void Particle::addForce(Vector3 force)
{
	this->force += force * inverseMass / deltaTime;
}

void Particle::addForceIgnoreMass(Vector3 force)
{
	if (inverseMass == 0.0f) return;
	this->force += force / deltaTime;
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
		position * (2.0f - damp * deltaTime) -
		oldPosition * (1.0f - damp * deltaTime) +
		getForce() * (deltaTime * deltaTime * inverseMass);
	oldPosition = position;
	position = newPosition;
	clearForce();
}

void Particle::move(Vector3 position)
{
	this->position = position;
}

const Vector3 Particle::getVelocity() const
{
	return (position - oldPosition) * (1.0f / deltaTime);
}

void Particle::setVelocity(Vector3 velocity)
{
	oldPosition = position - velocity * deltaTime;
}

void Particle::clearForce()
{
	force = ZeroVector;
}

}