// cx (c) Nikolas Wipper 2020

#include <cx2.h>
#include <stdio.h>

typedef enum {
    TEST_ERROR,
    ANOTHER_ERROR
} ERRORS;

int throws_error() {
    ERR(TEST_ERROR)
}

int throwing_proxy() {
    TRY(return throws_error())
}

int throwing_proxy2() {
    TRY(return throwing_proxy())
}

void handler(int err) {
    if (err == TEST_ERROR)
        puts("Test error thrown");
    if (err == ANOTHER_ERROR)
        puts("Another error thrown");
    if (err == SEGMENTATION_VIOLATION)
        puts("Segmentation vault");
    printf("Error code: %i", err);
}

int main() {
    set_handle(handler);
    char * o = 0;
    FIN(char p = *o)
    FIN(int i = throwing_proxy2())
}
