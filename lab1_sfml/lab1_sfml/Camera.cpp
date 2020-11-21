#include "Camera.hpp"

#include "Globals.hpp"
#include "Constants.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace
{
	const glm::vec3 cStartPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	const glm::vec3 cStartLookDirection = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
	const glm::vec3 cStartUp = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));

	const float cStartNearPlane = 0.01f;
	const float cStartFarPlane = 100.0f;
	const float cStartFieldOfView = 45.0f;
	
	const float cStartMoveSpeed = 1.0f;
	const float ÒStartRotationSpeed = 0.05f;
}

/////////////////////////////////////////////////
// 
//		PUBLIC
//
/////////////////////////////////////////////////

Camera::Camera()
{

}



//-----------------------------------------------
//		Initialization
//

void Camera::Initialize()
{
	mPosition = cStartPosition;
	mLookDirection = cStartLookDirection;
	mUp = cStartUp;

	mFieldOfView = cStartFieldOfView;
	mNearPlane = cStartNearPlane;
	mFarPlane = cStartFarPlane;

	mMoveSpeed = cStartMoveSpeed;
	mRotationSpeed = ÒStartRotationSpeed;

	mAspectRatio = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT);

	InitializeDebugInfo();
}

void Camera::InitializeDebugInfo()
{
	mDebugFont.loadFromFile(PATH_TO_DEBUG_FONT);

	mDebugText = sf::Text();
	mDebugText.setFont(mDebugFont);
	mDebugText.setCharacterSize(14);
	mDebugText.setFillColor(sf::Color::White);
	mDebugText.setPosition(WINDOW_WIDTH - 400, 20);

	UpdateDebugInfo();
}



//-----------------------------------------------
//		Update
//

void Camera::Update()
{
	// TODO
}

// TODO: change
void Camera::UpdateLookDirection(const glm::vec2& mousePositionChangeDelta)
{
	{
		//mLookDirection = glm::mat3(glm::rotate(-mousePositionChangeDelta.x * gFrameTime, mUp)) * mLookDirection;
		//glm::vec3 localX = glm::cross(mLookDirection, mUp);

		//glm::mat4 rotator = glm::rotate(mousePositionChangeDelta.x * mRotationSpeed * gFrameTime, mUp);// * // moving camera left or right
		//					//glm::rotate(-mousePositionChangeDelta.y * mRotationSpeed * gFrameTime, localX);  // moving camera up or down

		//mLookDirection = glm::mat3(rotator) * mLookDirection;
	}

}

void Camera::HandleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::A)
		{
			mPosition -= mMoveSpeed * gFrameTime * glm::normalize(glm::cross(mLookDirection, mUp));
		}
		if (event.key.code == sf::Keyboard::D)
		{
			mPosition += mMoveSpeed * gFrameTime * glm::normalize(glm::cross(mLookDirection, mUp));
		}
		if (event.key.code == sf::Keyboard::W)
		{
			mPosition += mMoveSpeed * gFrameTime * mLookDirection;
		}
		if (event.key.code == sf::Keyboard::S)
		{
			mPosition -= mMoveSpeed * gFrameTime * mLookDirection;
		}

		UpdateDebugInfo();

		break;
	}
}



//-----------------------------------------------
//		Getters
//

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(mPosition, mPosition + mLookDirection, mUp);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(mFieldOfView), mAspectRatio.x / mAspectRatio.y, mNearPlane, mFarPlane);
}

const sf::Text& Camera::GetDebugInfo() const
{
	return mDebugText;
}




//-----------------------------------------------
//		Setters
//

// ...



//-----------------------------------------------
//		Debug
//

sf::Text Camera::GetDebugInfo()
{
	return mDebugText;
}



/////////////////////////////////////////////////
// 
//		PRIVATE
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Update
//

void Camera::UpdateDebugInfo()
{
	mDebugText.setString(
		"Camera\n\t Position: " + std::to_string(mPosition.x) + "  " + std::to_string(mPosition.y) + "  " + std::to_string(mPosition.z) + "\n"
	);
}
