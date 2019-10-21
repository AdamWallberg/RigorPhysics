#pragma once

#include <vector>
#include "Objects/Particle.h"

namespace rg
{

class PhysicsHandler
{
public:
	typedef std::vector<Particle*> ParticleList;
	
	PhysicsHandler();
	~PhysicsHandler();
	void update();

	Particle* addParticle(Particle* particle);
	void destroyParticle(Particle* particle);
	const ParticleList& getParticles() { return particles; }
private:
	template<class T> void destroyItem(T* item, std::vector<T*> list);
	ParticleList particles;
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