#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "../Utilities/FileReader.h"

namespace Queen
{
	namespace Renderer
	{
		class Shader
		{
		public:
			Shader();
			~Shader();

			// Getters

			// Setters

			// Derived
			void CreateProgram(const char* vertexFilepath, const char* fragmentFilepath);
			void UseProgram();
			void SetUniformLocation4f(const char* uniform, float x, float y, float z, float w);
			void SetUniformLocationMat4f(const char* uniform, glm::mat4 x);

		private:
			FileReader m_vertexReader, m_fragmentReader;
			GLuint m_programId = -1;
		};
	}
}