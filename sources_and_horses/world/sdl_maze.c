/* 
 this file is a hack job just to test a concept - all the functions are 
 included, just open in a directory with the pictures!
 
 compile with: 
 gcc -Wall -pedantic -std=c99 `sdl2-config --cflags --libs`
 
 Maze....BUT in SDL with moveable character
 */

#include <stdio.h>
#include "SDL.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE     32
#define MAX            20
#define OPEN ' '
#define WALL '#'
#define EXTRA_LINE 1

char maze[MAX][MAX];

void SDL_Start();
//void read_file(FILE**,  char maze[][MAX], int *row, int *column, int argc, char *argv);
void print_maze(char maze[][MAX], int row_size, int column_size);
int possible_move(char maze[][MAX], int x, int y, int row_size, int column_size); //is the move possible?

int main(int argc, char **argv)
{
  int row_size, column_size;
  int i = 0;
  int j = 0;
  int column_count = 0, row_count = 0; 
  char maze_element;
  FILE *file;
  const char *textcheck= ".txt";
  
 //read_file(maze, row, column, argc, *argv); commented out this function because seg faults like a champ - putting it in main.c

 /* reading in the text file - checking for errors */
 if ((argc == 2) &&(strstr(argv[1],textcheck)!= NULL)){
    file = fopen(argv[1], "r");
    if (file == NULL){
      printf( "Error reading file. Please check it exists and/or is not empty or corrupted.\n" ); 
      exit(1); 
    }
  }
  /* read the integers for the rows and columns */
  fscanf(file,"%d %d\n", &column_size, &row_size); //not checking...coding dangerously
  printf("row %d column %d\n", row_size, column_size);

  while ((maze_element = getc(file)) != EOF && i < MAX && j < MAX){
   
    
    if (maze_element == '\n'){     //if there is a newline, 
      j = 0;                       //avoid by resetting the column to zero
      i++;                         //and start on the next row
    }else{
      maze[i][j] = maze_element;   //for all other values, fill in
      j++;                         //column by column
    }
    
    column_count=j;
  row_count=i;
  }
  
  

  
  fclose(file);                    //close the maze file 
   
  printf("row %d column %d\n", row_size, column_size);
  printf("row %d column %d\n", row_count, column_count);
  print_maze(maze, row_size, column_size);
  SDL_Start();
  
	return 0;
}

void SDL_Start()
{
  SDL_Window *window = NULL;
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "\nUnable to initialise SDL:  %s\n",
						SDL_GetError());
		exit(1);
	}else{
		window = SDL_CreateWindow ("MADLAB_test2",                    //window name
                               SDL_WINDOWPOS_UNDEFINED,      //x-axis on the screen coordinate
                               SDL_WINDOWPOS_UNDEFINED,      //y-axis screen coordinate
                               SCREEN_WIDTH, SCREEN_HEIGHT,  //size of the window
                               SDL_WINDOW_RESIZABLE);        //make the window resizeable       

		if (window == NULL){
			printf("Could not create window: %s\n", SDL_GetError());
			exit(1);
		}
	}
   
  SDL_Delay(5000);
	atexit(SDL_Quit);
}

/*
void read_file(char maze[][MAX], int *row, int *column, int argc, char *argv)
{

//some stuff about the pointer being undeclared. Don't care enough right now to fix
  int i = 0, j = 0;  
  char maze_element;
  int column_count = 0, row_count = 0; 
  FILE *file;
  
  if ((argc == 2)){
    file = fopen(argv[1], "r");
    if (file == NULL){
      printf( "Error reading file. Please check it exists and/or is not empty or corrupted.\n" ); 
      exit(1); 
    }
  }
  while ((maze_element = getc(file)) != EOF && i < MAX && j < MAX){

  if (maze_element == '\n'){     //if there is a newline, 
    j = 0;                       //avoid by resetting the column to zero
    i++;                         //and start on the next row
  }else{
    maze[i][j] = maze_element;   //for all other values, fill in
    j++;                         //column by column
    }
  }
  
  row_count = i;
  column_count = j;
  *row = row_count;
  *column = column_count;
  
  fclose(file);                  //close the maze file
   
}
* */

void print_maze(char maze[][MAX], int row_size, int column_size)
{
  for(int i = 0; i < row_size; i++){
    for(int j = 0; j < column_size; j++){
      printf("%c", maze[i][j]);
    } 
    printf("\n");
  }
  printf("\n");
}

void draw_image(SDL_Window *window)(maze_block, x_axis * BLOCK_SIZE, y_axis * BLOCK_SIZE); 
{

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /*load maze block*/
  SDL_Surface *maze_image   = SDL_LoadBMP("grass.bmp");     
  SDL_Surface *maze_surface = SDL_ConvertSurfaceFormat(maze_image,                //writing it to a surface
                                                       SDL_GetWindowPixelFormat(window), 
                                                       0); 
                                                           
  SDL_Texture *texture_maze = SDL_CreateTextureFromSurface(renderer,
                                                           maze_surface); 
  SDL_FreeSurface(maze_image);                                                    //freeing the image; no longer needed
  
  /*load moving character*/
  SDL_Surface *temp_image = SDL_LoadBMP("prof2.bmp");                             //loading sprite sheet

  SDL_Surface *surface    = SDL_ConvertSurfaceFormat(temp_image,                  //writing it to a surface
                                                     SDL_GetWindowPixelFormat(window), 
                                                     0);     
                                                //freeing the image; no longer needed

  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 
                                                255, 0, 255));                    //removing the hot pink from sprite sheet
                                           
  SDL_Texture *texture_sprite   = SDL_CreateTextureFromSurface(renderer,
                                                               surface);          //creating a texture
                                            
  SDL_FreeSurface(temp_image);              
}

void draw_maze(char maze[][MAX])  
{  
  int x_axis, y_axis;  
  
  /*drawing the maze in SDL, with tons of style*/

  for (y_axis = 0; y_axis < MAX; y_axis++){  
    for (x_axis = 0; x_axis < MAX; x_axis++){  
      if (maze[y_axis][x_axis] != OPEN){  
        draw_image(maze_block, x_axis * BLOCK_SIZE, y_axis * BLOCK_SIZE);  
      } // else{
        //draw_image(maze_block, x_axis * BLOCK_SIZE, y_axis * BLOCK_SIZE);  
       // }  
    }  
  } 
}

int possible_move(char maze[][MAX], int x, int y, int row_size, int column_size)
{
      int possible = 1;
      
      if (((x > row_size-EXTRA_LINE) || (x < 0)) || ((y > column_size-EXTRA_LINE) || (y < 0))){ //for the boundary of the maze
        possible = 0; //fails
      }
      else if (maze[x][y] == WALL){ //if that maze space is populated by this
        possible = 0; //fails
      }
      return possible; //move is possible
}
