#ifndef DRIVERS__GPIO_H__
#define DRIVERS__GPIO_H__

#include <termina.h>

#include "option.h"

typedef enum {
    GPIOPinState__Low,
    GPIOPinState__High
} termina__enum__GPIOPinState_t;

typedef struct {
    termina__enum__GPIOPinState_t _variant;
} GPIOPinState;

typedef struct {
    size_t port;
    size_t pin;
} GPIOPinId;

typedef struct {
    GPIOPinId _0;
} termina__enum__Option__GPIOPinId__Some_params_t;

typedef struct {
    termina__enum__Option__GPIOPinId__Some_params_t Some;
    termina__enum__Option_t _variant;
} Option__GPIOPinId;

#endif
