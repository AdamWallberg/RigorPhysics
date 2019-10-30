#pragma once

#include "Math.hpp"

namespace rg
{

class Particle
{
public:
	Particle(Vector3 position, float mass, float damp);
	void addForce(Vector3 force);
	void addForceUnscaled(Vector3 force);
	void addForceIgnoreMass(Vector3 force);
	void setMass(float mass);
	virtual void update();
	void move(Vector3 position);
	const Vector3 getVelocity() const;
	void setVelocity(Vector3 velocity);
	const Vector3 getPosition() const { return position; }
	const Vector3 getForce() const { return force; }
	const float getMass() const { return mass; }
	const float getInverseMass() const { return inverseMass; }
	const float getDamping() const { return damp; }
private:
	void clearForce();
	Vector3 position;
	Vector3 oldPosition;
	Vector3 force;
	float mass;
	float inverseMass;
	float damp;
};

}