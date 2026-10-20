#ifndef OBDH__PUS__SERVICES__SERVICE6_H__
#define OBDH__PUS__SERVICES__SERVICE6_H__

#include <termina.h>

#include "drivers/memory.h"
#include "obdh/pus/services/service6/internal.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* notify_tm_1_3)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* notify_tm_1_7)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
        void (* send_tm_1_4_mem_address_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id, const uint32_t mem_address);
        void (* send_tm_1_4_mem_id_read_only)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id);
        void (* send_tm_1_4_num_of_instr_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N);
        void (* send_tm_1_4_short_pack_length)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);
        void (* send_tm_1_8_tm_exceed_limit_appdata)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
    } pus_service_1;
    struct {
        void * _that;
        void (* get_current_obt)(const termina__event_t * const termina__ev, void * const termina__this, CUCTime * const current_obt);
    } obt_manager;
    struct {
        void * _that;
        void (* count_lost_tm)(const termina__event_t * const termina__ev, void * const termina__this);
        void (* get_next_tm_count)(const termina__event_t * const termina__ev, void * const termina__this, uint16_t * const count);
    } tm_counter;
    termina__allocator_t tm_handler_pool;
    struct {
        void * _that;
        void (* send_tm)(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tm_handler);
    } tm_channel;
    struct {
        void * _that;
        void (* check_access)(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const _Bool write, Status__MemAccessError * const result);
        void (* checksum)(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint16_t * const checksum);
        void (* read)(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint8_t dst[256U]);
        void (* write)(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const uint8_t src[256U]);
    } memory;
} CPUSService6;

void CPUSService6__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);

#endif
