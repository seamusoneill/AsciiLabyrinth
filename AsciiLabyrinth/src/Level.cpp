#include "Level.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <array>

Level::Level()
{
}


Level::~Level()
{
}

int Level::CreateLevel(/*int argc, char **argv*/)
{
	int ii, jj;

	/*if (argc < 7) {
		printf("Usage: %s xsize ysize fill (r1 r2 count)+\n", argv[0]);
		return 1;
	}*/

	size_x = SCREEN_WIDTH;
	size_y = SCREEN_HEIGHT;
	fillprob = 40;

	generations =  (10 - 4) / 3;

	params = params_set = (generation_params*)malloc(sizeof(generation_params) * generations);

	for (ii = 4; ii + 2 < 10; ii += 3)
	{
		params->r1_cutoff = 8;
		params->r2_cutoff = 5;
		params->reps = 10;
		params++;
	}

	srand(time(NULL));

	InitMap();

	for (ii = 0; ii < generations; ii++)
	{
		params = &params_set[ii];
		for (jj = 0; jj < params->reps; jj++)
		{
			Generation();
		}
	}

	//PrintFunc();
	PrintMap();
	return 0;
}


void Level::InitMap()
{
	int xi, yi;

	for (yi = 1; yi < size_y - 1; ++yi)
	{
		for (xi = 1; xi < size_x - 1; xi++)
		{
			map1[yi][xi] = RandomPick();
		}
	}

	for (yi = 0; yi < size_y; ++yi)
	{
		for (xi = 0; xi < size_x; ++xi)
		{
			map2[yi][xi] = TILE_WALL;
		}
	}

	for (yi = 0; yi < size_y; ++yi)
	{
		map1[yi][0] = map1[yi][size_x - 1] = TILE_WALL;
	}

	for (xi = 0; xi < size_x; ++xi)
	{
		map1[0][xi] = map1[size_y - 1][xi] = TILE_WALL;
	}
}

void Level::Generation()
{
	int xi, yi, ii, jj;

	for (yi = 1; yi < size_y - 1; yi++)
		for (xi = 1; xi < size_x - 1; xi++)
		{
			int adjcount_r1 = 0,
				adjcount_r2 = 0;

			for (ii = -1; ii <= 1; ii++)
				for (jj = -1; jj <= 1; jj++)
				{
					if (map1[yi + ii][xi + jj] != TILE_FLOOR)
						adjcount_r1++;
				}
			for (ii = yi - 2; ii <= yi + 2; ii++)
				for (jj = xi - 2; jj <= xi + 2; jj++)
				{
					if (abs(ii - yi) == 2 && abs(jj - xi) == 2)
						continue;
					if (ii<0 || jj<0 || ii >= size_y || jj >= size_x)
						continue;
					if (map1[ii][jj] != TILE_FLOOR)
						adjcount_r2++;
				}
			if (adjcount_r1 >= params->r1_cutoff || adjcount_r2 <= params->r2_cutoff)
				map2[yi][xi] = TILE_WALL;
			else
				map2[yi][xi] = TILE_FLOOR;
		}
	for (yi = 1; yi < size_y - 1; yi++)
		for (xi = 1; xi < size_x - 1; xi++)
			map1[yi][xi] = map2[yi][xi];
}

void Level::PrintFunc()
{
	int ii;

	printf("W[0](p) = rand[0,100) < %i\n", fillprob);

	for (ii = 0; ii<generations; ii++)
	{
		printf("Repeat %i: W'(p) = R[1](p) >= %i",
			params_set[ii].reps, params_set[ii].r1_cutoff);

		if (params_set[ii].r2_cutoff >= 0)
			printf(" || R[2](p) <= %i\n", params_set[ii].r2_cutoff);
		else
			putchar('\n');
	}
}

void Level::PrintMap()
{
	int xi, yi;

	for (yi = 0; yi < size_y; yi++)
	{
		for (xi = 0; xi < size_x; xi++)
		{
			switch (map1[yi][xi]) 
			{
				case TILE_WALL:  
					charMap[yi][xi].Char.AsciiChar = '#'; 
					break;
				case TILE_FLOOR: 
					charMap[yi][xi].Char.AsciiChar =  ' '; 
					break;
			}
		}
	}
}

int Level::RandomPick()
{
	if (rand() % 100 < fillprob)
		return TILE_WALL;
	else
		return TILE_FLOOR;
}