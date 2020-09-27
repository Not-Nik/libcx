// cx (c) Nikolas Wipper 2020

#include "cx2.h"

#include <stdio.h>
#include <stdlib.h>

static exchdlr global_handler;
static int trace_counter = 1;
static jmp_buf * env;

void err_() {
    puts("Tracing back exception:");
}

void trace_(const char * file, const char * func, int line) {
    printf("\t%i) %s:%i in '%s'\n", trace_counter++, file, line, func);
}

jmp_buf * save_env(jmp_buf * new_env) {
    jmp_buf * temp = env;
    env = new_env;
    return temp;
}

void sighandler(int signum) {
    jmp_buf * env = save_env((jmp_buf *)0); \
    err_();
    int error = 0;
    if (signum == SIGABRT) error = ABORT +1;
    else if (signum == SIGFPE) error = FLOATING_POINT_EXCEPTION +1;
    else if (signum == SIGILL) error = ILLEGAL_INSTRUCTION +1;
    else if (signum == SIGINT) error = INTERRUPT +1;
    else if (signum == SIGSEGV) error = SEGMENTATION_VIOLATION +1;
    else if (signum == SIGTERM) error = TERMINATE +1;
    longjmp(*env, error);
}

void set_handle(exchdlr handler) {
    signal(SIGINT, sighandler);
    signal(SIGFPE, sighandler);
    signal(SIGILL, sighandler);
    signal(SIGINT, sighandler);
    signal(SIGSEGV, sighandler);
    signal(SIGTERM, sighandler);
    global_handler = handler;
}

void finalize(int err) {
    global_handler(err -1);
    exit(1);
}
