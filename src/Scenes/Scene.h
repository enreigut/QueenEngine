#pragma once

#include <unordered_map>
#include <sstream>
#include "../ECS/Entity.h"

namespace Queen
{
	class Scene
	{
	public:
		Scene();
		Scene(const char* name);
		~Scene();

		// Getters
		ECS::Entity* GetEntity(const char* name);
		inline const char* GetSceneName() const { return m_name; }
		inline std::unordered_map<const char*, ECS::Entity*> GetEntities() const { return m_entities; }

		// Setters

		// Derived
		void AddEntity(ECS::Entity* entity);
		std::string Serialise();

	private:
		const char* m_name = "New Scene";
		std::unordered_map<const char*, ECS::Entity*> m_entities;
	};
}