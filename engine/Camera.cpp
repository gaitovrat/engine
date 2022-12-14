#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "Configuration.hpp"

#include <iostream>

Camera::Camera() : m_eye(0.0f, 0.0f, 3.0f), m_target(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f), m_lastX(), m_lastY(), m_pitch(), m_yaw(), m_height(), m_width()
{
}

Camera& Camera::GetInstance()
{
	static Camera camera;

	return camera;
}

glm::mat4 Camera::ToMatrix() const
{
	return glm::lookAt(m_eye, m_eye + m_target, m_up);
}

void Camera::MoveLeft(const float speed)
{
	m_eye -= glm::normalize(glm::cross(m_target, m_up)) * speed;

	NotifyAll(VIEW_MATRIX_CHANGED);
}

void Camera::MoveForward(const float speed)
{
	m_eye += speed * m_target;

    NotifyAll(VIEW_MATRIX_CHANGED);
}

void Camera::MoveRight(const float speed)
{
	m_eye += glm::normalize(glm::cross(m_target, m_up)) * speed;

    NotifyAll(VIEW_MATRIX_CHANGED);
}

void Camera::MoveBackward(float speed)
{
	m_eye -= speed * m_target;

    NotifyAll(VIEW_MATRIX_CHANGED);
}

void Camera::NotifyAll(const EObserverEvent event)
{
	for (const auto& observer : m_observers)
	{
        if (observer != nullptr)
        {
            observer->Notify(event, this);
        }
	}
}

void Camera::AddObserver(IObserver* observer)
{
    m_observers.push_back(observer);
}

void Camera::UpdateTarget(glm::vec3 eye)
{
	m_target = glm::normalize(eye);

    NotifyAll(VIEW_MATRIX_CHANGED);
}

void Camera::Rotate(const double x, const double y)
{
    float xoffset = x - m_lastX;
    float yoffset = m_lastY - y;

    m_lastX = x;
    m_lastY = y;

    float sensitivity = Configuration::Sensivity;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    UpdateTarget(direction);
}

void Camera::UpdateViewport(int width, int height)
{
    m_width = width;
    m_height = height;

    glViewport(0, 0, width, height);
    NotifyAll(PROJECTION_MATRIX_CHANGED);
}

glm::mat4 Camera::Projection()
{
    return glm::perspective(glm::radians(45.0f), float(m_width) / float(m_height), 0.1f, 100.0f);
}

int Camera::Width() const
{
    return m_width;
}

int Camera::Height() const
{
    return m_height;
}

glm::vec3 Camera::Eye() const
{
    return m_eye;
}

glm::vec3 Camera::Target() const
{
    return m_target;
}

double Camera::ClickedX()
{
    return m_clickedX;
}

double Camera::ClickedY()
{
    return m_clickedY;
}

void Camera::SetClickedX(double x)
{
    m_clickedX = x;
}

void Camera::SetClickedY(double y)
{
    m_clickedY = y;
}
