#include "array.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"

ARRAY(uint32_t);

int main() {
    static const TestGroup TEST_GROUPS[] = {
        TEST_GROUP(ARRAY_TEST_GROUP),
    };

    for (size_t i = 0; i < ARRAY_LENGTH(TEST_GROUPS); i++) {
        TestGroup tg = TEST_GROUPS[i];
        for (size_t j = 0; j < tg.len; j++) {
            Test t = tg.ptr[j];

            printf("TEST: %s...", t.name);
            printf("%s\n", tg.ptr[j].test() ? "ok" : "failed");
        }
    }

    return 0;
}
