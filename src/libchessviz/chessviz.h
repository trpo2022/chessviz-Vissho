#ifndef _CHESSVIZ_
#define _CHESSVIZ_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define COORDINATES 4
#define FIELD 9
#define column_for_numbers  0 
#define column_for_letters  8
#define coord_for_black  0 
#define coord_for_white  7
#define coord_for_left_rook  1 
#define coord_for_right_rook  8
#define coord_for_left_kNight  2 
#define coord_for_right_kNight  7
#define coord_for_left_bishop  3 
#define coord_for_right_bishop  6
#define coord_for_queen  4 
#define coord_for_king  5
#define coord_for_black_pawn  1 
#define coord_for_white_pawn  6 
#define beginning_of_the_line  0

void create_chess(char** chess);
int check_rule(char** chess, int* rule, char type);
void free_and_exit(char** chess);
void step_chess(char** chess, char* step, int flag);
void print_chess(char** chess);
int check_king(char* step, int flag);

#endif // _CHESSVIZ_
