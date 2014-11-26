#include <stdio.h>
#include <stdlib.h>

#define ROOM_X 25
#define ROOM_Y 24
#define RESET -1

typedef struct roomGrid
{
	int **roomArray;
}roomGrid;

void makeRoom(roomGrid *rg, FILE *fp);
void printArray(roomGrid *rg);


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
	printArray(rg);


	return 0;
}


// (rg -> roomArray)[ROOM_X] = calloc(ROOM_Y +1, sizeof(*int));

void makeRoom(roomGrid *rg, FILE *fp)
{
	rg -> roomArray = 0;

	rg -> roomArray = (int **)calloc((ROOM_Y) + 1, sizeof(int *));
	if (rg -> roomArray == NULL)
	{
		fprintf(stderr, "No memory available.\n");
		exit(3);
	}

	for(int i = 0; i <= ROOM_Y; i++)
	{
		rg -> roomArray[i] = (int *)calloc((ROOM_X)+1, sizeof(int));
		if (rg -> roomArray[i] ==  NULL)
		{
			fprintf(stderr, "No memory available.\n");
			exit(4);
		}
	}

	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			printf("%2d", rg -> roomArray[i][j]);
		}
		printf("\n");
	}
		printf("\n");



// for (int i = 0, j = 0, c = 0; j <= ROOM_X && i <= ROOM_Y; j++)
// 	{
// 		c = fgets(*rg -> roomArray, 1, fp);

// 		(c == '\n') ? (j = RESET, i++): (rg -> roomArray[i][j] = c);
// 	}

	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			fscanf(fp, "%1d", &rg -> roomArray[i][j]);
		}
		
	}


	// for (int i = 0; i < ROOM_Y; i++)
	// {
	// 	for (int j = 0; j < ROOM_X; j++)
	// 	{
	// 		&rg -> roomArray[i][j] = fgets(rg -> roomArray, ROOM_X,fp);
	// 	}
	// }
}


void printArray(roomGrid *rg)
{
	for (int i = 0; i < ROOM_Y; i++)
	{
		for (int j = 0; j < ROOM_X; j++)
		{
			printf("%2d", rg -> roomArray[i][j]);
		}
		printf("\n");
	}
}



// for (int i = 0; i < rg -> ROOM_Y; i++)
// {
// 	for (int j = 0; j < rg -> ROOM_X; j++)
// 	{
// 		fscanf(fp, "%s", ROOM_X);
// 	}
// }
