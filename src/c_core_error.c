#include "c_core_error.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

_Noreturn void out_of_bounds() {
    printf("\nERROR: out of bounds\n");
    fflush(stdin);

    raise(SIGTRAP);

    while (1);
}

_Noreturn void malloc_error() {
    printf("\nERROR: allocation error\n");
    fflush(stdin);

    exit(1);
}
