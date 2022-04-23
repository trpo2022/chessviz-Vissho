#include <libchessviz/board_read.h>
#include <libchessviz/board.h>
#include <libchessviz/board_print_plain.h>
#include <libchessviz/move.h>

int main()
{
    int i, flag = 1;
    char** chess;
    char step[30];

    chess = create_chess();
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
