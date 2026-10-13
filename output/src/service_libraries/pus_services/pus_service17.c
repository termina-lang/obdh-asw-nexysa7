
#include "service_libraries/pus_services/pus_service17.h"

static Status__i32 CPUSService17__exec17_1TC(const termina__event_t * const termina__ev, CPUSService17 * const self);

static Status__i32 CPUSService17__exec17_1TC(const termina__event_t * const termina__ev, CPUSService17 * const self) {
    
    #line 76 "src/service_libraries/pus_services/pus_service17.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 78 "src/service_libraries/pus_services/pus_service17.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    #line 85 "src/service_libraries/pus_services/pus_service17.fin"
    if (status._variant == Status__Success) {
        
        #line 87 "src/service_libraries/pus_services/pus_service17.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 88 "src/service_libraries/pus_services/pus_service17.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 92 "src/service_libraries/pus_services/pus_service17.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 92 "src/service_libraries/pus_services/pus_service17.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 94 "src/service_libraries/pus_services/pus_service17.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 95 "src/service_libraries/pus_services/pus_service17.fin"
            uint16_t tm_count = 0U;

            #line 97 "src/service_libraries/pus_services/pus_service17.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 98 "src/service_libraries/pus_services/pus_service17.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 99 "src/service_libraries/pus_services/pus_service17.fin"
            build_tm_17_2((TMHandler *)b_tm_handler.data, tm_count, current_obt);

            #line 100 "src/service_libraries/pus_services/pus_service17.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &status);

        } else
        {
            
            #line 105 "src/service_libraries/pus_services/pus_service17.fin"
            status._variant = Status__Failure;
            #line 105 "src/service_libraries/pus_services/pus_service17.fin"
            status.Failure._0 = 1L;

        }

    }

    #line 113 "src/service_libraries/pus_services/pus_service17.fin"
    if (status._variant == Status__Success) {
        
        #line 115 "src/service_libraries/pus_services/pus_service17.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    }

    #line 123 "src/service_libraries/pus_services/pus_service17.fin"
    return status;

}

void CPUSService17__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 135 "src/service_libraries/pus_services/pus_service17.fin"
    CPUSService17 * self = (CPUSService17 *)termina__this;

    #line 135 "src/service_libraries/pus_services/pus_service17.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 137 "src/service_libraries/pus_services/pus_service17.fin"
    Status__i32 status;

    #line 138 "src/service_libraries/pus_services/pus_service17.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 140 "src/service_libraries/pus_services/pus_service17.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 141 "src/service_libraries/pus_services/pus_service17.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 142 "src/service_libraries/pus_services/pus_service17.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 145 "src/service_libraries/pus_services/pus_service17.fin"
    if (subtype == 1U) {
        
        #line 147 "src/service_libraries/pus_services/pus_service17.fin"
        status = CPUSService17__exec17_1TC(termina__ev, self);

    } else
    {
        
        #line 151 "src/service_libraries/pus_services/pus_service17.fin"
        status._variant = Status__Failure;
        #line 151 "src/service_libraries/pus_services/pus_service17.fin"
        status.Failure._0 = 4L;

    }

    #line 157 "src/service_libraries/pus_services/pus_service17.fin"
    if (status._variant == Status__Success) {
        
        #line 159 "src/service_libraries/pus_services/pus_service17.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 162 "src/service_libraries/pus_services/pus_service17.fin"
        const int32_t error_code = status.Failure._0;

        #line 165 "src/service_libraries/pus_services/pus_service17.fin"
        if (error_code == 4L) {
            
            #line 167 "src/service_libraries/pus_services/pus_service17.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 172 "src/service_libraries/pus_services/pus_service17.fin"
        if (error_code == 3L) {
            
            #line 174 "src/service_libraries/pus_services/pus_service17.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        {
            
            #line 181 "src/service_libraries/pus_services/pus_service17.fin"
            (*action_status)._variant = Status__Failure;
            #line 181 "src/service_libraries/pus_services/pus_service17.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 188 "src/service_libraries/pus_services/pus_service17.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 188 "src/service_libraries/pus_services/pus_service17.fin"
    return;

}
