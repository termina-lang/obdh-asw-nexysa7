
#include "obdh/manager/tc_executor.h"

void CManagerTExecutor__PUS_prio_exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested) {
    
    #line 58 "src/obdh/manager/tc_executor.fin"
    CManagerTExecutor * self = (CManagerTExecutor *)termina__this;

    #line 58 "src/obdh/manager/tc_executor.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 60 "src/obdh/manager/tc_executor.fin"
    uint8_t tc_type = tc_handler->df_header.type;

    #line 62 "src/obdh/manager/tc_executor.fin"
    if (tc_type == 17U) {
        
        #line 64 "src/obdh/manager/tc_executor.fin"
        self->pus_service_17.exec_tc(termina__ev, self->pus_service_17._that, tc_handler);

    } else
    #line 66 "src/obdh/manager/tc_executor.fin"
    if (tc_type == 2U) {
        
        #line 68 "src/obdh/manager/tc_executor.fin"
        self->pus_service_2.exec_tc(termina__ev, self->pus_service_2._that, tc_handler);

    } else
    #line 70 "src/obdh/manager/tc_executor.fin"
    if (tc_type == 9U) {
        
        #line 72 "src/obdh/manager/tc_executor.fin"
        self->pus_service_9.exec_tc(termina__ev, self->pus_service_9._that, tc_handler);

    } else
    #line 74 "src/obdh/manager/tc_executor.fin"
    if (tc_type == 128U) {
        
        #line 76 "src/obdh/manager/tc_executor.fin"
        self->pus_service_128.exec_tc(termina__ev, self->pus_service_128._that, tc_handler, reboot_requested);

    } else
    {
        
        #line 80 "src/obdh/manager/tc_executor.fin"
        self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_handler->packet_header.packet_id, tc_handler->packet_header.packet_seq_ctrl);

    }

    #line 86 "src/obdh/manager/tc_executor.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 86 "src/obdh/manager/tc_executor.fin"
    return;

}

void CManagerTExecutor__mng_tc_acceptation(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler) {
    
    #line 98 "src/obdh/manager/tc_executor.fin"
    CManagerTExecutor * self = (CManagerTExecutor *)termina__this;

    #line 98 "src/obdh/manager/tc_executor.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 100 "src/obdh/manager/tc_executor.fin"
    self->pus_service_1.notify_tm_1_1(termina__ev, self->pus_service_1._that, tc_handler->packet_header.packet_id, tc_handler->packet_header.packet_seq_ctrl, tc_handler->df_header.flag_ver_ack);

    #line 105 "src/obdh/manager/tc_executor.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 105 "src/obdh/manager/tc_executor.fin"
    return;

}

void CManagerTExecutor__mng_tc_rejection(const termina__event_t * const termina__ev, void * const termina__this, const TCHandler * const tc_handler, const TCStatus * const tc_status) {
    
    #line 117 "src/obdh/manager/tc_executor.fin"
    CManagerTExecutor * self = (CManagerTExecutor *)termina__this;

    #line 117 "src/obdh/manager/tc_executor.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 119 "src/obdh/manager/tc_executor.fin"
    self->pus_service_1.send_tm_1_2(termina__ev, self->pus_service_1._that, tc_status, tc_handler);

    #line 121 "src/obdh/manager/tc_executor.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 121 "src/obdh/manager/tc_executor.fin"
    return;

}
