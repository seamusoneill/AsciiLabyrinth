#include <conio.h>
#include <Windows.h>

#include "Player.h"

using namespace std;

const int SCREEN_WIDTH = 256; //Making these too big causes a stack overflow. I don't know what the limit is
const int SCREEN_HEIGHT = 256;

bool Update();
void GetInput();

Player p = Player();

int main()
{
	bool quit = false;

	while (!quit) {
		Update();
	}
	return 0;
}

//Buffer declared here for visibility
HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

bool Update()
{
	//For clearing previous buffer location.
	int playerPositionX = p.GetX();
	int playerPositionY = p.GetY();

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	//Note: Game will wait for input before refreshing again. TODO fix this and make a real game loop.
	GetInput();
	
	if (p.GetX() > 0 & p.GetY() > 0) //This won't happen if we have walls.
	{
		//Need to remove P from last place in buffer.
		
		buffer[p.GetX()][p.GetY()].Char.AsciiChar = p.GetRepresentation();
		buffer[p.GetX()][p.GetY()].Attributes = 0x0E; //Color Attribute
		buffer[playerPositionX][playerPositionY].Char.AsciiChar = ' ';
	}
	else{
		//Set position on relevant axis to = 0;
	}
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	return false;
}

void GetInput()
{

	char key = 127;

	key = _getch();

	if (key == 0 || key == -32)  //get a special key
	{
		key = _getch();
		//TODO Due to the way the buffer is structured all of these are topsy turvy x = rows. y = columns
		if (key == 72) //up arrow
		{
			p.Move(LEFT);
		}
		else if (key == 75) //left arrow
		{
			p.Move(DOWN);
		}
		else if (key == 77) //right
		{
			p.Move(UP);
		}
		else if (key == 80) //down
		{
			p.Move(RIGHT);
		}
	}
}

