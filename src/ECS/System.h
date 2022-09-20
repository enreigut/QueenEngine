#pragma once

#include <vector>
#include "Entity.h"

namespace Queen
{
	namespace ECS
	{
		class System
		{
		public:
			System() {};
			~System() {};

		private:
			std::vector<Entity&> m_entities;
		};
	}
}