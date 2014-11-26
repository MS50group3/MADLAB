/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

/* definitions */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define TILE_SIZE    32
#define ROOM_X 25
#define ROOM_Y 24

typedef struct roomGrid
{
	char **roomArray;
}roomGrid;


//void HandleEvent(SDL_Event event, SDL_Rect rcSprite, SDL_Rect rcSrc);
void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg);
//void draw(SDL_Renderer *renderer, SDL_Rect rcSprite, SDL_Rect rcSrc, SDL_Window *window, SDL_Rect rcBrick, roomGrid *rg);
//void run();



int main(int argc, char *argv[])
{
	roomGrid roomStuff, *rg;
	rg = &roomStuff;

	FILE *fp = NULL;
	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("File could not be opened.\n");
		exit(1);
	}
	printf("File was opened.\n");

	makeRoom(rg, fp);
	fclose(fp);

	//run(rg);
	printArray(rg);

	return 0;
}


// (rg -> roomArray)[ROOM_X] = calloc(ROOM_Y +1, sizeof(char*));

void makeRoom(roomGrid *rg, FILE *fp)
{
	rg -> roomArray = 0;

	rg -> roomArray = (char **)calloc((ROOM_Y) + 1, sizeof(char *));
	if (rg -> roomArray == NULL)
	{
		fprintf(stderr, "No memory available.\n");
		exit(3);
	}

	for(int i = 0; i <= ROOM_Y; i++)
	{
		rg -> roomArray[i] = (char *)calloc((ROOM_X)+1, sizeof(char));
		if (rg -> roomArray[i] ==  NULL)
		{
			fprintf(stderr, "No memory available.\n");
			exit(4);
		}
	}

	//rg -> roomArray[ROOM_X] = calloc(ROOM_Y +1, sizeof(char*));



	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			fscanf(fp, "%c", &rg -> roomArray[i][0]);
		}
	}
	

	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			printf("%2c", rg -> roomArray[i][j]);
		}
		printf("\n");
	}
}

void printArray(roomGrid *rg)
{
	for (int i = 0; i <= ROOM_Y; i++)
	{
		for (int j = 0; j <= ROOM_X; j++)
		{
			printf("%2c", rg -> roomArray[i][j]);
		}
		printf("\n");
	}
}