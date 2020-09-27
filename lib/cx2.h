// cx (c) Nikolas Wipper 2020

#ifndef CX_CX2_H
#define CX_CX2_H

#include <setjmp.h>

#define ERR(x) jmp_buf * env = save_env((jmp_buf *)0); \
err_();                                                  \
TRACE();                                                 \
longjmp(*env, x+1);

#define TRY(...) {jmp_buf my_env;       \
jmp_buf * returned = save_env(&my_env); \
int val = setjmp(my_env);               \
if (val)                                \
{                                       \
TRACE();                                \
longjmp(*returned, val);                \
}                                       \
__VA_ARGS__;                            \
}

#define FIN(...) {jmp_buf my_env;       \
save_env(&my_env);                      \
int val = setjmp(my_env);               \
if (val)                                \
{                                       \
TRACE();                                \
finalize(val);                          \
}                                       \
}                                       \
__VA_ARGS__;

#define TRACE() trace_(__FILE_NAME__, __func__, __LINE__)

typedef void (* exchdlr)(int);

typedef enum {
    ABORT = 22457,
    FLOATING_POINT_EXCEPTION,
    ILLEGAL_INSTRUCTION,
    INTERRUPT,
    SEGMENTATION_VIOLATION,
    TERMINATE,
} SIGNAL_ERRORS;

void err_();

void trace_(const char * file, const char * func, int line);

jmp_buf * save_env(jmp_buf * new_env);

// Sets exception handler for finalize
void set_handle(exchdlr handler);

void finalize(int err);

#endif //CX_CX2_H
