#ifndef OBDH__PUS__SERVICES__SERVICE4_H__
#define OBDH__PUS__SERVICES__SERVICE4_H__

#include <termina.h>

#include "obdh/pus/services/service4/internal.h"
#include "obdh/system_data_pool.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* notify_tm_1_3)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* notify_tm_1_7)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_4_PID_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);
        void (* send_tm_1_4_PID_stats_undefined)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
        void (* send_tm_1_4_num_of_instr_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N);
        void (* send_tm_1_4_short_pack_length)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);
        void (* send_tm_1_8_not_free_stats_config)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);
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
    _Atomic uint8_t * system_data_pool_u8;
    _Atomic uint32_t * system_data_pool_u32;
    StatsConfig stats_config_table;
    StatsDef param_stats[4U];
} CPUSService4;

void CPUSService4__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);

void CPUSService4__startup(const termina__event_t * const termina__ev, void * const termina__this);

void CPUSService4__update_all_stats(const termina__event_t * const termina__ev, void * const termina__this);

#endif
