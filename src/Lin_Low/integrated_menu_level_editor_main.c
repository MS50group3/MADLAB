#include <stdlib.h>
#include "display.h"
#include <stdbool.h>

void runloadscreen(){
    
    Display d=newDisplay();
    startFrame(d);
    
    LoadScreen(d);

    quit(d);
}

int main(int argc, char *argv[])
{
    runloadscreen();

    return 0;
}
