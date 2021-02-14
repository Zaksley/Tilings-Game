#include <stdio.h>
#include <stdlib.h>
#include "test_color.h"
#include "test_tile.h"
#include "test_rule.h"
#include "outils.h"

int main()
{
    text_white();
    printf("*** Debut des tests ***\n");
    printf("\n");
    int error_color = execute_test_color();
    int error_tile = execute_test_tile();
    int error_rule = execute_test_rule();

    display_error(error_color, "de color");
    display_error(error_tile, "de tile");
    display_error(error_rule, "de rule");
    display_error(error_tile + error_rule + error_color, "");

    text_white();
    printf("\n");
    printf("*** Fin des tests ***\n");
    return EXIT_SUCCESS;
}
