#include <conio.h>
#include <Windows.h>
#include <vector>
#include <time.h>

#include "Player.h"
#include "Ladder.h"
#include "Monster.h"
#include "Shovel.h"
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
static Shovel shovel = Shovel();
Level l = Level();
vector<Monster> monsterTab;

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
	for (int i = 0; playerPlaced == false; ++i) //NO ERROR CHECKING  D:  WHAT HAPPENS IF i/j go out of range(TODO)
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

	srand(time(NULL));
	int cptMonsters = 0;
	int cptMonstersMax = 20;

	while(!monsterTab.empty()) //Empty the vector
		monsterTab.pop_back();

	while (cptMonsters < cptMonstersMax)
	{
		for (int i = SCREEN_HEIGHT - 1; i > 0; --i)
		{
			for (int j = SCREEN_WIDTH - 1; j > 0; --j)
			{
				int RandomInt = rand() % 100;
				if (buffer[i][j].Char.AsciiChar == ' ' && cptMonsters <= cptMonstersMax && RandomInt == 1)
				{
					monsterTab.push_back(Monster());
					monsterTab[cptMonsters].Initialise(point(j, i)); //place monster
					buffer[monsterTab[cptMonsters].GetPosition().y][monsterTab[cptMonsters].GetPosition().x].Char.AsciiChar = monsterTab[cptMonsters].GetRepresentation();
					buffer[monsterTab[cptMonsters].GetPosition().y][monsterTab[cptMonsters].GetPosition().x].Attributes = 0x0C; //Color Attribute
					++cptMonsters;
				}
			}
		}
	}

	bool shovelPlaced = false;
	while (!shovelPlaced)
	{
		point checking = p.GetPosition();
		point furthestShovelPositionFound;
		int pacesFromPlayer = 0;
		int count = 0;
		vector<point> uncheckedXPaths;
		vector<point> uncheckedYPaths;
		
		if (buffer[checking.y][checking.x + 1].Char.AsciiChar != '#')
			uncheckedXPaths.push_back(point(checking.y, checking.x + 1));
		else if (buffer[checking.y - 1][checking.x].Char.AsciiChar != '#')
				uncheckedYPaths.push_back(point(checking.y - 1, checking.x));

		while (!uncheckedXPaths.empty() || !uncheckedYPaths.empty())
		{
			if (!uncheckedXPaths.empty())
			{
				uncheckedXPaths.pop_back();
				//Check the path we have marked
				while (buffer[checking.y][checking.x + 1].Char.AsciiChar != '#')
				{
					
					uncheckedXPaths.push_back(point(checking.y, checking.x + 1));
					if (buffer[checking.y + 1][checking.x].Char.AsciiChar != '#')
						uncheckedYPaths.push_back(point(checking.y + 1, checking.x));
					++checking.x;
					count = checking.x + checking.y;
					if (count > pacesFromPlayer)
					{
						pacesFromPlayer = count;
						furthestShovelPositionFound = checking;
					}
				}
			}
			if (!uncheckedYPaths.empty())
			{
				uncheckedYPaths.pop_back();
				while (buffer[checking.y + 1][checking.x].Char.AsciiChar != '#')
				{	
					uncheckedYPaths.push_back(point(checking.y + 1, checking.x));
					if (buffer[checking.y][checking.x + 1].Char.AsciiChar != '#')
						uncheckedXPaths.push_back(point(checking.y, checking.x + 1));
					++checking.y;
					count = checking.x + checking.y;
					if (count > pacesFromPlayer)
					{
						pacesFromPlayer = count;
						furthestShovelPositionFound = checking;
					}
				}
			}
		}
		furthestShovelPositionFound = checking;
		shovel.Initialise(furthestShovelPositionFound);
		buffer[shovel.GetPosition().y][shovel.GetPosition().x].Char.AsciiChar = shovel.GetRepresentation();
		buffer[shovel.GetPosition().y][shovel.GetPosition().x].Attributes = 0x0E; //Color Attribute
		shovelPlaced = true;
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
	
	srand(time(NULL));
		
	point previousMonsterPosition;
	for (int i = 0; i < monsterTab.size(); ++i)
	{
		
		previousMonsterPosition = monsterTab[i].GetPosition();

		monsterTab[i].Update();

		int RandomInt = rand()%4;

		switch (RandomInt)
		{
		case 0:
			if (CheckCollision(RIGHT, monsterTab[i]))
			{
				monsterTab[i].Move(RIGHT);
			}
			break;
		case 1:
			if (CheckCollision(LEFT, monsterTab[i]))
			{
				monsterTab[i].Move(LEFT);
			}
			break;
		case 2:
			if (CheckCollision(UP, monsterTab[i]))
			{
				monsterTab[i].Move(UP);
			}
			break;
		case 3:
			if (CheckCollision(DOWN, monsterTab[i]))
			{
				monsterTab[i].Move(DOWN);
			}
			break;
		default:
			break;
		}


		buffer[monsterTab[i].GetPosition().y][monsterTab[i].GetPosition().x].Char.AsciiChar = monsterTab[i].GetRepresentation();
		buffer[monsterTab[i].GetPosition().y][monsterTab[i].GetPosition().x].Attributes = 0x0C; //Color Attribute

		//Need to remove monster from last place in buffer.
		if (previousMonsterPosition.x != monsterTab[i].GetPosition().x ||
			previousMonsterPosition.y != monsterTab[i].GetPosition().y)
		{
			if(buffer[previousMonsterPosition.y][previousMonsterPosition.x].Char.AsciiChar != p.GetRepresentation());
				buffer[previousMonsterPosition.y][previousMonsterPosition.x].Char.AsciiChar = ' ';
		}
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
			p.Look(UP);
		}
		else if (key == 75) //left arrow
		{
			if (CheckCollision(LEFT, p))
				p.Move(LEFT);
			p.Look(LEFT);
		}
		else if (key == 77) //right
		{
			if (CheckCollision(RIGHT, p))
				p.Move(RIGHT);
			p.Look(RIGHT);
		}
		else if (key == 80) //down
		{
			if (CheckCollision(DOWN, p))
				p.Move(DOWN);
			p.Look(DOWN);
		}
	}
	else if (key == ' ')
	{
		if (p.GetHasShovel())
			switch (p.GetRepresentation())
		{
			case '^':
				buffer[p.GetPosition().y - 1][p.GetPosition().x].Char.AsciiChar = ' ';
				break;
			case  'v':
				buffer[p.GetPosition().y + 1][p.GetPosition().x].Char.AsciiChar = ' ';
				break;
			case '<':
				buffer[p.GetPosition().y][p.GetPosition().x - 1].Char.AsciiChar = ' ';
				break;
			case '>':
				buffer[p.GetPosition().y][p.GetPosition().x + 1].Char.AsciiChar = ' ';
				break;
			default:
				break;
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
		if (movingObject.GetRepresentation() == p.GetRepresentation())
			Initialise();
		else
			return false;
	else if (collisionChar == 'T')
		if (movingObject.GetRepresentation() == p.GetRepresentation()) //This is dumb but it works
			p.SetHasShovel(true);
		else
			return false;
	else if ((collisionChar == '§' && movingObject.GetRepresentation() == p.GetRepresentation())
		|| (collisionChar == p.GetRepresentation() && movingObject.GetRepresentation() == '§'))
	{
		for (int i = 0; i < SCREEN_HEIGHT; ++i)
		{
			for (int j = 0; j < SCREEN_WIDTH; ++j)
			{
				buffer[i][j].Char.AsciiChar = '!';
				buffer[i][j].Attributes = 0x0C; //Color Attribute
			}
		}
	}
	return true;
}