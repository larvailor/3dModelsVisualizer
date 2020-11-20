#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

#include "glm/glm.hpp"

class Camera
{
public:
	Camera();

	void HandleInput(sf::Event& event);

	glm::vec3 mPosition;
	float mScale;
	float mNearPlane;
	float mFarPlane;
	float mFieldOfView;

private:
	float mMoveSpeed;
};


#endif
