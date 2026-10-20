#ifndef OBDH__PUS__SERVICES__SERVICE1_H__
#define OBDH__PUS__SERVICES__SERVICE1_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1/internal.h"
#include "obdh/pus/services/service1/tc_acceptance.h"
#include "obdh/pus/tc_handler.h"
#include "obdh/tm_counter.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

extern const uint8_t TM_1_4_TC_X_Y_TC_SHORT_PACK_LENGTH;

extern const uint8_t TM_1_4_TC_X_Y_TC_NOT_VALID_NUM_OF_INSTR;

extern const uint8_t TM_1_4_TC_2_X_DEVICE_NOT_VALID;

extern const uint8_t TM_1_4_TC_2_X_DEVICE_ADDRESS_NOT_VALID;

extern const uint8_t TM_1_4_TC_3_X_INVALID_SID;

extern const uint8_t TM_1_4_TC_4_7_PID_STATS_UNDEFINED;

extern const uint8_t TM_1_4_TC_5_X_INVALID_EV_ID;

extern const uint8_t TM_1_4_TC_6_X_INVALID_MEMORY_ADDRESS;

extern const uint8_t TM_1_4_TC_6_X_MEMORY_ID_READ_ONLY;

extern const uint8_t TM_1_4_TC_6_X_OUT_OF_MEMORY_ID_LIMITS;

extern const uint8_t TM_1_4_TC_11_X_SCHED_TC_REJECTED;

extern const uint8_t TM_1_4_TC_11_X_INVALID_SCHED_TIME;

extern const uint8_t TM_1_4_TC_12_X_PMON_UNDEFINED;

extern const uint8_t TM_1_4_TC_12_X_PMON_DEFINED;

extern const uint8_t TM_1_4_TC_12_X_PMON_ENABLED;

extern const uint8_t TM_1_4_TC_12_X_INVALID_PMONID;

extern const uint8_t TM_1_4_TC_12_X_INVALID_PMON_DEFINITION;

extern const uint8_t TM_1_4_TC_15_X_INVALID_PACKET_STORE;

extern const uint8_t TM_1_4_TC_19_X_EV_ACTION_IS_ENABLED;

extern const uint8_t TM_1_4_TC_19_1_EV_ACTION_REJECTED;

extern const uint8_t TM_1_4_TC_19_X_EV_ACTION_NOT_DEFINED;

extern const uint8_t TM_1_4_TC_20_X_INVALID_PID;

extern const uint8_t TM_1_4_TC_20_X_PID_READ_ONLY_VIA_TC;

extern const uint8_t TM_1_4_ERROR_IN_ACCEPTANCE;

extern const uint8_t TM_1_8_TM_X_Y_TM_EXCEED_LIMIT_APPDATA;

extern const uint8_t TM_1_8_TM_2_1_DEV_COMMAND_EXEC_ERROR;

extern const uint8_t TM_1_8_TC_4_1_NOT_FREE_PID_STATS_CONFIG;

extern const uint8_t TM_1_8_TC_6_X_MEM_ACCESS_FAIL;

extern const uint8_t TM_1_8_TC_11_X_SCHED_TC_POOL_EMPTY;

extern const uint8_t TM_1_8_TC_19_1_MAX_EV_ACTIONS_REACHED;

typedef struct {
    termina__resource_lock_type_t _lock_type;
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
} CPUSService1;

void CPUSService1__notify_tm_1_1(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);

void CPUSService1__notify_tm_1_3(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);

void CPUSService1__notify_tm_1_7(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);

void CPUSService1__send_tm_1_2(const termina__event_t * const termina__ev, void * const termina__this, const TCStatus * const tc_status, const TCHandler * const tc_handler);

void CPUSService1__send_tm_1_4_EvID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t EvID);

void CPUSService1__send_tm_1_4_PID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);

void CPUSService1__send_tm_1_4_PID_read_only_via_TC(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);

void CPUSService1__send_tm_1_4_PID_stats_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);

void CPUSService1__send_tm_1_4_PMONID_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID);

void CPUSService1__send_tm_1_4_PMON_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID);

void CPUSService1__send_tm_1_4_PMON_definition_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID);

void CPUSService1__send_tm_1_4_PMON_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID);

void CPUSService1__send_tm_1_4_PMON_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID);

void CPUSService1__send_tm_1_4_SID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t SID);

void CPUSService1__send_tm_1_4_device_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t device_address);

void CPUSService1__send_tm_1_4_error_in_acceptance(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);

void CPUSService1__send_tm_1_4_ev_action_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);

void CPUSService1__send_tm_1_4_ev_action_rejected(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);

void CPUSService1__send_tm_1_4_ev_action_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID);

void CPUSService1__send_tm_1_4_mem_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id, const uint32_t mem_address);

void CPUSService1__send_tm_1_4_mem_id_read_only(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id);

void CPUSService1__send_tm_1_4_num_of_instr_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N);

void CPUSService1__send_tm_1_4_short_pack_length(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);

void CPUSService1__send_tm_1_8_device_command_exec_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t on_off_command);

void CPUSService1__send_tm_1_8_max_ev_actions_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t evID);

void CPUSService1__send_tm_1_8_mem_access_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_ID);

void CPUSService1__send_tm_1_8_not_free_stats_config(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID);

void CPUSService1__send_tm_1_8_tm_exceed_limit_appdata(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);

#endif
