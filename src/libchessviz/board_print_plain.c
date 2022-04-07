#include <libchessviz/board_print_plain.h>
#include <stdio.h>

#define FIELD 9

void print_chess(char** chess)
{
    for (int i = 0; i < FIELD; i++) {
        for (int j = 0; j < FIELD; j++) {
            printf("%c ", chess[i][j]);
        }
        printf("\n");
    }
}
