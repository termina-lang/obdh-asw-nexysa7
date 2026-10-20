#ifndef DRIVERS__GAISLER__APBUART_H__
#define DRIVERS__GAISLER__APBUART_H__

#include <termina.h>

#include "drivers/char_dev.h"

#include "option.h"

typedef struct {
    uint32_t data;
    uint32_t status;
    uint32_t control;
    uint32_t scaler;
} APBUARTRegs;

typedef struct {
    termina__resource_lock_type_t _lock_type;
    volatile APBUARTRegs * registers;
} CAPBUARTDriver;

void CAPBUARTDriver__initialize(const termina__event_t * const termina__ev, void * const termina__this);

void CAPBUARTDriver__read_byte(const termina__event_t * const termina__ev, void * const termina__this, Option__u8 * const byte);

void CAPBUARTDriver__stop_tx(const termina__event_t * const termina__ev, void * const termina__this);

void CAPBUARTDriver__tx_ready(const termina__event_t * const termina__ev, void * const termina__this, _Bool * const ready);

void CAPBUARTDriver__write_byte(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte);

#endif
