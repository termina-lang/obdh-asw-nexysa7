#ifndef OBDH__HK_FDIR_H__
#define OBDH__HK_FDIR_H__

#include <termina.h>

#include "obdh/pus/services/service12.h"
#include "obdh/pus/services/service19.h"
#include "obdh/pus/services/service3.h"
#include "obdh/pus/services/service4.h"
#include "obdh/pus/services/service5.h"

#include "option.h"

extern const size_t num_actions_per_second;

typedef struct {
    termina__id_t _task_id;
    termina__id_t _task_msg_queue_id;
    struct {
        void * _that;
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
    } pus_service_1;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
        void (* update_all_stats)(const termina__event_t * const termina__ev, void * const termina__this);
    } pus_service_4;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
        void (* extract_action)(const termina__event_t * const termina__ev, void * const termina__this, const size_t action_index, TCHandler * const action_packet);
        void (* get_pending_action_number)(const termina__event_t * const termina__ev, void * const termina__this, size_t paction_num[4U]);
        void (* manage_event_action)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID);
    } pus_service_19;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
        void (* is_Ev_ID_enabled_ext)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t Ev_ID, _Bool * const p_enabled);
        void (* send_tm_5_x)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID, const FaultInfo * const fault_info);
    } pus_service_5;
    struct {
        void * _that;
        void (* do_monitoring)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t PMONID, uint16_t * const evID, FaultInfo * const fault_info, _Bool * const event_triggered);
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
        void (* is_PMON_enabled)(const termina__event_t * const termina__ev, void * const termina__this, const size_t PMONID, _Bool * const is_enabled);
    } pus_service_12;
    struct {
        void * _that;
        void (* do_hk)(const termina__event_t * const termina__ev, void * const termina__this);
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
        void (* update_params)(const termina__event_t * const termina__ev, void * const termina__this);
    } pus_service_3;
    termina__allocator_t tc_handler_pool;
    termina__out_port_t action_tc_message_queue_output;
    termina__id_t hkfdir_message_queue_input;
    termina__id_t hk_fdir_timer_ev;
} CHousekeepingFDIRTask;

void termina__task_entry__CHousekeepingFDIRTask(void * const arg);

void CHousekeepingFDIRTask__check_pending_actions(const termina__event_t * const termina__ev, void * const termina__this);

void CHousekeepingFDIRTask__do_fdir(const termina__event_t * const termina__ev, void * const termina__this);

void CHousekeepingFDIRTask__do_hk_fdir(const termina__event_t * const termina__ev, void * const termina__this, const TimeVal termina__ignored__current_time);

void CHousekeepingFDIRTask__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler);

#endif
