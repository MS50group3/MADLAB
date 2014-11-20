/*a bit of collision*/
#include <stdio.h>
#define OPEN 0

enum orientation {north, south, west, east};

/*collision for the edge of the screen*/

//sprite variable to be renamed//
int main (void)
{
/*rules for movement left - right*/
  if(rc_sprite.x <= 0){                           //if the sprite movements left bring it to zero x axis
    rc_sprite.x = 0;                              //the sprite's x-axis remains at zero
  }
  if(rc_sprite.x >= SCREEN_WIDTH - BLOCK_SIZE){   //if the sprite's movements go all the way right
    rc_sprite.x = SCREEN_WIDTH - BLOCK_SIZE;      //subtract block size so you can still draw the sprite
  }                                           
/*rules for movement up - down*/
  if(rc_sprite.y <= 0){                           //if the sprite movements up bring it to zero y axis
    rc_sprite.y = 0;                              //the sprite's x-axis remains at zero
  }
  if (rc_sprite.y >= SCREEN_HEIGHT - BLOCK_SIZE){ //if the sprite's movements go all the way down
	rc_sprite.y = SCREEN_HEIGHT - BLOCK_SIZE;     //subtract block size so you can still draw the sprite
  }
  else if(room[y][x] != 0){                       //rule to take care of map blocking - spaces sprite can move in the room
	
  }
}
void movement (int room[][MAX], int x, int y)
{
  rc_sprite.y = room[y];
  rc_sprite.x = room[x];
  
  /*north*/
  if ((possible_move(room, x, (y+1), row_size, column_size) == 1) && (room[x][(y+1)]) ==  OPEN){
	rc_sprite.y = room[y+1];
    rc_sprite.x = room[x];
  }else{
    rc_sprite.y = room[y];
    rc_sprite.x = room[x];
  }
  /*south*/
  if ((possible_move(room, x, (y-1), row_size, column_size) == 1) && (room[x][(y-1)]) ==  OPEN){
	rc_sprite.y = room[y-1];
    rc_sprite.x = room[x];
  }else{
    rc_sprite.y = room[y];
    rc_sprite.x = room[x];
  }
  /*east*/
    if ((possible_move(room, (x+1), y, row_size, column_size) == 1) && (room[x+1][y)]) ==  OPEN){
	rc_sprite.y = room[y];
    rc_sprite.x = room[x+1];
  }else{
    rc_sprite.y = room[y];
    rc_sprite.x = room[x];
  }
  /*west*/
  if ((possible_move(room, (x-1), y, row_size, column_size) == 1) && (room[x-1][y)]) ==  OPEN){
	rc_sprite.y = room[y];
    rc_sprite.x = room[x-1];
  }else{
    rc_sprite.y = room[y];
    rc_sprite.x = room[x];
  }
}

int possible_move(char maze[][MAX], int x, int y, int row_size, int column_size)
{
  int possible = 1;

  if (((x > row_size) || (x < 0)) || ((y > column_size) || (y < 0))){ //for the boundary of the room
    possible = 0; //fails
  }
  else if (room[x][y] != OPEN){ //if space is populated....
    possible = 0;               //fails
  }
    return possible;            //move is possible
}
