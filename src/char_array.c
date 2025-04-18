#include "char_array.h"
#include <stdlib.h>

void charArray_free(charArray *str) {
    free(str->ptr);

    str->ptr = NULL;
    str->len = 0;
    str->cap = 0;
}

ARRAY_IMPL(char);
