#include "Game.h"



Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	//Move the screen to the left so that (0, 0) is in the centre of the screen
	screenView.setCenter(0.0f, window->getView().getCenter().y);
	screenView.zoom(0.6f);

	//Set up the line
	line.setPosition(screenView.getCenter().x, 0.0f);
	line.setSize(sf::Vector2f(16.0f, window->getSize().y));
	line.setFillColor(sf::Color::Magenta);

	//Set up the car
	car.setSize(sf::Vector2f(64.0f, 128.0f));
	car.setPosition(screenView.getCenter().x, screenView.getCenter().y - car.getSize().y * 2);
	car.setFillColor(sf::Color::Green);

	//Set up the second car
	car2.setSize(sf::Vector2f(64.0f, 128.0f));
	car2.setPosition(screenView.getCenter().x, screenView.getCenter().y + car.getSize().y);
	car2.setFillColor(sf::Color::Blue);

	//Load in font
	font.loadFromFile("font/arial.ttf");

	//Set up text
	idText.setFont(font);
	idText.setCharacterSize(18);
	idText.setPosition(sf::Vector2f(screenView.getCenter().x - (screenView.getSize().x / 2), 0.0f));
	idText.setFillColor(sf::Color::Green);
	idText.setString("Fuzzy");

	distanceText.setFont(font);
	distanceText.setCharacterSize(18);
	distanceText.setPosition(sf::Vector2f(screenView.getCenter().x - (screenView.getSize().x / 2), 18.0f));
	distanceText.setFillColor(sf::Color::Green);

	velocityText.setFont(font);
	velocityText.setCharacterSize(18);
	velocityText.setPosition(sf::Vector2f(screenView.getCenter().x - (screenView.getSize().x / 2), 36.0f));
	velocityText.setFillColor(sf::Color::Green);

	outputText.setFont(font);
	outputText.setCharacterSize(18);
	outputText.setPosition(sf::Vector2f(screenView.getCenter().x - (screenView.getSize().x / 2), 54.0f));
	outputText.setFillColor(sf::Color::Green);

	idText2.setFont(font);
	idText2.setCharacterSize(18);
	idText2.setPosition(sf::Vector2f(screenView.getCenter().x + (screenView.getSize().x / 6), screenView.getSize().y - 54.0f));
	idText2.setFillColor(sf::Color::Blue);
	idText2.setString("Rule-Based");

	distanceText2.setFont(font);
	distanceText2.setCharacterSize(18);
	distanceText2.setFillColor(sf::Color::Blue);
	distanceText2.setPosition(screenView.getCenter().x + (screenView.getSize().x / 6), screenView.getSize().y - 36.0f);

	velocityText2.setFont(font);
	velocityText2.setCharacterSize(18);
	velocityText2.setFillColor(sf::Color::Blue);
	velocityText2.setPosition(screenView.getCenter().x + (screenView.getSize().x / 6), screenView.getSize().y - 18.0f);

	//Load in fuzzy engine
	engine = fl::FisImporter().fromFile("Fuzzy.fis");
}

Game::~Game()
{
}

void Game::handleInput(float deltaTime)
{
	//Line movement
	if (gameMode == 0)
	{
		if (input->isKeyDown(sf::Keyboard::Left))
		{
			if (line.getPosition().x > window->getView().getCenter().x - window->getView().getSize().x / 2)
			{
				line.move(-500.0f * deltaTime, 0.0f);
			}
		}
		if (input->isKeyDown(sf::Keyboard::Right))
		{
			if (line.getPosition().x + line.getSize().x < window->getView().getCenter().x + window->getView().getSize().x / 2)
			{
				line.move(500.0f * deltaTime, 0.0f);
			}
		}
	}

	//Changing modes
	if (input->isKeyDown(sf::Keyboard::Num0))
	{
		gameMode = 0;
		input->setKeyUp(sf::Keyboard::Num0);
	}
	if (input->isKeyDown(sf::Keyboard::Num1))
	{
		gameMode = 1;
		input->setKeyUp(sf::Keyboard::Num1);
	}
}

void Game::update(float deltaTime)
{
	if (gameMode == 0)
	{
		//Calculate distance (from the centre of the car to the centre of the line)
		distanceFromCarToLine = (car.getPosition().x + (car.getSize().x / 2)) - (line.getPosition().x + (line.getSize().x / 2));
		distanceFromCarToLine /= window->getSize().x;

		if (distanceFromCarToLine > 1)
		{
			distanceFromCarToLine = 1;
		}
		if (distanceFromCarToLine < -1)
		{
			distanceFromCarToLine = -1;
		}
		
		//Set the input values of the fuzzy system
		engine->setInputValue("Velocity", carVelocity);
		engine->setInputValue("Distance", distanceFromCarToLine);

		//Have the engine calculate the output
		engine->process();

		//Update the car velocity
		carVelocity += engine->getOutputValue("Steering");

		//Display distance and velocity
		distanceText.setString("Distance: " + std::to_string(distanceFromCarToLine));
		velocityText.setString("Velocity: " + std::to_string(carVelocity));
		outputText.setString("Steering: " + std::to_string(engine->getOutputValue("Steering")));

		//Move the car
		car.move(carVelocity * velocityMultiplier * deltaTime, 0.0f);

		//------------------------- (Rule Based Control)

		//Calculate distance (from the centre of the car to the centre of the line
		distanceFromCarToLine2 = (car2.getPosition().x + (car2.getSize().x / 2)) - (line.getPosition().x + (line.getSize().x / 2));
		distanceFromCarToLine2 /= window->getSize().x;

		//Calculate the velocity
		if (distanceFromCarToLine2 > 0.7)
		{
			carVelocity2 = -1.0f;
		}
		else if (distanceFromCarToLine2 > 0.4)
		{
			carVelocity2 = -0.4f;
		}
		else if (distanceFromCarToLine2 > 0.1)
		{
			carVelocity2 = -0.2f;
		}
		else if (distanceFromCarToLine2 > 0)
		{
			carVelocity2 = -0.1f;
		}

		else if(distanceFromCarToLine2 == 0)
		{
			carVelocity2 = 0.0f;
		}

		else if (distanceFromCarToLine2 < -0.7)
		{
			carVelocity2 = 1.0f;
		}
		else if (distanceFromCarToLine2 < -0.4)
		{
			carVelocity2 = 0.5f;
		}
		else if (distanceFromCarToLine2 < -0.1)
		{
			carVelocity2 = 0.2f;
		}
		else if (distanceFromCarToLine2 < 0)
		{
			carVelocity2 = 0.1f;
		}

		//Display text
		distanceText2.setString("Distance : " + std::to_string(distanceFromCarToLine2));
		velocityText2.setString("Velocity : " + std::to_string(carVelocity2));

		//Move the car
		car2.move(carVelocity2 * velocityMultiplier * deltaTime, 0.0f);
	}
	else if (gameMode == 1)
	{
		//Initialise temp variables
		float carDist = 0;
		float linePos = 0;
		carVelocity = 0;

		if (readyToTakeInput)
		{
			//Store car position
			std::cout << std::endl << "Enter line position (-350 <-> 350: ";
			std::cin >> linePos;

			//Set line position
			line.setPosition(linePos, 0.0f);

			//Store line position
			std::cout << std::endl << "Enter car distance (-1 <-> 1): ";
			std::cin >> carDist;

			if (carDist > 1)
			{
				carDist = 1;
			}
			if (carDist < -1)
			{
				carDist = -1;
			}

			car.setPosition(line.getPosition().x + (carDist * window->getSize().x), car.getPosition().y);

			//Store car velocity
			std::cout << "Enter car velocity: ";
			std::cin >> carVelocity;

			if (carVelocity > 1)
			{
				carVelocity = 1;
			}
			if (carVelocity < -1)
			{
				carVelocity = -1;
			}

			readyToTakeInput;
		}

		//Set input
		engine->setInputValue("Velocity", carVelocity);
		engine->setInputValue("Distance", carDist);

		//Calculate output
		engine->process();

		//Display results
		distanceText.setString("Distance: " + std::to_string(carDist));
		velocityText.setString("Velocity: " + std::to_string(carVelocity));
		outputText.setString("Steering: " + std::to_string(engine->getOutputValue("Steering")));

		std::cout << "Output: " << engine->getOutputValue("Steering") << std::endl;

		//Render
		render();

		//Ask whether to go again
		int a;
		std::cout << "Press 1 to try again or 2 to go back" << std::endl;
		std::cin >> a;

		if (a == 1)
		{
			readyToTakeInput = true;
		}
		else if (a == 2)
		{
			//If not, change mode and reset positions
			gameMode = 0;
			car.setPosition(screenView.getCenter().x, screenView.getCenter().y - car.getSize().y * 2);
			line.setPosition(sf::Vector2f(0.0f, 0.0f));
			car2.setPosition(screenView.getCenter().x, screenView.getCenter().y + car.getSize().y);
		}
	}
}

//Render game
void Game::render()
{
	beginDraw();

	//Set the view
	window->setView(screenView);

	window->draw(line);
	window->draw(car);
	window->draw(car2);

	window->draw(idText);
	window->draw(distanceText);
	window->draw(velocityText);
	window->draw(outputText);

	window->draw(idText2);
	window->draw(distanceText2);
	window->draw(velocityText2);

	endDraw();
}

//Clear buffer
void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

//Display buffer
void Game::endDraw()
{
	window->display();
}
