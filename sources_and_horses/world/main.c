/* This tutorial will open a 640 x 480 screen
** and display a map. Pressing escape
** or closing the window will exit the program
*/

#include "main.h"

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void loadMap(char *);
extern SDL_Surface *loadImage(char *);
extern void draw(void);
extern void delay(unsigned int);

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;
	
	/* Start up SDL */
	
	init("Parallel Realities Tutorial 11");
	
	/* Call the cleanup function when the program exits */
	
	atexit(cleanup);
	
	go = 1;
	
	/* Load the brick image */
	
	brickImage = loadImage("gfx/brick.png");
	
	/* If we get back a NULL image, just exit */
	
	if (brickImage == NULL)
	{
		exit(1);
	}
	
	/* Load the background image */
	
	backgroundImage = loadImage("gfx/background.png");
	
	/* If we get back a NULL image, just exit */
	
	if (backgroundImage == NULL)
	{
		exit(1);
	}
	
	loadMap("data/maps/map01.dat");
	
	/* Loop indefinitely for messages */
	
	while (go == 1)
	{
		getInput();
		
		draw();
		
		/* Sleep briefly to stop sucking up all the CPU time */
		
		delay(frameLimit);
		
		frameLimit = SDL_GetTicks() + 16;
	}
	
	/* Exit the program */
	
	exit(0);
}
