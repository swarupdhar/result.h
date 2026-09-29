/**
 * Copyright 2026 Swarup Dhar.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define XSTR(x) #x
#define STR(x) XSTR(x)

#ifndef ERROR_TYPE
#   define ERROR_TYPE char*
#endif

typedef ERROR_TYPE error_t;

#define Result(T) result_##T##_t

#define DECLARE_RESULT_TYPE(T)                                                 \
    typedef struct result_##T {                                                \
        bool is_valid;                                                         \
        union {                                                                \
            T value;                                                           \
            error_t error;                                                     \
        };                                                                     \
    } Result(T)

#define Success(T, val) (Result(T)) { .is_valid = true, .value = (val) }
#define Fail(T, err) (Result(T)) { .is_valid = false, .error = err }

#define unwrap(T, result, ...)                                                 \
    do {                                                                       \
        Result(T) $res = (result);                                             \
        if ($res.is_valid) {                                                   \
            T $ = $res.value;                                                  \
            __VA_ARGS__                                                        \
        } else {                                                               \
            printf("%s in " STR(__FILE__)":" STR(__LINE__) "\n", $res.error);  \
            exit(1);                                                           \
        }                                                                      \
    } while(0)

#define if_let(T, var, x, ...)                                                 \
    T var = { 0 };                                                             \
    do {                                                                       \
        Result(T) result = (x);                                                \
        if(!result.is_valid) {                                                 \
            error_t $ = result.error;                                          \
            __VA_ARGS__                                                        \
        }                                                                      \
        else {                                                                 \
            var = result.value;                                                \
        }                                                                      \
    } while(0);

