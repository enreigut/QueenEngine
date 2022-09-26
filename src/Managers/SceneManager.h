#pragma once

#include "Manager.h"
#include "../Scenes/Scene.h"
#include "../ECS/Entity.h"
#include <vector>
#include <unordered_map>

namespace Queen
{
	namespace Managers
	{
		class SceneManager : public Manager
		{
		public:
			SceneManager();
			~SceneManager();

			// Getters

			// Setters

			// Derived
			void Start() override;
			void Shutdown() override;
			void AddScene(Scene* s);
			Scene* CreateScene(const char* name);
			Scene* CreateScene(const char* name, std::vector<ECS::Entity> entities);
			
			void SerialiseScene(Scene* scene);
			void DeserialiseScene(std::string data);


		private:
			const char* m_activeScene = "";
			std::unordered_map<const char*, Scene*> m_scenes;
		};
	}
}