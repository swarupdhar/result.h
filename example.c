#include "result.h"
#include <stdio.h>

DECLARE_RESULT_TYPE(int);


Result(int) int_divide(int a, int b) {
    if (b == 0) {
        return Fail(int, "Division by zero error");
    }

    return Success(int, a / b);
}


int main() {

    unwrap(int, int_divide(5, 1), {
        printf("%d\n", $);
    });

    if_let(int, a, int_divide(5, 0), {
        printf("%s\n", $);
    });
    printf("%d\n", a);

    if_let(int, b, int_divide(5, 0), {
        printf("%s\n", $);
        b = 0;
    });

    printf("%d\n", b);

    return 0;
}



