#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constants.hpp"
#include "ObjParser.hpp"
#include "Camera.hpp"

#include <iostream>

//
// Functions declarations
//

void TransformCoordinates(std::vector<Vertex>& obj, sf::VertexArray& va, Camera& camera);

// MAIN

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lab1");

    //-------------------------------------------
    // Set up

    std::vector<Vertex> obj = ObjParser::parseObj(PATH_TO_MODEL);

    sf::VertexArray va(sf::Lines, obj.size());

	Camera camera;


	// TEST


	//sf::VertexArray lines(sf::LineStrip, 5);
	//lines[0].position = sf::Vector2f(100, 100);
	//lines[1].position = sf::Vector2f(200, 100);
	//lines[2].position = sf::Vector2f(200, 200);
	//lines[3].position = sf::Vector2f(100, 200);
	//lines[4].position = sf::Vector2f(100, 100);
	//

	//glm::mat4 model(1.0f);
	//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z));
	//glm::mat4 proj = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, camera.mNearPlane, camera.mFarPlane);
	////glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 mvp = proj * view * model;

	//glm::mat4 viewPortMatrix = glm::mat4(
	//	WINDOW_WIDTH / 2.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, -(WINDOW_HEIGHT / 2.0f), 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f + WINDOW_WIDTH / 2.0f, 0.0f + WINDOW_HEIGHT / 2.0f, 0.0f, 1.0f
	//);

	//for (auto i = 0; i < 5; i++)
	//{
	//	glm::vec4 newCoord = mvp * glm::vec4(lines[i].position.x, lines[i].position.y, 1.0f, 1.0f);
	//	newCoord = viewPortMatrix * newCoord;
	//	lines[i].position.x = newCoord.x;
	//	lines[i].position.y = newCoord.y;
	//}




    //-------------------------------------------
    // Program loop
	


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			camera.HandleInput(event);
        }




        //-------------------------------------------
        // Render stuff here
		
		window.clear();

		TransformCoordinates(obj, va, camera);
        window.draw(va);

        window.display();
    }

    return 0;
}




void TransformCoordinates(std::vector<Vertex>& obj, sf::VertexArray& va, Camera& camera)
{
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(0.40f, 0.40f, 0.40f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z));
	glm::mat4 view = glm::lookAt(
		glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z), // the position the camera, in world space
		glm::vec3(0, 0, 0), // where you want to look at, in world space
		glm::vec3(0, 1, 0)
	);
	glm::mat4 proj = glm::perspective(glm::radians(camera.mFieldOfView), WINDOW_WIDTH / WINDOW_HEIGHT, camera.mNearPlane, camera.mFarPlane);

	glm::mat4 mvp = proj * view * model;

	glm::mat4 viewPortMatrix = glm::mat4(
		WINDOW_WIDTH / 2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -(WINDOW_HEIGHT / 2.0f), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f + WINDOW_WIDTH / 2.0f, 0.0f + WINDOW_HEIGHT / 2.0f, 0.0f, 1.0f
	);

	glm::vec4 newVertexPos;
	for (unsigned i = 0; i < obj.size(); i++)
	{
		newVertexPos = mvp * glm::vec4(obj[i].position, 1.0f);
		newVertexPos = viewPortMatrix * newVertexPos;

		va[i].position = sf::Vector2f(newVertexPos.x, newVertexPos.y);
		//va[i].color = sf::Color(50, 50, 50, 255);
	}





	//glm::vec3 scaleVector(3.0f);
	//glm::vec3 rotationVector(0.0f);
	//glm::vec3 translationVec(0.0f);

	//glm::mat4 modelMatrix;
	//modelMatrix = glm::scale(modelMatrix, scaleVector);
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), rotationVector);
	//modelMatrix = glm::translate(modelMatrix, translationVec);


	//glm::mat4 viewMatrix = glm::lookAt(
	//	glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z), // the position the camera, in world space
	//	glm::vec3(0, 0, 0), // where you want to look at, in world space
	//	glm::vec3(0, 1, 0)
	//);


	//glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.mFieldOfView), 4.0f / 3.0f, camera.mNearPlane, camera.mFarPlane);


	//glm::mat4 modelViewProjectionMat = projectionMatrix * viewMatrix * modelMatrix;


	//glm::mat4 viewPortMatrix = glm::mat4(
	//	WINDOW_WIDTH / 2.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, -(WINDOW_HEIGHT / 2.0f), 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f + WINDOW_WIDTH / 2.0f, 0.0f + WINDOW_HEIGHT / 2.0f, 0.0f, 1.0f
	//);

	//glm::vec4 newVertexPos;
	//for (unsigned i = 0; i < obj.size(); i++)
	//{
	//	newVertexPos = modelViewProjectionMat * glm::vec4(obj[i].position, 1.0f);
	//	newVertexPos = viewPortMatrix * newVertexPos;

	//	va[i].position = sf::Vector2f(newVertexPos.x, newVertexPos.y);
	//	va[i].color = sf::Color(50, 50, 50, 255);
	//}
}
