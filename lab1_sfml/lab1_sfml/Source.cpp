#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Globals.hpp"
#include "Constants.hpp"
#include "ObjParser.hpp"
#include "Camera.hpp"

/////////////////////////////////////////////////
// 
//		GLOBAL VARIABLES
//
/////////////////////////////////////////////////

// Extern declarations
float gFrameTime;

// Rendering
sf::RenderWindow renderWindow(sf::VideoMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), "Lab1");

// Frame time
float frameTime;
sf::Clock frameTimeClock;

// FPS
int fpsCounter;
int fps;
sf::Clock fpsClock;
sf::Font debugFont;
sf::Text debugFrameTime;
sf::Text debugFps;



/////////////////////////////////////////////////
// 
//		FUNCTIONS DECLARATIONS
//
/////////////////////////////////////////////////

void Initialization();
void UpdateFrameTime();
void UpdateFps();
void RenderDebugInfo();

void TransformCoordinates(std::vector<Vertex>& obj, sf::VertexArray& va, Camera& camera);



/////////////////////////////////////////////////
// 
//		FUNCTIONS IMPLEMENTATIONS
//
/////////////////////////////////////////////////

int main()
{

    //-------------------------------------------
    // Set up

	Initialization();

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
	
    while (renderWindow.isOpen())
    {
        sf::Event event;
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow.close();

			camera.HandleInput(event);
        }

		//-------------------------------------------
		//		Update
		
		UpdateFrameTime();
		UpdateFps();

		TransformCoordinates(obj, va, camera);

        //-------------------------------------------
        //		Render
		
		renderWindow.clear();

        renderWindow.draw(va);

		RenderDebugInfo();

        renderWindow.display();
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

}

void Initialization()
{
	debugFont.loadFromFile(PATH_TO_DEBUG_FONT);

	// Frame time
	debugFrameTime = sf::Text();
	debugFrameTime.setFont(debugFont);
	debugFrameTime.setCharacterSize(16);
	debugFrameTime.setFillColor(sf::Color::White);
	debugFrameTime.setPosition(5, 5);

	// FPS
	debugFps = sf::Text();
	debugFps.setFont(debugFont);
	debugFps.setCharacterSize(16);
	debugFps.setFillColor(sf::Color::White);
	debugFps.setPosition(5, 20);
}



//-----------------------------------------------
//		Update
//

void UpdateFrameTime()
{
	debugFrameTime.setString("FT: " + std::to_string(frameTime));
	frameTime = frameTimeClock.restart().asSeconds();
}

void UpdateFps()
{
	fpsCounter++;
	if (fpsClock.getElapsedTime().asSeconds() > 1)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		debugFps.setString("FPS: " + std::to_string(fps));
		fpsClock.restart();
	}
}



//-----------------------------------------------
//		Render
//

void RenderDebugInfo()
{
	// Frame time
	renderWindow.draw(debugFrameTime);

	// Fps
	renderWindow.draw(debugFps);
}
