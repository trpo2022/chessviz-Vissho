#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define coordinates 4

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
    chess[8][0] = ' ';
}

int checkrule(char** chess, int* rule)
{
    int flag = 0;
    char c = chess[rule[0]][rule[1]];
    // rule[1] and rule[3] - буквы, rule[0] and rule[2] - цифры
    printf("%d %d %d %d\n", rule[1], rule[0], rule[3], rule[2]);
    if (c == 'P' || c == 'p') {
        if (rule[1] != rule[3]) {
            flag++;
        }
        if (c == 'P') {
            if (rule[0] == 6 && (rule[0] - rule[2]) != 2
                && (rule[0] - rule[2]) != 1) {
                flag++;
            } else if ((rule[0] - rule[2]) != 1 && rule[0] != 6) {
                flag++;
            }
        }
        if (c == 'p') {
            if (rule[0] == 1 && (rule[2] - rule[0]) != 2
                && (rule[2] - rule[0]) != 1) {
                flag++;
            } else if ((rule[2] - rule[0]) != 1 && rule[0] != 1) {
                flag++;
            }
        }
    }
    if (c == 'R' || c == 'r') {
        if (rule[1] != rule[3] && rule[0] != rule[2]) {
            flag++;
        }
    }
    if (c == 'N' || c == 'n') {
        if (rule[1] - rule[3] == 1 || rule[1] - rule[3] == -1) {
            if (rule[0] - rule[2] != 2 && rule[0] - rule[2] != -2) {
                flag++;
            }
        } else if (rule[0] - rule[2] == 1 || rule[0] - rule[2] == -1) {
            if (rule[1] - rule[3] != 2 && rule[1] - rule[3] != -2) {
                flag++;
            }
        }
    }
    if (c == 'B' || c == 'b') {
        if (rule[1] - rule[3] != rule[0] - rule[2]
            && rule[1] - rule[3] != rule[2] - rule[0]) {
            flag++;
        }
    }
    if (c == 'k' || c == 'K') {
        if (rule[1] - rule[3] > 1 || rule[3] - rule[1] > 1
            || rule[0] - rule[2] > 1 || rule[2] - rule[0] > 1) {
            flag++;
        }
    }

    return flag;
}

void stepchess(char** chess, char* step)
{
    long int x = strlen(step);
    int stepF1, stepF2, stepS1, stepS2;
    char type, figure, end1, end2, end3, end4;
    if (x == 5) {
        stepF1 = step[0];
        stepF2 = step[1];
        type = step[2];
        stepS1 = step[3];
        stepS2 = step[4];
    } else if (x == 6) {
        figure = step[0];
        stepF1 = step[1];
        stepF2 = step[2];
        type = step[3];
        stepS1 = step[4];
        stepS2 = step[5];
    } else if (x >= 7) {
        figure = step[0];
        stepF1 = step[1];
        stepF2 = step[2];
        type = step[3];
        stepS1 = step[4];
        stepS2 = step[5];
        end1 = step[6];
        end2 = step[7];
        end3 = step[8];
        end4 = step[9];
    }

    stepF1 -= 96; // Преобразовываем ход в рабочие данные
    stepF2 -= 56;
    stepS1 -= 96;
    stepS2 -= 56;
    stepF2 *= (-1);
    stepS2 *= (-1);

    // printf("%d %d %d %d\n", stepF1, stepF2, stepS1, stepS2);

    if (x < 5 || x > 10) {
        printf("Вы ввели некорректный ход!\n");
        exit(-1);
    } else if (
            stepF2 > 7 || stepF2 < 0 || stepS2 > 7 || stepS2 < 0 || stepF1 > 8
            || stepF1 < 1 || stepS1 > 8 || stepS1 < 1) {
        printf("Вы вышли за пределы поля!\n");
        exit(-1);
    } else if (figure != toupper(chess[stepF2][stepF1]) && x == 6) {
        if (chess[stepF2][stepF1] == ' ') {
            printf("На этом месте нет фигуру!\n");
        } else {
            printf("Вы берете не ту фигуру!\n");
        }
        exit(-1);
    } else if (chess[stepF2][stepF1] == ' ') {
        printf("На этом месте нет фигуру!\n");
        exit(-1);
    } else if (
            (type == '-' && chess[stepS2][stepS1] != ' ')
            || (type == 'x' && chess[stepS2][stepS1] == ' ')
            || (type != '-' && type != 'x')) {
        printf("Вы используете некорректный тип хода!\n");
        exit(-1);
    } else if (
            x >= 7
            && (end1 != '+' && end1 != '#'
                && (end1 != 'e' || end2 != '.' || end3 != 'p'
                    || end4 != '.'))) {
        printf("Вы используете некорректный тип хода!!\n");
        exit(-1);
    }

    int RULE[coordinates] = {stepF2, stepF1, stepS2, stepS1};
    if (checkrule(chess, RULE) != 0) {
        printf("Вы неправильно походили фигурой!\n");
        exit(-1);
    }

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

int checkking(char** chess)
{
    int i, flag = 0;
    for (i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (chess[i][j] == 'k' || chess[i][j] == 'K') {
                flag++;
            }
        }
    }
    return flag;
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

    while (checkking(chess) == 2) {
        scanf("%s", step);
        stepchess(chess, step);
        printchess(chess);
    }

    for (i = 0; i < 9; i++) {
        free(chess[i]);
    }
    free(chess);
    return 0;
}
