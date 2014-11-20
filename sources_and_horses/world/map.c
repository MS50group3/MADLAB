#include "map.h"

void draw_image(SDL_Surface *, int, int); //what's happening here

void load_room(char *name) //this takes the name of the map.txt file that is appropriate for the level
{
	int x, y;
	FILE *file;

	fp = fopen(name, "r");

	if (fp == NULL){  //if the map is empty, corrupt, or is otherwise unread
		printf("Failed to open map %s\n", name);
		exit(1);        //bail out
	}

  /*this blocks the room*/
	for (y = 0; y < ROOM_Y; y++){
		for (x = 0;  x <ROOM_X; x++){
			fscanf(fp,"%d", &room.tile[y][x]); //do not upload a char map! use 1s and 0s
		}
	}

	fclose(file);
}

void drawRoom()
{
	int x, y;
	
	/* Draw the background */
	
	draw_image(backgroundImage, 0, 0);

	/* Draw the map */

	for (y=0;y<MAX_MAP_Y;y++){
		for (x=0;x<MAX_MAP_X;x++){
			if (map.tile[y][x] != 0){
				draw_image(solidsImage, x * TILE_SIZE, y * TILE_SIZE); //maze image to be replaced - testing purposes only
			}
		}
	}
}
