#pragma once
#include <array>
#include <Windows.h>

#define TILE_FLOOR 0
#define TILE_WALL 1


typedef struct 
{
	int r1_cutoff, r2_cutoff;
	int reps;
} generation_params;

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;

class Level
{
	private:
		int size_x, size_y;
		int fillprob;
		int generations;
		generation_params *params;
		generation_params *params_set;

	public:
		Level();
		~Level();

		void InitMap();
		void Generation();
		void PrintFunc();
		void PrintMap();
		int RandomPick();

		int CreateLevel(/*int argc, char **argv*/);

		int map1[SCREEN_HEIGHT][SCREEN_WIDTH];
		int map2[SCREEN_HEIGHT][SCREEN_WIDTH];
		CHAR_INFO charMap[SCREEN_HEIGHT][SCREEN_WIDTH];
		

};

