#pragma once

#include <unordered_map>
#include <typeinfo>
#include "Component.h"

namespace Queen
{
	namespace ECS
	{
		class Entity
		{
		public:
			Entity() {};
			Entity(const char* name): m_name(name) {};
			~Entity() {};

			// Getters
			inline const char* GetName() const { return m_name; }

			template<typename T>
			T* GetComponent()
			{
				const char* key = typeid(T).name();
				if (m_components.find(key) != m_components.end())
					return (T*)m_components.at(key);

				return nullptr;
			}

			// Setters

			// Derived
			template<typename T>
			void AddComponent(Component* component)
			{
				const char* key = typeid(T).name();
				if (m_components.find(key) == m_components.end())
					m_components[key] = component;
			}

		private:
			const char* m_name = "New Entity";
			std::unordered_map<const char*, Component*> m_components;
		};
	}
}