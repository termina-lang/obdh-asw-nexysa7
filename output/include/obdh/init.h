#ifndef OBDH__INIT_H__
#define OBDH__INIT_H__

#include <termina.h>

#include "drivers/gaisler/apbuart.h"
#include "drivers/gaisler/grgpio.h"
#include "obdh/system_data_pool.h"

#include "option.h"

extern const uint32_t Zero;

extern const uint32_t Unit;

extern const uint32_t Dec;

typedef struct {
    termina__id_t _handler_id;
    _Atomic uint8_t * system_data_pool_u8;
    _Atomic uint32_t * system_data_pool_u32;
    struct {
        void * _that;
        void (* init_gpio)(const termina__event_t * const termina__ev, void * const termina__this);
    } gpio_driver;
    struct {
        void * _that;
        void (* initialize)(const termina__event_t * const termina__ev, void * const termina__this);
    } uart_drv;
} CInitHandler;

void CInitHandler__init(const termina__event_t * const termina__ev, void * const termina__this, const TimeVal termina__ignored__boot_time);

#endif
