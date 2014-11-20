/* Graphics module for bouncing ball. */
#include <stdbool.h>

typedef struct display *Display;

Display newDisplay();
void startFrame(Display d);
void drawBall(Display d, float x, float y);
void endFrame(Display d);
void quit(Display d);
bool getEvent(Display d);

