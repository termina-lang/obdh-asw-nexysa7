#ifndef OBDH__TMTC__TC_FRAME_RECEIVER_H__
#define OBDH__TMTC__TC_FRAME_RECEIVER_H__

#include <termina.h>

#include "encoding/binary.h"
#include "obdh/pus/tc_handler.h"
#include "obdh/pus/tc_packet.h"

#include "option.h"

typedef enum {
    TCFrameRxStatus__SyncBytesRx,
    TCFrameRxStatus__SyncLengthRx
} termina__enum__TCFrameRxStatus_t;

typedef struct {
    termina__enum__TCFrameRxStatus_t _variant;
} TCFrameRxStatus;

typedef struct {
    termina__resource_lock_type_t _lock_type;
    termina__allocator_t tc_handler_pool;
    termina__deque_t * tc_frame;
    TCFrameRxStatus rx_status;
    size_t rx_index;
    uint8_t raw_rx_tc_length[2U];
    size_t sync_index;
    uint8_t sync_word[4U];
} CTCFrameReceiver;

void CTCFrameReceiver__receive(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte, Option__box * const tc_handler);

#endif
