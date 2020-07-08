#include "Input.h"

//forces a key to be pressed
void Input::setKeyDown(int key)
{
	keys[key] = true;
}

//forces a key to be not pressed
void Input::setKeyUp(int key)
{
	keys[key] = false;
}

//returns whether a key is being pressed
bool Input::isKeyDown(int key)
{
	return keys[key];
}

//forces the mouses' x position
void Input::setMouseX(int lx)
{
	mouse.x = lx;
}

//forces the mouses' y position
void Input::setMouseY(int ly)
{
	mouse.y = ly;
}

//forces a mouse position
void Input::setMousePosition(int lx, int ly)
{
	mouse.x = lx;
	mouse.y = ly;
}

//returns the mouses' x positon
int Input::getMouseX()
{
	return mouse.x;
}

//returns the mouses' y position
int Input::getMouseY()
{
	return mouse.y;
}

//forces the left mouse button to be pressed
void Input::setMouseLeftDown(bool left)
{
	mouse.left = left;
}

//returns whether the left mouse button is being pressed
bool Input::isMouseLeftDown()
{
	return mouse.left;
}

Input::Input()
{
}


Input::~Input()
{
}
