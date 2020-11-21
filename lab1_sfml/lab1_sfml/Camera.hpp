#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

#include "glm/glm.hpp"


class Camera
{
public:
	Camera();

	void Update(const glm::vec2& mousePositionChangeDelta);
	void HandleInput(sf::Event& event);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:
	glm::vec3 mPosition;
	glm::vec3 mViewDirection;
	glm::vec3 mUp;

	glm::mat4 mViewMatrix;

	float mMoveSpeed;

	float mNearPlane;
	float mFarPlane;
	float mFieldOfView;
};


#endif
