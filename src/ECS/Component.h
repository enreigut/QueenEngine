#pragma once

#include <GLM/glm.hpp>

namespace Queen
{
	namespace ECS
	{
		struct Component
		{
		};

		struct Transform: public Component
		{
			glm::vec3 p_position;
			glm::vec3 p_rotation;
			glm::vec3 p_scale;
		};

		struct Model : public Component
		{
			std::string p_name;
			std::vector<float> p_vertices;
			std::vector<unsigned int> p_indices;
		};
	}
}