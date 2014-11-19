#include "map.h"

extern void drawImage(SDL_Surface *, int, int);

void loadMap(char *name)
{
	int x, y;
	FILE *fp;

	fp = fopen(name, "rb");

	/* If we can't open the map then exit */

	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);

		exit(1);
	}

	/* Read the data from the file into the map */

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			fscanf(fp, "%d", &map.tile[y][x]);
		}
	}

	/* Close the file afterwards */

	fclose(fp);
}

void drawMap()
{
	int x, y;
	
	/* Draw the background */
	
	drawImage(backgroundImage, 0, 0);

	/* Draw the map */

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			if (map.tile[y][x] != 0)
			{
				drawImage(brickImage, x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
}
