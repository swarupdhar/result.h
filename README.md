# result.h

A result type implementation using C macro.

## Why?

Just because we can. Don't see why anyone would want this or would like to code
in C in this way. This is more of an intellectual exercise in C macro system.
If this is of use to you or you find it cool then great!

## Example

```c
#include <stdio.h>
#include "result.h"

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
    printf("%d\n", a); // here a is 0 as it was zero initialized

    if_let(int, b, int_divide(5, 0), {
        printf("%s\n", $);
        b = -1;
    });
    printf("%d\n", b);

    return 0;
}
```

## Usage

Just import the header, that's it. All result types must be declared before
use. When using `unwrap`, the result's value is exposed in the block using the
`$` variable name. Similarly, in `if_let` block, the error value is exposed as
`$`.
