#include <ctest.h>
#include <stdio.h>

#include <chessviz/board_read.h>
#include <libchessviz/move.h>
#include <libchessviz/board.h>
#include <libchessviz/board_print_plain.h>

CTEST(read_txt, simple_read_file)
{
    FILE* file = fopen("test.txt", "r");
    char result[6];
    fgets(result, 6, file);
    fclose(file);

    const char expected[6] = {'e', '2', '-', 'e', '4'};

    ASSERT_STR(result, expected);
}
