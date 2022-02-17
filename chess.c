#include <stdio.h>
#include <stdlib.h>

void createchess(char** chess)
{
    int i, j;
    char x = 96, z = 56;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (j == 0 && z != 48) {
                chess[i][j] = z;
                z--;
            } else if (i == 8) {
                chess[i][j] = x;
                x++;
            } else if (i == 1 && j > 0) {
                chess[i][j] = 'p';
            } else if (i == 6 && j > 0) {
                chess[i][j] = 'P';
            } else if (i == 0 && (j == 1 || j == 8)) {
                chess[i][j] = 'r';
            } else if (i == 0 && (j == 2 || j == 7)) {
                chess[i][j] = 'n';
            } else if (i == 0 && (j == 3 || j == 6)) {
                chess[i][j] = 'b';
            } else if (i == 0 && j == 4) {
                chess[i][j] = 'q';
            } else if (i == 0 && j == 5) {
                chess[i][j] = 'k';
            } else if (i == 7 && (j == 1 || j == 8)) {
                chess[i][j] = 'R';
            } else if (i == 7 && (j == 2 || j == 7)) {
                chess[i][j] = 'N';
            } else if (i == 7 && (j == 3 || j == 6)) {
                chess[i][j] = 'B';
            } else if (i == 7 && j == 4) {
                chess[i][j] = 'Q';
            } else if (i == 7 && j == 5) {
                chess[i][j] = 'K';
            } else {
                chess[i][j] = ' ';
            }
        }
    }
}

void stepchess(char** chess, char* step)
{
    int stepF1 = step[0], stepF2 = step[1], stepS1 = step[3], stepS2 = step[4];
    stepF1 -= 96;
    stepF2 -= 56;
    stepS1 -= 96;
    stepS2 -= 56;
    stepF2 *= (-1);
    stepS2 *= (-1);
    chess[stepS2][stepS1] = chess[stepF2][stepF1];
    chess[stepF2][stepF1] = ' ';
}

void printchess(char** chess)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", chess[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i;
    char** chess;
    char step[30];
    chess = (char**)malloc(9 * sizeof(char*));
    for (i = 0; i < 9; i++) {
        chess[i] = (char*)malloc(9 * sizeof(char));
    }

    createchess(chess);
    printchess(chess);

    scanf("%s", step);
    stepchess(chess, step);
    printchess(chess);

    for (i = 0; i < 9; i++) {
        free(chess[i]);
    }
    free(chess);
    return 0;
}
