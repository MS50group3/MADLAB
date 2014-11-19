/* Puzzle framework */

#include <stdlib.h>
#include "display.h"

void run(){

    Display d = newDisplay();

    while(getEvent(d) == false){
	    startFrame(d);
	    drawBall(d,0.5,0.5);
    	endFrame(d);
	}
    quit(d);
}

int main(){ 
	run(); 
}

