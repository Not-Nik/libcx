// cx (c) Nikolas Wipper 2020

#include <cx.h>
#include <stdio.h>

typedef enum {
    TEST_ERROR
} ERRORS;

int_ex throws_error() {
    ERR(int_ex, TEST_ERROR)
}

int_ex fine_function() {
    OK(int_ex, 42)
}

int_ex throwing_proxy2() {
    int e = TRY(int_ex, throws_error())
    OK(int_ex, 10)
}

int_ex throwing_proxy() {
    int e = TRY(int_ex, throwing_proxy2())
    OK(int_ex, 10)
}

void exception_handler(int err) {
    if (err == TEST_ERROR)
        puts("Test error thrown");
}

int main() {
    set_handle(exception_handler);
    FIN(fine_function())
    FIN(throwing_proxy())
}
