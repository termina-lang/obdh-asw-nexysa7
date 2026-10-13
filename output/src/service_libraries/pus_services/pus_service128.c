
#include "service_libraries/pus_services/pus_service128.h"

static Status__i32 CPUSService128__exec128_1TC(const termina__event_t * const termina__ev, CPUSService128 * const self);

static Status__i32 CPUSService128__exec128_1TC(const termina__event_t * const termina__ev, CPUSService128 * const self) {
    
    #line 22 "src/service_libraries/pus_services/pus_service128.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 24 "src/service_libraries/pus_services/pus_service128.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    #line 30 "src/service_libraries/pus_services/pus_service128.fin"
    if (status._variant == Status__Success) {
        
        #line 31 "src/service_libraries/pus_services/pus_service128.fin"
        self->exec_tc_req_status_update.reebot_flag = true;

        #line 32 "src/service_libraries/pus_services/pus_service128.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    }

    #line 39 "src/service_libraries/pus_services/pus_service128.fin"
    return status;

}

void CPUSService128__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status, _Bool * const reebot_flag) {
    
    #line 43 "src/service_libraries/pus_services/pus_service128.fin"
    CPUSService128 * self = (CPUSService128 *)termina__this;

    #line 43 "src/service_libraries/pus_services/pus_service128.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 45 "src/service_libraries/pus_services/pus_service128.fin"
    Status__i32 status;

    #line 46 "src/service_libraries/pus_services/pus_service128.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 48 "src/service_libraries/pus_services/pus_service128.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 49 "src/service_libraries/pus_services/pus_service128.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 50 "src/service_libraries/pus_services/pus_service128.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 52 "src/service_libraries/pus_services/pus_service128.fin"
    if (subtype == 1U) {
        
        #line 54 "src/service_libraries/pus_services/pus_service128.fin"
        status = CPUSService128__exec128_1TC(termina__ev, self);

    } else
    {
        
        #line 58 "src/service_libraries/pus_services/pus_service128.fin"
        status._variant = Status__Failure;
        #line 58 "src/service_libraries/pus_services/pus_service128.fin"
        status.Failure._0 = 4L;

    }

    #line 64 "src/service_libraries/pus_services/pus_service128.fin"
    if (status._variant == Status__Success) {
        
        #line 66 "src/service_libraries/pus_services/pus_service128.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 69 "src/service_libraries/pus_services/pus_service128.fin"
        const int32_t error_code = status.Failure._0;

        #line 72 "src/service_libraries/pus_services/pus_service128.fin"
        if (error_code == 4L) {
            
            #line 74 "src/service_libraries/pus_services/pus_service128.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 79 "src/service_libraries/pus_services/pus_service128.fin"
        if (error_code == 3L) {
            
            #line 81 "src/service_libraries/pus_services/pus_service128.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        {
            
            #line 88 "src/service_libraries/pus_services/pus_service128.fin"
            (*action_status)._variant = Status__Failure;
            #line 88 "src/service_libraries/pus_services/pus_service128.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 95 "src/service_libraries/pus_services/pus_service128.fin"
    *reebot_flag = self->exec_tc_req_status_update.reebot_flag;

    #line 97 "src/service_libraries/pus_services/pus_service128.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 97 "src/service_libraries/pus_services/pus_service128.fin"
    return;

}
