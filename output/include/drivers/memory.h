#ifndef DRIVERS__MEMORY_H__
#define DRIVERS__MEMORY_H__

#include <termina.h>

#include "option.h"

typedef enum {
    MemAccessError__InvalidAccess,
    MemAccessError__ReadOnly
} termina__enum__MemAccessError_t;

typedef struct {
    termina__enum__MemAccessError_t _variant;
} MemAccessError;

typedef struct {
    MemAccessError _0;
} termina__enum__Status__MemAccessError__Failure_params_t;

typedef struct {
    termina__enum__Status__MemAccessError__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__MemAccessError;

#endif
