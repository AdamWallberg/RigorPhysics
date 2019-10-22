#pragma once

#include "Math.hpp"

namespace rg
{

class Plane
{
public:
	Plane(Vector3 position, Vector3 normal);
	float relation(Vector3 position) const;
	
	Vector3 position;
	Vector3 normal;
};

}