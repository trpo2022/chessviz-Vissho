#include "chessviz.h"

void create_chess(char** chess)
{
    int i, j;
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
}

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

void free_and_exit(char** chess)
{
    int i;
    for (i = 0; i < FIELD; i++) {
        free(chess[i]);
    }
    free(chess);
    exit(-1);
}

void step_chess(char** chess, char* step, int flag)
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
    const int left_border = 1, right_border = 8;
    const int up_border = 0, down_border = 7;

    if (x < 5 || x > 10) {
        printf("Вы ввели некорректный ход!\n");
        free_and_exit(chess);
    } else if (
            stepF2 > down_border || stepF2 < up_border || stepS2 > down_border || stepS2 < up_border || stepF1 > right_border
            || stepF1 < left_border || stepS1 > right_border || stepS1 < left_border) {
        printf("Вы вышли за пределы поля!\n");
        free_and_exit(chess);
        ;
    } else if (figure != toupper(chess[stepF2][stepF1]) && x == 6) {
        if (chess[stepF2][stepF1] == ' ') {
            printf("На этом месте нет фигуру!\n");
            free_and_exit(chess);
        } else {
            printf("Вы берете не ту фигуру!\n");
            free_and_exit(chess);
        }
    } else if (chess[stepF2][stepF1] == ' ') {
        printf("На этом месте нет фигуру!\n");
        free_and_exit(chess);
    } else if (stepF1 == stepS1 && stepF2 == stepS2) {
        printf("Вы не можете ходить на месте!\n");
        free_and_exit(chess);
    } else if (
            (type == '-' && chess[stepS2][stepS1] != ' ')
            || (type == 'x' && chess[stepS2][stepS1] == ' ')
            || (type != '-' && type != 'x')) {
        printf("Вы используете некорректный тип хода!\n");
        free_and_exit(chess);
    } else if (
            x >= 7
            && (end1 != '+' && end1 != '#'
                && (end1 != 'e' || end2 != '.' || end3 != 'p'
                    || end4 != '.'))) {
        printf("Вы используете некорректный тип хода!!\n");
        free_and_exit(chess);
    } else if (type == 'x') {
        if (isupper(chess[stepF2][stepF1]) != 0) {
            if (isupper(chess[stepS2][stepS1]) != 0) {
                printf("Нельзя рубить одинаковые по цвету фигуры!\n");
                free_and_exit(chess);
            }
        } else if (islower(chess[stepF2][stepF1]) != 0) {
            if (islower(chess[stepS2][stepS1]) != 0) {
                printf("Нельзя рубить одинаковые по цвету фигуры!\n");
                free_and_exit(chess);
            }
        }
    } else if (flag == 1 && islower(chess[stepF2][stepF1])) {
        printf("Вы ходите не по очерёдности!\n");
        free_and_exit(chess);
    } else if (flag == -1 && isupper(chess[stepF2][stepF1])) {
        printf("Вы ходите не по очерёдности!\n");
        free_and_exit(chess);
    }

    int RULE[COORDINATES] = {stepF2, stepF1, stepS2, stepS1};
    if (check_rule(chess, RULE, type) != 0) {
        printf("Вы неправильно походили фигурой!\n");
        free_and_exit(chess);
    }

    chess[stepS2][stepS1] = chess[stepF2][stepF1];
    chess[stepF2][stepF1] = ' ';
}

void print_chess(char** chess)
{
    for (int i = 0; i < FIELD; i++) {
        for (int j = 0; j < FIELD; j++) {
            printf("%c ", chess[i][j]);
        }
        printf("\n");
    }
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
