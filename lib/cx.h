#ifndef CX_CX_H
#define CX_CX_H

#include <stdbool.h>

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64
#endif
#endif

typedef struct {
    bool ex;
    int val;
} int_ex;

typedef struct {
    bool ex;
    float val;
} float_ex;

#ifdef ENV64
typedef struct {
    bool ex;
    long val;
} long_ex;

typedef struct {
    bool ex;
    double val;
} double_ex;
#endif

typedef void (* exchdlr)(int);

#define TRY(type, x) x.val; if (!try_()) return (type){.ex = err(-1, __FILE_NAME__, __func__, __LINE__)};
#define FIN(x) x.val; finalize(__FILE_NAME__, __func__, __LINE__);

#define OK(type, x) return (type){.ex = true, .val = x};
#define ERR(type, x) return (type){.ex = err(x, __FILE_NAME__, __func__, __LINE__)};

// Returns whether an exception is currently going on
bool try_();

// Calls error handler if exception is going on
void finalize(const char * file, const char * func, int line);

// Throw error code e. If e is -1 the previous error is kept.
bool err(int e, const char * file, const char * func, int line);

// Sets exception handler for finalize
void set_handle(exchdlr handler);

#endif //CX_CX_H
