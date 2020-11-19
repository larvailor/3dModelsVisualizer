#include "Camera.hpp"

namespace
{
	const float START_POS_X = 0.0f;
	const float START_POS_Y = 0.0f;
	const float START_POS_Z = 0.0f;

	const float START_SCALE = 0.0f;
	const float START_PITCH = 0.0f;
	const float START_ROLL = 0.0f;
	const float START_NEAR_PLANE = 0.01f;
	const float START_FAR_PLANE = 100.0f;
	const float START_FIELD_OF_VIEW = 45.0f;

}

Camera::Camera()
	: mPosition(START_POS_X, START_POS_Y, START_POS_Z)
	, mScale(START_SCALE)
	, mPitch(START_PITCH)
	, mRoll(START_ROLL)
	, mNearPlane(START_NEAR_PLANE)
	, mFarPlane(START_FAR_PLANE)
	, mFieldOfView(START_FIELD_OF_VIEW)
{

}

void Camera::HandleInput(sf::Event& event)
{
	float speed = 0.03f;
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::A)
		{
			mPosition.x -= speed;
		}
		if (event.key.code == sf::Keyboard::D)
		{
			mPosition.x += speed;
		}

		if (event.key.code == sf::Keyboard::W)
		{
			mPosition.z -= speed;
		}
		if (event.key.code == sf::Keyboard::S)
		{
			mPosition.z += speed;
		}
		break;
	}
}
