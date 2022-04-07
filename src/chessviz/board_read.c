#include <chessviz/board_read.h>
#include <stdlib.h>

#define FIELD  9 
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

char** create_chess()
{
    int i, j;
    char** chess;
    chess = (char**)malloc(FIELD * sizeof(char*));
    for (i = 0; i < FIELD; i++) {
        chess[i] = (char*)malloc(FIELD * sizeof(char));
    }
    char x = 97, z = 56;
    for (i = 0; i < FIELD; i++) {
        for (j = 0; j < FIELD; j++) {
            if (j == column_for_numbers) {
                chess[i][j] = z;
                z--;
            } else if (i == column_for_letters) {
                chess[i][j] = x;
                x++;
            } else if (i == coord_for_black_pawn && j > beginning_of_the_line) {
                chess[i][j] = 'p';
            } else if (i == coord_for_white_pawn && j > beginning_of_the_line) {
                chess[i][j] = 'P';
            } else if (
                    i == coord_for_black
                    && (j == coord_for_left_rook
                        || j == coord_for_right_rook)) {
                chess[i][j] = 'r';
            } else if (
                    i == coord_for_black
                    && (j == coord_for_left_kNight
                        || j == coord_for_right_kNight)) {
                chess[i][j] = 'n';
            } else if (
                    i == coord_for_black
                    && (j == coord_for_left_bishop
                        || j == coord_for_right_bishop)) {
                chess[i][j] = 'b';
            } else if (i == coord_for_black && j == coord_for_queen) {
                chess[i][j] = 'q';
            } else if (i == coord_for_black && j == coord_for_king) {
                chess[i][j] = 'k';
            } else if (
                    i == coord_for_white
                    && (j == coord_for_left_rook
                        || j == coord_for_right_rook)) {
                chess[i][j] = 'R';
            } else if (
                    i == coord_for_white
                    && (j == coord_for_left_kNight
                        || j == coord_for_right_kNight)) {
                chess[i][j] = 'N';
            } else if (
                    i == coord_for_white
                    && (j == coord_for_left_bishop
                        || j == coord_for_right_bishop)) {
                chess[i][j] = 'B';
            } else if (i == coord_for_white && j == coord_for_queen) {
                chess[i][j] = 'Q';
            } else if (i == coord_for_white && j == coord_for_king) {
                chess[i][j] = 'K';
            } else {
                chess[i][j] = ' ';
            }
        }
    }
    chess[column_for_letters][column_for_numbers] = ' ';
    return chess;
}

void free_and_exit(char** chess)
{
    int i;
    for (i = 0; i < FIELD; i++) {
        free(chess[i]);
    }
    free(chess);
    exit(-1);
}
