#pragma once

#include <vector>
#include "Entity.h"
#include "Component.h"
#include "../Utilities/ObjParser.h"

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
		};

		// TODO: Separte system into different classes
		class LoadSystem
		{
		public:
			LoadSystem() {}
			~LoadSystem() {}

			ECS::Model LoadModel(const char* filePath)
			{
				ObjParser objParser;
				objParser.Parse(filePath);
				ECS::Model m = {};
				m.p_name = objParser.GetObjData().name;
				m.p_vertices = objParser.GetObjData().vertices;
				m.p_indices = objParser.GetObjData().vertexIndices;
				return m;
			}

		private:
		};
	}
}