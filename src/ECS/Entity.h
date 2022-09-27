#pragma once

#include <unordered_map>
#include <typeinfo>
#include "Component.h"
#include <sstream>

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

			std::string SerialiseComponents()
			{
				std::stringstream ss;

				ss << "m_components: [\n";

				if (GetComponent<ECS::Transform>() != nullptr)
				{
					ECS::Transform* t = GetComponent<ECS::Transform>();
					ss << "\t\t\tTransform: {\n";
					ss << "\t\t\t\tp_position: {\n";
					ss << "\t\t\t\t\tx: " << t->p_position.x << ",\n";
					ss << "\t\t\t\t\ty: " << t->p_position.y << ",\n";
					ss << "\t\t\t\t\tz: " << t->p_position.z << "\n";
					ss << "\t\t\t\t},\n";
					ss << "\t\t\t\tp_rotation: {\n";
					ss << "\t\t\t\t\tx: " << t->p_rotation.x << ",\n";
					ss << "\t\t\t\t\ty: " << t->p_rotation.y << ",\n";
					ss << "\t\t\t\t\tz: " << t->p_rotation.z << "\n";
					ss << "\t\t\t\t},\n";
					ss << "\t\t\t\tp_scale: {\n";
					ss << "\t\t\t\t\tx: " << t->p_scale.x << ",\n";
					ss << "\t\t\t\t\ty: " << t->p_scale.y << ",\n";
					ss << "\t\t\t\t\tz: " << t->p_scale.z << "\n";
					ss << "\t\t\t\t}\n";
					ss << "\t\t\t},\n";
				}
				
				if (GetComponent<ECS::Model>() != nullptr)
				{
					ECS::Model* m = GetComponent<ECS::Model>();
					ss << "\t\t\tModel: {\n";
					ss << "\t\t\t\tp_name: " << m->p_name << ",\n";
					ss << "\t\t\t\tp_vertices: [\n";
					for (int i = 0; i < m->p_vertices.size(); i++)
					{
						ss << "\t\t\t\t\t" << m->p_vertices[i] << ",\n";
					}
					ss << "\t\t\t\t],\n";
					ss << "\t\t\t\tp_indices: [\n";
					for (int i = 0; i < m->p_indices.size(); i++)
					{
						ss << "\t\t\t\t\t" << m->p_indices[i] << ",\n";
					}
					ss << "\t\t\t\t]\n";
					ss << "\t\t\t},\n";
				}

				ss << "\t\t]";

				return ss.str();
			}

			std::string Serialise()
			{
				std::stringstream ss;

				ss << "Entity: {\n";
				ss << "\t\tm_name: " << m_name << ",\n";
				ss << "\t\t" << SerialiseComponents() << "\n";
				ss << "\t},";

				return ss.str();
			}

			ECS::Entity* DeserialiseComponents(std::string data)
			{

			}

			ECS::Entity* Deserialise(std::string data)
			{

			}

		private:
			const char* m_name = "New Entity";
			std::unordered_map<const char*, Component*> m_components;
		};
	}
}