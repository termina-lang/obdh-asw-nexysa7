#ifndef OBDH__PUS__SERVICES__SERVICE9_H__
#define OBDH__PUS__SERVICES__SERVICE9_H__

#include <termina.h>

#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service9/types.h"
#include "obdh/pus/tm_handler.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* notify_tm_1_3)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* notify_tm_1_7)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
        void (* send_tm_1_4_short_pack_length)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);
    } pus_service_1;
    struct {
        void * _that;
        void (* set_obt)(const termina__event_t * const termina__ev, void * const termina__this, const CUCTime next_obt);
    } obt_manager;
} CPUSService9;

void CPUSService9__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);

#endif
