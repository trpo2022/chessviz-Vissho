#include <libchessviz/board.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define coord_for_black_pawn  1 
#define coord_for_white_pawn  6 

int check_rule(char** chess, int* rule, char type)
{
    int flag = 0, i;
    char c = chess[rule[0]][rule[1]];
    // rule[1] and rule[3] - буквы, rule[0] and rule[2] - цифры
    // printf("%d %d %d %d\n", rule[1], rule[0], rule[3], rule[2]);
    if ((c == 'P' || c == 'p') && type == '-') {
        if (rule[1] != rule[3]) {
            flag++;
        }
        if (c == 'P') {
            if (rule[0] == coord_for_white_pawn && (rule[0] - rule[2]) != 2
                && (rule[0] - rule[2]) != 1) {
                flag++;
            } else if ((rule[0] - rule[2]) != 1 && rule[0] != coord_for_white_pawn) {
                flag++;
            }
        }
        if (c == 'p') {
            if (rule[0] == coord_for_black_pawn && (rule[2] - rule[0]) != 2
                && (rule[2] - rule[0]) != 1) {
                flag++;
            } else if ((rule[2] - rule[0]) != 1 && rule[0] != coord_for_black_pawn) {
                flag++;
            }
        }
    } else if ((c == 'P' || c == 'p') && type == 'x') {
        if (c == 'P') {
            if (rule[0] - rule[2] != 1
                || (rule[1] - rule[3] != 1 && rule[3] - rule[1] != 1)) {
                flag++;
            }
        }
        if (c == 'p') {
            if (rule[2] - rule[0] != 1
                || (rule[1] - rule[3] != 1 && rule[3] - rule[1] != 1)) {
                flag++;
            }
        }
    }
    if (c == 'R' || c == 'r') {
        if (rule[0] != rule[2]) {
            if (rule[0] > rule[2]) {
                for (i = rule[2] + 1; i < rule[0]; i++) {
                    if (chess[i][rule[1]] != ' ') {
                        flag++;
                        break;
                    }
                }
            } else {
                for (i = rule[0] + 1; i < rule[2]; i++) {
                    if (chess[i][rule[1]] != ' ') {
                        flag++;
                        break;
                    }
                }
            }
        } else if (rule[1] != rule[3]) {
            if (rule[1] > rule[3]) {
                for (i = rule[3] + 1; i < rule[1]; i++) {
                    if (chess[rule[0]][i] != ' ') {
                        flag++;
                        break;
                    }
                }
            } else {
                for (i = rule[1] + 1; i < rule[3]; i++) {
                    if (chess[rule[0]][i] != ' ') {
                        flag++;
                        break;
                    }
                }
            }
        }
        if (rule[1] != rule[3] && rule[0] != rule[2]) {
            flag++;
        }
    }
    if (c == 'N' || c == 'n') {
        int x, y;
        x = abs(rule[1] - rule[3]);
        y = abs(rule[0] - rule[2]);
        printf("%d-%d\n", x, y);
        if ((x != 2 || y != 1) && (x != 1 || y != 2)) {
            flag++;
        }
    }
    if (c == 'B' || c == 'b') {
        int x = rule[3] - rule[1], y = rule[2] - rule[0];
        int j;
        if (x > 0 && y > 0) {
            j = rule[0] + 1;
            for (i = rule[1] + 1; i < rule[3]; i++) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j++;
            }
        } else if (x > 0 && y < 0) {
            j = rule[0] - 1;
            for (i = rule[1] + 1; i < rule[3]; i++) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j--;
            }
        } else if (x < 0 && y < 0) {
            j = rule[0] - 1;
            for (i = rule[1] - 1; i > rule[3]; i--) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j--;
            }
        } else if (x < 0 && y > 0) {
            j = rule[0] + 1;
            for (i = rule[1] - 1; i > rule[3]; i--) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j++;
            }
        }
        if (rule[1] - rule[3] != rule[0] - rule[2]
            && rule[1] - rule[3] != rule[2] - rule[0]) {
            flag++;
        }
    }
    if ((c == 'k' || c == 'K') && type == '-') {
        if (rule[1] - rule[3] > 1 || rule[3] - rule[1] > 1
            || rule[0] - rule[2] > 1 || rule[2] - rule[0] > 1) {
            flag++;
        }
    }
    if (c == 'q' || c == 'Q') {
        int x, y;
        x = abs(rule[1] - rule[3]);
        y = abs(rule[0] - rule[2]);
        if ((x == 2 && y == 1) || (x == 1 && y == 2)) {
            flag++;
        }
        x = rule[3] - rule[1];
        y = rule[2] - rule[0];
        int j, i;
        if (x > 0 && y > 0) {
            j = rule[0] + 1;
            for (i = rule[1] + 1; i < rule[3]; i++) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j++;
            }
        } else if (x > 0 && y < 0) {
            j = rule[0] - 1;
            for (i = rule[1] + 1; i < rule[3]; i++) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j--;
            }
        } else if (x < 0 && y < 0) {
            j = rule[0] - 1;
            for (i = rule[1] - 1; i > rule[3]; i--) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j--;
            }
        } else if (x < 0 && y > 0) {
            j = rule[0] + 1;
            for (i = rule[1] - 1; i > rule[3]; i--) {
                if (chess[j][i] != ' ') {
                    flag++;
                    break;
                }
                j++;
            }
        }
        if (rule[0] == rule[2] || rule[1] == rule[3]) {
            if (rule[0] != rule[2]) {
                if (rule[0] > rule[2]) {
                    for (i = rule[2] + 1; i < rule[0]; i++) {
                        if (chess[i][rule[1]] != ' ') {
                            flag++;
                            break;
                        }
                    }
                } else {
                    for (i = rule[0] + 1; i < rule[2]; i++) {
                        if (chess[i][rule[1]] != ' ') {
                            flag++;
                            break;
                        }
                    }
                }
            } else if (rule[1] != rule[3]) {
                if (rule[1] > rule[3]) {
                    for (i = rule[3] + 1; i < rule[1]; i++) {
                        if (chess[rule[0]][i] != ' ') {
                            flag++;
                            break;
                        }
                    }
                } else {
                    for (i = rule[1] + 1; i < rule[3]; i++) {
                        if (chess[rule[0]][i] != ' ') {
                            flag++;
                            break;
                        }
                    }
                }
            }
        }
        x = abs(rule[1] - rule[3]);
        y = abs(rule[0] - rule[2]);
        if (x != 0 && y != 0 && x != y) {
            flag++;
        }
    }

    return flag;
}

int check_king(char* step, int flag)
{
    long int x = strlen(step);
    char end1;
    if (x >= 7) {
        end1 = step[6];
    }

    int flag1 = 0;

    if (end1 == '+') {
        if (flag == 1) {
            printf("Шах королю белых!\n");
        } else if (flag == -1) {
            printf("Шах королю чёрных!\n");
        }
    } else if (end1 == '#') {
        if (flag == 1) {
            printf("Шах и мат королю белых!\n");
        } else if (flag == -1) {
            printf("Шах и мат королю чёрных!\n");
        }
        flag1++; 
    }

    return flag1;
}
