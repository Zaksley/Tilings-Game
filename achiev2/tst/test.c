#include <stdio.h>
#include <stdlib.h>
#include "test_color.h"
#include "test_tile.h"
#include "test_rule.h"

int main()
{
    execute_test_color();
    execute_test_tile();
    execute_test_rule();
    return EXIT_SUCCESS;
}
