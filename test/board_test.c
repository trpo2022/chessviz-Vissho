#include <ctest.h>
#include <stdio.h>

#include <libchessviz/board.h>
#include <libchessviz/board_print_plain.h>
#include <libchessviz/board_read.h>
#include <libchessviz/move.h>

CTEST(read_the_move, correctly_entered_move)
{
    FILE* file = fopen("c_test.txt", "r");
    char result[6];
    fgets(result, 6, file);
    fclose(file);

    const char expected[6] = {'e', '2', '-', 'e', '4'};

    ASSERT_STR(expected, result);
}

CTEST(read_the_move, uncorrectly_entered_move)
{
    FILE* file = fopen("u_test.txt", "r");
    char result[6];
    fgets(result, 6, file);
    fclose(file);

    const char expected[6] = {'e', '2', '-', 'e', '4'};

    ASSERT_STR(expected, result);
}

CTEST(checking_rule, correct_check_of_rules)
{
    char** chess = create_chess();
    char type = '-';
    int RULE[4] = {6, 5, 4, 5}; //ход e2-e4
    int result = check_rule(chess, RULE, type);

    for (int i = 0; i < 9; i++) {
        free(chess[i]);
    }
    free(chess);

    ASSERT_FALSE(result);
}

CTEST(checking_rule, uncorrect_check_of_rules)
{
    char** chess = create_chess();
    char type = '-';
    int RULE[4] = {6, 5, 2, 5}; //ход e2-e6
    int result = check_rule(chess, RULE, type);

    for (int i = 0; i < 9; i++) {
        free(chess[i]);
    }
    free(chess);

    ASSERT_FALSE(result);
}

CTEST(creating_a_table, correct_chess_table)
{
    char** chess = create_chess();

    ASSERT_NOT_NULL(chess);

    for (int i = 0; i < 9; i++) {
        free(chess[i]);
    }
    free(chess);
}
