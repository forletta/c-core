#include "array.h"
#include "ascii_string.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"

// #define TEST(test_) {.name = #test_, .test = test_}
// #define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
//
// #define ASSERT_EQ(rhs, lhs)                                                    \
//     if (rhs != lhs)                                                            \
//         return false;
// #define ASSERT_NE(rhs, lhs)                                                    \
//     if (rhs == lhs)                                                            \
//         return false;
//
// typedef struct {
//     char *name;
//     bool (*test)(void);
// } Test;
//
// bool test_AsciiStr_copy() {
//     AsciiStr str = {
//         .ptr = "hello",
//         .len = 5,
//     };
//
//     AsciiStr new = AsciiStr_copy(&str);
//
//     ASSERT_NE(str.ptr, new.ptr);
//     ASSERT_EQ(str.len, new.len);
//     ASSERT_EQ(strncmp(str.ptr, new.ptr, 5), 0);
//
//     return true;
// }
//
// bool test_AsciiStr_copy_from_cstr() {
//     char *cstr = "hello";
//
//     AsciiStr str = AsciiStr_copy_from_cstr(cstr);
//
//     ASSERT_NE(str.ptr, cstr);
//     ASSERT_EQ(strncmp(str.ptr, cstr, str.len), 0);
//
//     return true;
// }
//
// bool test_AsciiStr_take_from_cstr() {
//     char *cstr = "hello";
//
//     AsciiStr str = AsciiStr_take_from_cstr(cstr);
//
//     ASSERT_EQ(str.ptr, cstr);
//     ASSERT_EQ(strncmp(str.ptr, cstr, 5), 0);
//
//     return true;
// }
//
// bool test_AsciiStr_get() {
//     AsciiStr str = {
//         .ptr = "hello",
//         .len = 5,
//     };
//
//     ASSERT_EQ(*AsciiStr_get(&str, 0), 'h');
//     ASSERT_EQ(*AsciiStr_get(&str, 1), 'e');
//     ASSERT_EQ(*AsciiStr_get(&str, 4), 'o');
//
//     return true;
// }
//
// bool test_AsciiStr_substr() {
//     AsciiStr str = {
//         .ptr = "hello",
//         .len = 5,
//     };
//
//     AsciiStr substr = AsciiStr_substr(&str, 1, 3);
//     ASSERT_EQ(substr.len, 2);
//     ASSERT_EQ(strncmp(substr.ptr, "el", 2), 0);
//
//     substr = AsciiStr_substr(&str, 0, 2);
//     ASSERT_EQ(substr.len, 2);
//     ASSERT_EQ(strncmp(substr.ptr, "he", 2), 0);
//
//     substr = AsciiStr_substr(&str, 3, 5);
//     ASSERT_EQ(substr.len, 2);
//     ASSERT_EQ(strncmp(substr.ptr, "lo", 2), 0);
//
//     substr = AsciiStr_substr(&str, 0, 5);
//     ASSERT_EQ(substr.len, 5);
//     ASSERT_EQ(strncmp(substr.ptr, "hello", 5), 0);
//
//     return true;
// }
//
// bool test_AsciiString_take_from_str() {
//     char *cstr = "hello";
//     char *ptr = malloc(5);
//     strncpy(ptr, cstr, 5);
//
//     AsciiStr str = {
//         .ptr = ptr,
//         .len = 5,
//     };
//
//     AsciiString string = AsciiString_take_from_str(str);
//
//     ASSERT_EQ(str.ptr, string.ptr);
//     ASSERT_EQ(str.len, string.len);
//     ASSERT_EQ(strncmp(str.ptr, string.ptr, 5), 0);
//
//     AsciiString_free(&string);
//
//     return true;
// }
//
// bool test_AsciiString_copy_from_str() {
//     AsciiStr str = {
//         .ptr = "hello",
//         .len = 5,
//     };
//
//     AsciiString string = AsciiString_copy_from_str(&str);
//
//     ASSERT_NE(str.ptr, string.ptr);
//     ASSERT_EQ(str.len, string.len);
//     ASSERT_EQ(strncmp(str.ptr, string.ptr, 5), 0);
//
//     return true;
// }
//
// bool test_AsciiString_take_from_cstr() {
//     char *cstr = malloc(5);
//
//     strncpy(cstr, "hello", 5);
//
//     AsciiString string = AsciiString_take_from_cstr(cstr);
//
//     ASSERT_EQ(cstr, string.ptr);
//     ASSERT_EQ(5, string.len);
//     ASSERT_EQ(strncmp(cstr, string.ptr, 5), 0);
//
//     AsciiString_free(&string);
//
//     return true;
// }
//
// bool test_AsciiString_copy_from_cstr() {
//     char *cstr = "hello";
//
//     AsciiString string = AsciiString_copy_from_cstr(cstr);
//
//     ASSERT_NE(cstr, string.ptr);
//     ASSERT_EQ(strlen(cstr), string.len);
//     ASSERT_EQ(strncmp(cstr, string.ptr, 5), 0);
//
//     AsciiString_free(&string);
//
//     return true;
// }
//
// bool test_AsciiString_get() {
//     AsciiString string = AsciiString_copy_from_cstr("hello");
//
//     ASSERT_EQ(*AsciiString_get(&string, 0), 'h');
//     ASSERT_EQ(*AsciiString_get(&string, 1), 'e');
//     ASSERT_EQ(*AsciiString_get(&string, 4), 'o');
//
//     AsciiString_free(&string);
//
//     return true;
// }
//
// bool test_AsciiString_push() {
//     AsciiString string = AsciiString_copy_from_cstr("hello");
//
//     AsciiString_push(&string, ' ');
//
//     ASSERT_EQ(strncmp(string.ptr, "hello ", 6), 0);
//     ASSERT_EQ(string.len, 6);
//
//     return true;
// }

ARRAY(uint32_t);

int main() {
    // static const Test TESTS[] = {
    //     TEST(test_AsciiStr_copy_from_cstr),
    //     TEST(test_AsciiStr_copy),
    //     TEST(test_AsciiStr_take_from_cstr),
    //     TEST(test_AsciiStr_get),
    //     TEST(test_AsciiStr_substr),
    //     TEST(test_AsciiString_take_from_str),
    //     TEST(test_AsciiString_copy_from_str),
    //     TEST(test_AsciiString_take_from_cstr),
    //     TEST(test_AsciiString_copy_from_cstr),
    //     TEST(test_AsciiString_get),
    //     TEST(test_AsciiString_push),
    // };
    //
    // for (size_t i = 0; i < ARRAY_LENGTH(TESTS); i++) {
    //     printf("TEST: %s...", TESTS[i].name);
    //     printf("%s\n", TESTS[i].test() ? "ok" : "failed");
    // }

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
