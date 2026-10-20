#ifndef DRIVERS__GAISLER__GRGPIO_H__
#define DRIVERS__GAISLER__GRGPIO_H__

#include <termina.h>

#include "option.h"

typedef enum {
    GPIODriverError__InvalidLEDIndex
} termina__enum__GPIODriverError_t;

typedef struct {
    termina__enum__GPIODriverError_t _variant;
} GPIODriverError;

typedef struct {
    GPIODriverError _0;
} termina__enum__Status__GPIODriverError__Failure_params_t;

typedef struct {
    termina__enum__Status__GPIODriverError__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__GPIODriverError;

typedef struct {
    uint32_t Data;
    uint32_t Output;
    uint32_t Direction;
} GPIO_registers;

typedef struct {
    termina__resource_lock_type_t _lock_type;
    volatile GPIO_registers * registers;
} CGPIODriver;

void CGPIODriver__init_gpio(const termina__event_t * const termina__ev, void * const termina__this);

void CGPIODriver__write_led(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t led, const uint8_t value, Status__GPIODriverError * const status);

#endif
