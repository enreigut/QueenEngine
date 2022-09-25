#include "Camera.h"

#include <GLM/ext.hpp>

namespace Queen
{
	Camera::Camera()
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::CalculateViewMatrix()
	{
		// TODO: No roll yet
		p_rotation.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		p_rotation.y = sin(glm::radians(m_pitch));
		p_rotation.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		p_rotation = glm::normalize(p_rotation);

		m_viewMatrix = glm::lookAt(
			p_position,
			p_position + p_rotation,
			m_upVector
		);
	}

	void Camera::CalculateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(glm::radians(p_fov), GetAspectRatio(), p_near, p_far);
	}
}