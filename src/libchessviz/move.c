#include <libchessviz/move.h>
#include <libchessviz/board.h>
#include <chessviz/board_read.h>

#define COORDINATES 4

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
