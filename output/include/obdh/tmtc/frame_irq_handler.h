#ifndef OBDH__TMTC__FRAME_IRQ_HANDLER_H__
#define OBDH__TMTC__FRAME_IRQ_HANDLER_H__

#include <termina.h>

#include "drivers/char_dev.h"
#include "obdh/pus/tc_handler.h"
#include "obdh/tmtc/tc_frame_receiver.h"
#include "obdh/tmtc/tm_frame_transmitter.h"

#include "option.h"

typedef struct {
    termina__id_t _handler_id;
    termina__out_port_t tc_message_queue_output;
    struct {
        void * _that;
        void (* transmit)(const termina__event_t * const termina__ev, void * const termina__this);
    } tm_frame_transmitter;
    struct {
        void * _that;
        void (* receive)(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte, Option__box * const tc_handler);
    } tc_frame_receiver;
    struct {
        void * _that;
        void (* read_byte)(const termina__event_t * const termina__ev, void * const termina__this, Option__u8 * const byte);
    } char_dev;
} CTMTCFrameIRQHandler;

void CTMTCFrameIRQHandler__irq_handler(const termina__event_t * const termina__ev, void * const termina__this, const uint32_t termina__ignored__vector);

#endif
