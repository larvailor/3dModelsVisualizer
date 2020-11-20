#include "Globals.hpp"
#include "Camera.hpp"

namespace
{
	const float START_POS_X = 0.0f;
	const float START_POS_Y = 0.0f;
	const float START_POS_Z = 0.0f;

	const float START_SCALE = 0.0f;
	const float START_NEAR_PLANE = 0.01f;
	const float START_FAR_PLANE = 100.0f;
	const float START_FIELD_OF_VIEW = 45.0f;
	
	const float START_MOVE_SPEED = 100.0f;

}

Camera::Camera()
	: mPosition(START_POS_X, START_POS_Y, START_POS_Z)
	, mScale(START_SCALE)
	, mNearPlane(START_NEAR_PLANE)
	, mFarPlane(START_FAR_PLANE)
	, mFieldOfView(START_FIELD_OF_VIEW)
	, mMoveSpeed(START_MOVE_SPEED)
{

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
