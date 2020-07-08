#include "fl/Headers.h"
#include "SFML/Graphics.hpp"

#include "FuzzyEngine.h"
#include "Input.h"
#include "Game.h"


int main(int argc, char* argv[]) {
	//Set up game window
	sf::RenderWindow window(sf::VideoMode(800, 600), "AI Racing Game");

	//Set input
	Input input;
	//Clock to calculate deltaTime
	sf::Clock clock;
	float deltaTime;

	Game game(&window, &input);

	//While the game is running
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//checks if the red x button has been pressed, if so closes the game
			case sf::Event::Closed:
				window.close();
				break;
				//checks if the game window has been resized, if so resizes the game
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
				//checks if a key has been pressed, if so updates the input class
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
				//checks if a key has been released, if so updates the input class
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
				//checks whether the mouse's position has changed, if so updates it
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
				//checks whether the left mouse button has been pressed, if so updates the function
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(true);
				}
				break;
				//checks if the mouse button has been released, if so updates the function
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(false);
				}
				break;
				//default case 
			default:
				break;
			}
		}
		//Calculate deltaTime
		deltaTime = clock.restart().asSeconds();

		//Call functions needed every frame
		game.handleInput(deltaTime);
		game.update(deltaTime);
		game.render();
	}

	return 0;
}
