#ifndef OBDH__OBDH_MANAGER__OBDH_MANAGER_H__
#define OBDH__OBDH_MANAGER__OBDH_MANAGER_H__

#include <termina.h>

#include "obdh/obdh_manager/mng_tc_executor.h"

#include "option.h"

typedef struct {
    termina__id_t _task_id;
    termina__id_t _task_msg_queue_id;
    struct {
        void * _that;
        void (* PUS_prio_exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested);
        void (* mng_tc_acceptation)(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler);
        void (* mng_tc_rejection)(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler, const TCStatus * const tc_status);
    } mng_tc_executor;
    termina__out_port_t bkg_message_queue_output;
    termina__out_port_t hkfdir_message_queue_output;
    termina__allocator_t tc_handler_pool;
    termina__id_t action_tc_message_queue_input;
    termina__id_t tc_message_queue_input;
} COBDHManagerTask;

void termina__task_entry__COBDHManagerTask(void * const arg);

void COBDHManagerTask__process_action_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler);

void COBDHManagerTask__process_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler);

#endif
