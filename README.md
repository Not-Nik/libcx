# About
This repo contains two similar versions of the same library.
cx is another attempt to bring exceptions to C.

# Comparing
|aspect|cx | cx2 |
|------|---|-----|
|Required standard library functions|`puts`, `printf`|`puts`, `printf`, `setjmp`, `longjmp`|
|Special return type|Yes|No|
|Thread safe|Somewhat|Definitely no|
|Custom errors|Yes|Yes|
|User defined error handler|Yes|Yes|
|Trace back after exception|Yes|Yes|
|Signal handling|No|Yes|
|TRY/FIN signature|(\<struct with .ex and .val\>) -> value of struct|(\<any code block\>) -> no return|

# cx
Lightweight version of cx.

### Minimal example
```c
#include <cx.h>
#include <stdio.h>

void exception_handler(int err) {
    puts("Error");
}

int_ex error_function() {
    ERR(int_ex, 0);
    return OK(int_ex, 2);
}

int main() {
    set_handle(exception_handler);
    int i = FIN(error_function());
}
```

# cx2
Fancy-pants version of cx.

### Minimal example
```c
#include <cx2.h>
#include <stdio.h>

void exception_handler(int err) {
    puts("Error");
}

int error_function() {
    ERR(0);
    return 2; // Not executed
}

int main() {
    set_handle(exception_handler);
    FIN(int i = error_function())
}
```
