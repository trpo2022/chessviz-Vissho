// #include <ctype.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "../libchessviz/chessviz.h"

int main()
{
    int i, flag = 1;
    char** chess;
    char step[30];
    chess = (char**)malloc(FIELD * sizeof(char*));
    for (i = 0; i < FIELD; i++) {
        chess[i] = (char*)malloc(FIELD * sizeof(char));
    }

    create_chess(chess);
    print_chess(chess);

    do {
        scanf("%s", step);
        step_chess(chess, step, flag);
        print_chess(chess);
        flag = flag * (-1);
    } while (check_king(step, flag) == 0);

    for (i = 0; i < FIELD; i++) {
        free(chess[i]);
    }
    free(chess);

    return 0;
}
