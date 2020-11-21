#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

#include "glm/glm.hpp"

class Camera
{
public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	Camera();

	//-----------------------------------------------
	//		Initialization
	//

	void Initialize();
	void InitializeDebugInfo();

	//-----------------------------------------------
	//		Update
	//

	void Update();

	// TODO: change
	void UpdateLookDirection(const glm::vec2& mousePositionChangeDelta);
	void HandleInput(sf::Event& event);

	//-----------------------------------------------
	//		Getters
	//

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	const sf::Text& GetDebugInfo() const;

	//-----------------------------------------------
	//		Setters
	//

	// ...

	//-----------------------------------------------
	//		Debug
	//

	sf::Text GetDebugInfo();

private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	glm::vec3 mPosition = glm::vec3(0.0f);
	glm::vec3 mLookDirection = glm::vec3(0.0f);
	glm::vec3 mUp = glm::vec3(0.0f);

	float mMoveSpeed = 0.0f;
	float mRotationSpeed = 0.0f;

	float mFieldOfView = 0.0f;
	float mNearPlane = 0.0f;
	float mFarPlane = 0.0f;
	glm::vec2 mAspectRatio = glm::vec2(0.0f);

	sf::Font mDebugFont;
	sf::Text mDebugText;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Update
	//

	void UpdateDebugInfo();

};


#endif
