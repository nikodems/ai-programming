//Taken from CMP105 by Paul Robertson
#pragma once

//class used for the input
class Input
{
private:
	struct Mouse
	{
		int x, y;
		bool left;
	};

public:
	//Set key states
	void setKeyDown(int key);
	void setKeyUp(int key);
	//Check a key's state
	bool isKeyDown(int key);

	//Set mouse states
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	void setMouseLeftDown(bool left);
	//Get mouse states
	int getMouseX();
	int getMouseY();
	bool isMouseLeftDown();

	Input();
	~Input();
private:
	//Hold key values
	bool keys[256]{ false };
	Mouse mouse;

};

