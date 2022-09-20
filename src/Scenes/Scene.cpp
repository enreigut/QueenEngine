#include "Scene.h"

#include <sstream>

namespace Queen
{
	Scene::Scene()
	{

	}

	Scene::Scene(const char* name): m_name(name)
	{

	}

	Scene::~Scene()
	{

	}

	ECS::Entity* Scene::GetEntity(const char* name)
	{
		if (m_entities.find(name) != m_entities.end())
			return m_entities[name];

		return nullptr;
	}

	void Scene::AddEntity(ECS::Entity* entity)
	{
		if (m_entities.find(entity->GetName()) == m_entities.end())
			m_entities[entity->GetName()] = entity;
	}
}