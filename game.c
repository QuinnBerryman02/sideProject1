#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

char startNewGame;
char action;
int gameNotOver = 1;
char playerMove;
int player[2] = {7,3};
int hp = 100;
int damage = 10;
int level = 1;
int sword = 0;
int xp = 0;
int eHp;
int eDamage;
int map[64][60] = { // Looked up how to declare a matrix at https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+4,-4,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+3,+3,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+4,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+5,+5,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+5,+5,+5,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+6,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,-7,+6,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+7,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+7,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,-9,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+1,+2,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
//  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
//  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  };

void move ();       //done
void cycle ();      //done
void display();     //done
void fight ();      //done
void playerTurn (); //done
void enemyTurn ();  //done
void newGame();     //done
void game ();       //done
void levelUp();     //done
void displayMap();
void bossDead();
void bossIntro();
void bossFight();
void bossTurn();
void fightSetUp();

int main () {
  //system("MODE 56,37");
  system("MODE 120,75");
  _setmode(_fileno(stdout), 0x00020000);
  newGame();
  return 0;
}

void newGame () {
  wprintf(L"\e[1;1H\e[2J");
  wprintf(L"CONFIRM:\n\ty = yes\n\tn = no\nMOVEMENT:\n\tw = up\n\ta = left\n\ts = down\n\td = right\nz = map\nc = camp\nACTIONS:\n\ta = attack\n\ti = inventory\n\tw = wait\n");
  wprintf(L"NEW GAME?\t");
  scanf(" %c",&startNewGame);
  if (startNewGame == 'n') {
    wprintf(L"GOODBYE!");
  } else if (startNewGame == 'd') {
    wprintf(L"DEV MODE!\n");
    gameNotOver = 1;
    player[0] = 7;
    player[1] = 3;
    hp = 100;
    damage = 10;
    level = 100;
    xp = 10000;
    game();
  } else {
    wprintf(L"GAME START!\n");
    gameNotOver = 1;
    player[0] = 7;
    player[1] = 3;
    hp = 100;
    damage = 10;
    level = 1;
    xp = 0;
    game();
  }
}

void game () {
  while (gameNotOver) {
    cycle();
  }
  wprintf(L"GAME OVER!\nYOU REACHED LVL %d\n",level);
  newGame();
}

void cycle () {
  display();
  move();
  display();
  fightSetUp();
}

void move () {
  playerMove = ' ';
  wprintf(L"MOVE WHERE?\t");
  scanf(" %c", &playerMove); // couldnt figure out why scanf("%c") wasnt working, apparently scanf reads the enter key as an input and so gets skipped https://stackoverflow.com/questions/29775323/scanf-function-seems-to-be-skipped-in-c#:~:text=The%20problem%20is%20because%20of,second%20call%20to%20scanf()%20.&text=So%2C%20the%20newline%20character%20is,for%20input%20for%20that%20variable.
  switch (playerMove) {
    case 'w':
      if (map[player[0]-1][player[1]] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[0] = player[0] - 1;
      }
      break;
    case 'a':
      if (map[player[0]][player[1]-1] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[1] = player[1] - 1;
      }
      break;
    case 's':
      if (map[player[0]+1][player[1]] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[0] = player[0] + 1;
      }
      break;
    case 'd':
      if (map[player[0]][player[1]+1] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[1] = player[1] + 1;
      }
      break;
    case 'c':
      wprintf(L"YOU CAMP FOR THE NIGHT\n");
      break;
    case 'z':
      wprintf(L"YOU OPEN UP YOUR MAP\n");
      displayMap();
      break;
    default:
      wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
      break;
  }
}

void display () {
  int i;
  int j;
  wprintf(L"\033[1;30m");
  wprintf(L"██████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
  for (i=player[0]-2;i<player[0]+3;i++) {
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    for (j=player[1]-2;j<player[1]+3;j++) {
      if ((i == player[0]) && (j == player[1])) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"&&");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] == 0) {
        //
      } else if (map[i][j] == -1) {
        wprintf(L"\033[0;37m");
        wprintf(L"██");
        wprintf(L"\033[0m");
      } else if (map[i][j] > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"  ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] < -3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"**");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      }
    }
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    wprintf(L"\n");
  }
  wprintf(L"\033[1;30m");
  wprintf(L"██████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
}

void displayMap () {
  int i;
  int j;
  wprintf(L"\033[1;30m");
  wprintf(L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
  for (i=0;i<63;i++) {
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    for (j=0;j<60;j++) {
      if ((i == player[0]) && (j == player[1])) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"&&");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] == 0) {
        //
      } else if (map[i][j] == -1) {
        wprintf(L"\033[0;37m");
        wprintf(L"██");
        wprintf(L"\033[0m");
      } else if (map[i][j] > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"  ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] < -3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"**");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      }
    }
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    wprintf(L"\n");
  }
  wprintf(L"\033[1;30m");
  wprintf(L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
}

void levelUp () {
  hp = hp + 10;
  damage++;
  level++;
  wprintf(L"YOU HAVE REACHED LEVEL %d\n", level);
}

void fightSetUp() {
  eHp = (map[player[0]][player[1]] * 75);
  eDamage = (map[player[0]][player[1]] * 10);
  hp = 100 + ((level-1) * 10);
  damage = 10 + ((level-1) * 1);
  if (eHp < 0) {
    eHp = eHp * -1;
    eDamage = eDamage * -1;
    bossFight();
  } else {
    fight();
  }

}

void fight () {
  wprintf(L"A LVL %d ENEMY HAS COME TO MURDER YOU!!\n", map[player[0]][player[1]]);
  while ((hp > 0) && (eHp > 0)) {
    playerTurn();
    if ((hp > 0) && (eHp > 0)) {
      enemyTurn();
    }
  }
  if (hp <= 0) {
    gameNotOver = 0;
  } else if (eHp <= 0) {
    wprintf(L"YOU WIN THE FIGHT!\n");
    xp = xp + (map[player[0]][player[1]] * 50);
    wprintf(L"%dXP GAINED\n", (map[player[0]][player[1]] * 50));
    while (xp >= level*100) {
      levelUp();
    }
  }
}

void bossFight () {
  wprintf(L"BOSS ARRIVAL!!\n");
  bossIntro();
  while ((hp > 0) && (eHp > 0)) {
    playerTurn();
    if ((hp > 0) && (eHp > 0)) {
      bossTurn();
    }
  }
  if (hp <= 0) {
    gameNotOver = 0;
  } else if (eHp <= 0) {
    wprintf(L"YOU WIN THE FIGHT!\n");
    xp = xp + (map[player[0]][player[1]] * -200);
    wprintf(L"%dXP GAINED\n", (map[player[0]][player[1]] * -200));
    while (xp >= level*100) {
      levelUp();
    }
    bossDead();
  }
}

void playerTurn () {
  wprintf(L"WHAT WILL YOU DO?\t");
  scanf(" %c",&action);
  switch (action) {
    case 'a':
      if (sword == 0) {
        wprintf(L"YOU SWING YOUR MIGHTY STICK!!\n");
        eHp = eHp - damage;
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage);
      } else if (sword == 1) {
        wprintf(L"YOU THRUST YOUR RUSTY SWORD!!\n");
        eHp = eHp - (damage + 5);
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage+5);
      } else if (sword == 2) {
        wprintf(L"YOU SLASH WITH GOBLINSLAYER!!\n");
        eHp = eHp - (damage+15);
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage+15);
      }
      if (map[player[0]][player[1]] == 1) {
        wprintf(L"THE IMP HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 2) {
        wprintf(L"THE BEEFY IMP HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 3) {
        wprintf(L"THE STRONG IMP HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 4) {
        wprintf(L"THE GUARDIAN IMP HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == -4) {
        wprintf(L"THE IMPERIAL IMP HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == -7) {
        wprintf(L"THE OMINOUS ORC HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 5) {
        wprintf(L"THE YOUNG ORC HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 6) {
        wprintf(L"THE WARRIOR ORC HAS %d HP LEFT\n",eHp);
      } else if (map[player[0]][player[1]] == 7) {
        wprintf(L"THE ASSASSIN ORC HAS %d HP LEFT\n",eHp);
      } else {
        wprintf(L"THE ENEMY HAS %d HP LEFT\n",eHp);
      }
      break;
    case 'i':
      wprintf(L"YOU DONT HAVE POCKETS!!\n");
      break;
    case 'w':
      wprintf(L"YOU WAIT FOR AN OPENING!!\n");
      break;
    default:
      wprintf(L"YOU STUMBLE AND FALL!!\n");
      break;
  }
}

void enemyTurn() {
  if (map[player[0]][player[1]] == 1) {
    wprintf(L"THE IMP FLAILS AT YOU!!\n");
  } else if (map[player[0]][player[1]] == 2) {
    wprintf(L"THE BEEFY IMP BITES YOU!!\n");
  } else if (map[player[0]][player[1]] == 3) {
    wprintf(L"THE STRONG IMP KICKS YOU!!\n");
  } else if (map[player[0]][player[1]] == 4) {
    wprintf(L"THE GUARDIAN IMP PARRIES YOU!!\n");
  } else if (map[player[0]][player[1]] == 5) {
    wprintf(L"THE YOUNG ORC PUNCHES YOU!!\n");
  } else if (map[player[0]][player[1]] == 6) {
    wprintf(L"THE WARRIOR ORC CHARGES YOU!!\n");
  } else if (map[player[0]][player[1]] == 7) {
    wprintf(L"THE ASSASSIN ORC STABS YOU!!\n");
  } else {
    wprintf(L"THE ENEMY HITS YOU!!\n");
  }
  hp = hp - eDamage;
  wprintf(L"IT DEALS %d damage!!\t\t\t\tYOU HAVE %d HP LEFT\n",eDamage,hp);
}

void bossTurn () {
  if ((player[0] == 2) && (player[1] == 4)) {
    wprintf(L"THE IMPERIAL IMP THROWS AN IMP AT YOU!!\n");
    hp = hp - eDamage;
    wprintf(L"The IMPERIAL IMP DEALS %d DAMAGE!!\t\tYOU HAVE %d HP LEFT\n",eDamage,hp);
  } else if ((player[0] == 12) && (player[1] == 4)) {
    wprintf(L"THE OMINOUS ORC LAUNCHES A PILLAR AT YOU!!\n");
    hp = hp - eDamage;
    wprintf(L"The IMPERIAL IMP DEALS %d DAMAGE!!\t\tYOU HAVE %d HP LEFT\n",eDamage,hp);
  }
}

void bossIntro () {
  if ((player[0] == 2) && (player[1] == 4)) {
    wprintf(L"MUHAHA ... FOOLISH HUMAN ... YOU HAVE ENTERED MY DOMAIN\nYOU SHALL NOW FACE THE WRATH OF THE ");
    wprintf(L"\033[0;31m");
    wprintf(L"IMPERIAL IMP!!\n");
    wprintf(L"\033[0m");
  } else if ((player[0] == 12) && (player[1] == 4)) {
    wprintf(L"SO YOU HAVE COME ... IDIOT HUMAN ... YOU HAVE ENTERED MY CASTLE\nYOU SHALL NOW FACE THE FURY OF THE ");
    wprintf(L"\033[0;31m");
    wprintf(L"OMINOUS ORC!!\n");
    wprintf(L"\033[0m");
  }
}

void bossDead() {
  if ((player[0] == 2) && (player[1] == 4)) {
    wprintf(L"NOOOOOO YOU CURSED HUMAN ... MY COUSINS WILL AVENGE ME!!\n");
    map[player[0]][player[1]] = map[player[0]][player[1]] * -1;
    wprintf(L"AS THE IMP DIES YOU NOTICE A DOOR BEHIND HIS THRONE\nINSIDE YOU FIND A RUSTY SWORD ... AT LEAST ITS BETTER THAN YOUR MIGHTY STICK\nRUSTY SWORD OBTAINED!!\n");
    sword = 1;
  } else if ((player[0] == 12) && (player[1] == 4)) {
    wprintf(L"FIRST YOU KILL MY COUSIN ... AND THEN YOU SLAY ME!!\n");
    map[player[0]][player[1]] = map[player[0]][player[1]] * -1;
    wprintf(L"AS THE ORC DIES HE DROPS HIS MASSIVE SWORD\nIT LOOKS PRETTY MEAN BUT ALSO POWERFUL\nGOBLINSLAYER OBTAINED!!\n");
    sword = 2;
  }
}
