#ifndef OBDH__PUS__SERVICES__SERVICE19_H__
#define OBDH__PUS__SERVICES__SERVICE19_H__

#include <termina.h>

#include "obdh/pus/services/service19/types.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* notify_tm_1_3)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* notify_tm_1_7)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_4_EvID_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t EvID);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
        void (* send_tm_1_4_ev_action_enabled)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);
        void (* send_tm_1_4_ev_action_rejected)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);
        void (* send_tm_1_4_ev_action_undefined)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);
        void (* send_tm_1_4_num_of_instr_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N);
        void (* send_tm_1_4_short_pack_length)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);
        void (* send_tm_1_8_max_ev_actions_defined)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t evID);
    } pus_service_1;
    size_t pending_action_head[4U];
    size_t pending_action_number[4U];
    TCHandler pending_action_queue_4HS[8U];
    TCHandler pending_action_queue_3MS[8U];
    TCHandler pending_action_queue_2LS[8U];
    TCHandler pending_action_queue_1I[8U];
    TCHandler event_action_packets[16U];
    EventActionConfig event_action_config[16U];
} CPUSService19;

void CPUSService19__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);

void CPUSService19__extract_action(const termina__event_t * const termina__ev, void * const termina__this, const size_t action_index, TCHandler * const action_packet);

void CPUSService19__get_pending_action_number(const termina__event_t * const termina__ev, void * const termina__this, size_t paction_num[4U]);

void CPUSService19__manage_event_action(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID);

#endif
