#pragma once

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/gtx/projection.hpp>

typedef glm::vec3 Vector3;
#define ZeroVector Vector3(0.0f, 0.0f, 0.0f)

namespace rg
{

const float PI = 3.141592653589793f;

inline int orientation(Vector3 p, Vector3 q, Vector3 r)
{
	Vector3 cross = glm::cross(q - p, r - p);
	if (cross.z == 0.0f) return 0;
	return cross.z < 0.0f ? 1 : 2;
}

}