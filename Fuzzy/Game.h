#pragma once
#include "Input.h"
#include "SFML/Graphics.hpp"
#include "fl/Headers.h"

class Game
{
public:
	Game(sf::RenderWindow* hwnd, Input* in);
	~Game();

	//Handling player input
	void handleInput(float deltaTime);
	//Every frame loop
	void update(float deltaTime);
	//Rendering
	void render();

protected:
	//Functions
	void beginDraw();
	void endDraw();

	//Reference to the application's windows window
	sf::RenderWindow* window;
	//Input class
	Input* input;

	//Line
	sf::RectangleShape line;
	//Cars
	sf::RectangleShape car;
	sf::RectangleShape car2;

	//Variables
	float distanceFromCarToLine = 0.0f;
	float distanceFromCarToLine2 = 0.0f;
	float carVelocity = 0.0f;
	float carVelocity2 = 0.0f;

	float velocityMultiplier = 1000.0f;

	//Text
	sf::Text idText;
	sf::Text distanceText;
	sf::Text velocityText;

	sf::Text idText2;
	sf::Text distanceText2;
	sf::Text velocityText2;

	sf::Text outputText;
	
	//Font for displaying text
	sf::Font font;

	//View of the game
	sf::View screenView;

	//Game modes
	int gameMode = 0;

	//FIS Engine
	fl::Engine* engine;

	bool readyToTakeInput = true;
};

