#ifndef DRIVERS__GAISLER__GRGPIO_H__
#define DRIVERS__GAISLER__GRGPIO_H__

#include <termina.h>

#include "drivers/gpio.h"

#include "option.h"

typedef struct {
    uint32_t Data;
    uint32_t Output;
    uint32_t Direction;
} GPIO_registers;

typedef struct {
    termina__resource_lock_type_t _lock_type;
    uint32_t output_mask;
    volatile GPIO_registers * registers;
} CGRGPIODriver;

void CGRGPIODriver__init_gpio(const termina__event_t * const termina__ev, void * const termina__this);

void CGRGPIODriver__read_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin, GPIOPinState * const state);

void CGRGPIODriver__toggle_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin);

void CGRGPIODriver__write_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin, const GPIOPinState state);

#endif
