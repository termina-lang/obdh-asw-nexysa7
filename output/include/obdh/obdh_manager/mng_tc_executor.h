#ifndef OBDH__OBDH_MANAGER__MNG_TC_EXECUTOR_H__
#define OBDH__OBDH_MANAGER__MNG_TC_EXECUTOR_H__

#include <termina.h>

#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service128.h"
#include "obdh/pus/services/service17.h"
#include "obdh/pus/services/service2.h"
#include "obdh/pus/services/service9.h"
#include "obdh/pus/tc_packet.h"
#include "obdh/pus/tm_packet.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* notify_tm_1_1)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_2)(const termina__event_t * const termina__ev, void * const termina__this, const TCStatus * const tc_status, const TCHandler * const tc_handler);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
    } pus_service_1;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested);
    } pus_service_128;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
    } pus_service_9;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
    } pus_service_2;
    struct {
        void * _that;
        void (* exec_tc)(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);
    } pus_service_17;
} CManagerTExecutor;

void CManagerTExecutor__PUS_prio_exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested);

void CManagerTExecutor__mng_tc_acceptation(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler);

void CManagerTExecutor__mng_tc_rejection(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler, const TCStatus * const tc_status);

#endif
