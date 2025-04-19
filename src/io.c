#include "io.h"
#include <stddef.h>

ssize_t io_getline(charArray *str, FILE *restrict stream) {
    ssize_t bytes_read = getline(&str->ptr, &str->cap, stream);

    if (bytes_read > 0)
        // excludes null terminator
        str->len = bytes_read - 1;

    if (bytes_read < 0)
        charArray_free(str);

    return bytes_read;
}
