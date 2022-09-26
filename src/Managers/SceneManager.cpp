#include "SceneManager.h"

#include <stdio.h>
#include <sstream>

namespace Queen
{
	namespace Managers
	{
		SceneManager::SceneManager()
		{

		}

		SceneManager::~SceneManager()
		{
			for(auto scene = m_scenes.begin(); scene != m_scenes.end(); ++scene)
				delete(scene->second);
		}

		void SceneManager::Start()
		{
			if (IsRunning())
				throw std::exception("Manager already initialised!");

			SetRunning(true);
		}

		void SceneManager::Shutdown()
		{
			if (!IsRunning())
				throw std::exception("Manager is already shutted down!");

			SetRunning(false);
		}

		void SceneManager::AddScene(Scene* s)
		{
			if (!IsRunning())
				throw std::exception("Manager is not running!");

			if (m_scenes.find(s->GetSceneName()) == m_scenes.end())
				m_scenes[s->GetSceneName()] = s;
		}

		Scene* SceneManager::CreateScene(const char* name)
		{
			if (!IsRunning())
				throw std::exception("Manager is not running!");

			Scene* s = new Scene(name);
			AddScene(s);
			return s;
		}

		Scene* SceneManager::CreateScene(const char* name, std::vector<ECS::Entity> entities)
		{
			if (!IsRunning())
				throw std::exception("Manager is not running!");

			Scene* s = new Scene(name);

			for (int i = 0; i < entities.size(); i++)
				s->AddEntity(&entities[i]);

			AddScene(s);
			return s;
		}

		void SceneManager::SerialiseScene(Scene* scene)
		{
			scene->Serialise();
		}

		void SceneManager::DeserialiseScene(std::string data)
		{

		}
	}
}