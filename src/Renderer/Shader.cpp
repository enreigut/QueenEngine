#include "Shader.h"

#include <exception>
#include <vector>

namespace Queen
{
	namespace Renderer
	{
		Shader::Shader()
		{

		}

		Shader::~Shader()
		{

		}

		void CheckShaderCompileStatus(GLuint shaderId)
		{
			GLint result = GL_FALSE;
			int infoLogLength;

			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0)
			{
				std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
				glGetShaderInfoLog(shaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
				std::printf("%s\n", &vertexShaderErrorMessage[0]);
			}
		}

		void CheckProgramCompileStatus(GLuint programId)
		{
			GLint result = GL_FALSE;
			int infoLogLength;

			glGetProgramiv(programId, GL_LINK_STATUS, &result);
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0)
			{
				std::vector<char> programErrorMessage(infoLogLength + 1);
				glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
				printf("%s\n", &programErrorMessage[0]);
			}
		}

		void Shader::CreateProgram(const char* vertexFilepath, const char* fragmentFilepath)
		{
			GLuint vertexShader = -1;
			GLuint fragmentShader = -1;

			m_vertexReader.ReadFile(vertexFilepath);
			const char* vertexData = m_vertexReader.GetData();

			m_fragmentReader.ReadFile(fragmentFilepath);
			const char* fragmentData = m_fragmentReader.GetData();

			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexData, NULL);
			glCompileShader(vertexShader);

			CheckShaderCompileStatus(vertexShader);

			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentData, NULL);
			glCompileShader(fragmentShader);

			CheckShaderCompileStatus(fragmentShader);

			m_programId = glCreateProgram();
			glAttachShader(m_programId, vertexShader);
			glAttachShader(m_programId, fragmentShader);
			glLinkProgram(m_programId);

			CheckProgramCompileStatus(m_programId);

			glDetachShader(m_programId, vertexShader);
			glDetachShader(m_programId, fragmentShader);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void Shader::UseProgram()
		{
			glUseProgram(m_programId);
		}

		void Shader::SetUniformLocation4f(const char* uniform, float x, float y, float z, float w)
		{
			int location = glGetUniformLocation(m_programId, uniform);
			glUniform4f(location, x, y, z, w);
		}

		void Shader::SetUniformLocationMat4f(const char* uniform, glm::mat4 x)
		{
			int location = glGetUniformLocation(m_programId, uniform);
			glUniformMatrix4fv(location, 1, GL_FALSE, &x[0][0]);
		}
	}
}