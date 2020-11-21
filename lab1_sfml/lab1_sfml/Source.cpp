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
std::shared_ptr<sf::RenderWindow> renderWindow = std::make_shared<sf::RenderWindow>(
	sf::VideoMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), 
	"3dModelsVisualizer",
	sf::Style::Titlebar | sf::Style::Close
	);

Camera camera;

// Frame time
sf::Clock frameTimeClock;

//-------------------------------------------
//		Debug

sf::Font debugFont;

// Frame time
sf::Text debugFrameTime;

// FPS
int fps;
sf::Clock fpsClock;
sf::Text debugFps;

// Mouse
glm::vec2 oldMousePosition;
glm::vec2 mousePosition;


/////////////////////////////////////////////////
// 
//		FUNCTIONS DECLARATIONS
//
/////////////////////////////////////////////////

//-------------------------------------------
//		Initialization

void Initialization();

//-------------------------------------------
//		Update

void UpdateCamera();
void UpdateFrameTime();
void UpdateFps();

//-------------------------------------------
//		Render

void RenderDebugInfo();


//-------------------------------------------
//		Else

void TransformCoordinates(std::vector<Vertex>& obj, sf::VertexArray& va);



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


	// Test

	sf::VertexArray vaTest(sf::LineStrip, 3);

    //-------------------------------------------
    // Program loop
	
    while (renderWindow->isOpen())
    {
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow->close();

			camera.HandleInput(event);
        }

		//-------------------------------------------
		//		Update

		UpdateCamera();
		UpdateFrameTime();
		UpdateFps();


		TransformCoordinates(obj, va);

		//-------------------------------------------
		//		Render

		renderWindow->clear(sf::Color(50, 50, 50, 255));

		renderWindow->draw(va);
		RenderDebugInfo();

		renderWindow->display();
	}

	return 0;
}




void TransformCoordinates(std::vector<Vertex>& obj, sf::VertexArray& va)
{
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(0.40f, 0.40f, 0.40f));
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z));

	glm::mat4 mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * model;

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
	camera.Initialize();

	debugFont.loadFromFile(PATH_TO_DEBUG_FONT);

	// Frame time
	debugFrameTime = sf::Text();
	debugFrameTime.setFont(debugFont);
	debugFrameTime.setCharacterSize(14);
	debugFrameTime.setFillColor(sf::Color::White);
	debugFrameTime.setPosition(10, 20);

	// FPS
	debugFps = sf::Text();
	debugFps.setFont(debugFont);
	debugFps.setCharacterSize(14);
	debugFps.setFillColor(sf::Color::White);
	debugFps.setPosition(10, 40);
}



//-----------------------------------------------
//		Update
//

// TODO: change
void UpdateCamera()
{
	oldMousePosition = mousePosition;
	mousePosition = glm::vec2(static_cast<float>(sf::Mouse::getPosition(*renderWindow).x), static_cast<float>(sf::Mouse::getPosition(*renderWindow).y));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		camera.UpdateLookDirection(mousePosition - oldMousePosition);
	}

	camera.Update();
}

void UpdateFrameTime()
{
	debugFrameTime.setString("Frame time: " + std::to_string(gFrameTime));
	gFrameTime = frameTimeClock.restart().asSeconds();
}

void UpdateFps()
{
	fps++;
	if (fpsClock.getElapsedTime().asSeconds() > 1)
	{
		debugFps.setString("FPS: " + std::to_string(fps));
		fps = 0;
		fpsClock.restart();
	}
}




//-----------------------------------------------
//		Render
//

void RenderDebugInfo()
{
	// Frame time
	renderWindow->draw(debugFrameTime);

	// Fps
	renderWindow->draw(debugFps);

	// Camera
	renderWindow->draw(camera.GetDebugInfo());
}
