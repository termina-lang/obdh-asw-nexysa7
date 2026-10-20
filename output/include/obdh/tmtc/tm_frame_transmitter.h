#ifndef OBDH__TMTC__TM_FRAME_TRANSMITTER_H__
#define OBDH__TMTC__TM_FRAME_TRANSMITTER_H__

#include <termina.h>

#include "drivers/char_dev.h"
#include "encoding/binary.h"
#include "obdh/pus/tm_handler.h"
#include "obdh/pus/tm_packet.h"
#include "obdh/tm_counter.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    size_t tx_index;
    termina__deque_t * tm_frames;
    struct {
        void * _that;
        void (* count_lost_tm)(const termina__event_t * const termina__ev, void * const termina__this);
    } tm_counter;
    termina__allocator_t tm_handler_pool;
    struct {
        void * _that;
        void (* stop_tx)(const termina__event_t * const termina__ev, void * const termina__this);
        void (* tx_ready)(const termina__event_t * const termina__ev, void * const termina__this, _Bool * const ready);
        void (* write_byte)(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte);
    } char_dev;
    uint8_t sync_word[4U];
} CTMFrameTransmitter;

void CTMFrameTransmitter__send_tm(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tm_handler);

void CTMFrameTransmitter__transmit(const termina__event_t * const termina__ev, void * const termina__this);

#endif
