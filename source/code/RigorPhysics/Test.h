#pragma once

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate

namespace rg
{

glm::vec3 testFunction(glm::vec3 v0, glm::vec3 v1)
{
	return v0 + v1;
}

}