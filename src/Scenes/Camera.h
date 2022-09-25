#pragma once

#include <GLM/glm.hpp>

namespace Queen
{
	enum class ProjectionType
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		// Getters
		inline float GetAspectRatio() const { return m_width / m_height; }
		inline glm::mat4 GetViewMatrix() const { return m_viewMatrix; }
		inline glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }
		inline float GetWidth() const { return m_width; }
		inline float GetHeight() const { return m_height; }

		// Setters
		inline void SetWidth(float& width) { m_width = width; }
		inline void SetHeight(float& height) { m_height = height; }
		inline void SetSize(float& width, float& height) { m_width = width;  m_height = height; }

		// Derived
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

	public:
		glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 10.0f);
		// This points to LookAt pos
		glm::vec3 p_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		float p_fov = 45.0f;
		float p_near = 0.0f;
		float p_far = 100.0f;
		float m_yaw = -90.0f;
		float m_pitch = 0.0f;
		float m_roll = 0.0f;

	private:
		ProjectionType m_projectionType = ProjectionType::PERSPECTIVE;
		float m_width = 1280.0f;
		float m_height = 720.0f;
		glm::vec3 m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_frontVector = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
	};
}
