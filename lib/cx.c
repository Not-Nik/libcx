#include "cx.h"

#include <stdio.h>

static int error_code = -1;
static int trace_counter = 1;
static exchdlr global_handler;

bool try_() {
    return error_code == -1 ? true : false;
}

void finalize(const char * file, const char * func, int line) {
    if (error_code == -1)
        return;
    printf("\t%i) %s:%i in '%s'\n", trace_counter++, file, line, func);
    if (global_handler)
        return global_handler(error_code);
    printf("No error handler defined. Exiting...");
}

bool err(int e, const char * file, const char * func, int line) {
    if (e != -1) {
        error_code = e;
        puts("Tracing back exception:");
    }
    printf("\t%i) %s:%i in '%s'\n", trace_counter++, file, line, func);
    return false;
}

void set_handle(exchdlr handler) {
    global_handler = handler;
}
