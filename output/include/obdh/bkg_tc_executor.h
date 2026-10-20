#ifndef OBDH__BKG_TC_EXECUTOR_H__
#define OBDH__BKG_TC_EXECUTOR_H__

#include <termina.h>

#include "encoding/binary.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service20.h"
#include "obdh/pus/services/service6.h"
#include "obdh/pus/tc_packet.h"
#include "obdh/pus/tm_packet.h"
#include "obdh/system_data_pool.h"
#include "obdh/tm_counter.h"

#include "option.h"

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
    } pus_service_6;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
    } pus_service_20;
    termina__allocator_t tc_handler_pool;
    termina__id_t bkg_message_queue_input;
} CBKGTCExecutorTask;

void termina__task_entry__CBKGTCExecutorTask(void * const arg);

void CBKGTCExecutorTask__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler);

#endif
