#include <conio.h>
#include <Windows.h>
#include <vector>

#include "Player.h"
#include "Ladder.h"
#include "Level.h"

using namespace std;

void Initialise();
bool Update();
void GetInput();
bool CheckCollision(Direction movingTo, Object movingObject);

//Buffer variables
HANDLE hOutput;
COORD dwBufferSize;
COORD dwBufferCoord;
SMALL_RECT rcRegion;
CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

static Player p = Player();
static Ladder ladder = Ladder();
Level l = Level();


int main()
{
	Initialise();
	bool quit = false;

	while (!quit) {
		quit = Update();
	}
	return 0; 
}

void Initialise()
{
	hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	dwBufferCoord = { 0, 0 };
	rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	
	l.CreateLevel();

	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_WIDTH; ++j)
		{
			buffer[i][j].Char.AsciiChar = l.charMap[i][j].Char.AsciiChar;
			buffer[i][j].Attributes = 0x0F; //Color Attribute
		}
	}

	bool playerPlaced = false;
	for (int i = 0; playerPlaced == false; ++i)
	{
		for (int j = 0; playerPlaced == false; ++j)
		{
			if (buffer[i][j].Char.AsciiChar == ' ' && playerPlaced == false)
			{
				playerPlaced = true;
				p.Initialise(point(j, i));//place player
				buffer[p.GetPosition().y][p.GetPosition().x].Char.AsciiChar = p.GetRepresentation();
				buffer[p.GetPosition().y][p.GetPosition().x].Attributes = 0x0A; //Color Attribute
			}
		}
	}

	bool ladderPlaced = false;
	for (int i = SCREEN_HEIGHT - 1; ladderPlaced == false; --i)
	{
		for (int j = SCREEN_WIDTH - 1; ladderPlaced == false; --j)
		{
			if (buffer[i][j].Char.AsciiChar == ' ' && ladderPlaced == false)
			{
				ladderPlaced = true;
				ladder.Initialise(point(j, i)); //place ladder
				buffer[ladder.GetPosition().y][ladder.GetPosition().x].Char.AsciiChar = ladder.GetRepresentation();
				buffer[ladder.GetPosition().y][ladder.GetPosition().x].Attributes = 0x0B; //Color Attribute

			}
		}
	}
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}
bool Update()
{
	//For clearing previous buffer location.
	point previousPlayerPosition = p.GetPosition();

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	//Note: Game will wait for input before refreshing again. TODO fix this and make a real game loop.
	GetInput();
		
	buffer[p.GetPosition().y][p.GetPosition().x].Char.AsciiChar = p.GetRepresentation();
	buffer[p.GetPosition().y][p.GetPosition().x].Attributes = 0x0A; //Color Attribute
		
	//Need to remove P from last place in buffer.
	if (previousPlayerPosition.x != p.GetPosition().x ||
		previousPlayerPosition.y != p.GetPosition().y)
	{
		buffer[previousPlayerPosition.y][previousPlayerPosition.x].Char.AsciiChar = ' ';
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
		if (key == 72) //up arrow
		{
			if (CheckCollision(UP, p))
				p.Move(UP);
		}
		else if (key == 75) //left arrow
		{
			if (CheckCollision(LEFT, p))
				p.Move(LEFT);
		}
		else if (key == 77) //right
		{
			if (CheckCollision(RIGHT, p))
				p.Move(RIGHT);
		}
		else if (key == 80) //down
		{
			if (CheckCollision(DOWN, p))
				p.Move(DOWN);
		}
	}
}

bool CheckCollision(Direction movingTo, Object movingObject)
{
	char collisionChar;
	switch (movingTo)
	{
	case UP:
		collisionChar = buffer[movingObject.GetPosition().y - 1][movingObject.GetPosition().x].Char.AsciiChar;
		break;
	case DOWN:
		collisionChar = buffer[movingObject.GetPosition().y + 1][movingObject.GetPosition().x].Char.AsciiChar;
		break;
	case LEFT:
		collisionChar = buffer[movingObject.GetPosition().y][movingObject.GetPosition().x - 1].Char.AsciiChar;
		break;
	case RIGHT:
		collisionChar = buffer[movingObject.GetPosition().y][movingObject.GetPosition().x + 1].Char.AsciiChar;
		break;
	default:
		break;
	}
	if (collisionChar == '#')
		return false;
	else if (collisionChar == '!')
		Initialise();
	return true;
}