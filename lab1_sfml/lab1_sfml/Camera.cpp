#include "Camera.hpp"

#include "Globals.hpp"
#include "Constants.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace
{
	const glm::vec3 cStartPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 cStartViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 cStartUp = glm::vec3(0.0f, 1.0f, 0.0f);

	const float cStartNearPlane = 0.01f;
	const float cStartFarPlane = 100.0f;
	const float cStartFieldOfView = 45.0f;
	
	const float cStartMoveSpeed = 3.0f;

}

Camera::Camera()
	: mPosition(cStartPosition)
	, mViewDirection(cStartViewDirection)
	, mUp(cStartUp)
	, mViewMatrix(1.0f)
	, mNearPlane(cStartNearPlane)
	, mFarPlane(cStartFarPlane)
	, mFieldOfView(cStartFieldOfView)
	, mMoveSpeed(cStartMoveSpeed)
{

}

void Camera::Update(const glm::vec2& mousePositionChangeDelta)
{
	mViewDirection = glm::mat3(glm::rotate(-mousePositionChangeDelta.x * gFrameTime, mUp)) * mViewDirection;
}

void Camera::HandleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::A)
		{
			mPosition.x -= mMoveSpeed * gFrameTime;
		}
		if (event.key.code == sf::Keyboard::D)
		{
			mPosition.x += mMoveSpeed * gFrameTime;
		}

		if (event.key.code == sf::Keyboard::W)
		{
			mPosition.z -= mMoveSpeed * gFrameTime;
		}
		if (event.key.code == sf::Keyboard::S)
		{
			mPosition.z += mMoveSpeed * gFrameTime;
		}
		break;
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(mPosition, mPosition + mViewDirection, mUp);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(mFieldOfView), WINDOW_WIDTH / WINDOW_HEIGHT, mNearPlane, mFarPlane);
}
