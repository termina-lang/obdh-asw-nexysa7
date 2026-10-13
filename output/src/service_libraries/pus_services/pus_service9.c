
#include "service_libraries/pus_services/pus_service9.h"

static Status__i32 CPUSService9__exec9_129TC(const termina__event_t * const termina__ev, CPUSService9 * const self);

static Status__i32 CPUSService9__exec9_129TC(const termina__event_t * const termina__ev, CPUSService9 * const self) {
    
    #line 52 "src/service_libraries/pus_services/pus_service9.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 54 "src/service_libraries/pus_services/pus_service9.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    #line 60 "src/service_libraries/pus_services/pus_service9.fin"
    if (status._variant == Status__Success) {
        
        #line 62 "src/service_libraries/pus_services/pus_service9.fin"
        self->obt_manager.set_obt(termina__ev, self->obt_manager._that, self->exec_tc_req_status_update.next_OBT);

        #line 64 "src/service_libraries/pus_services/pus_service9.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    }

    #line 72 "src/service_libraries/pus_services/pus_service9.fin"
    return status;

}

void CPUSService9__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 85 "src/service_libraries/pus_services/pus_service9.fin"
    CPUSService9 * self = (CPUSService9 *)termina__this;

    #line 85 "src/service_libraries/pus_services/pus_service9.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 87 "src/service_libraries/pus_services/pus_service9.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 89 "src/service_libraries/pus_services/pus_service9.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 90 "src/service_libraries/pus_services/pus_service9.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 91 "src/service_libraries/pus_services/pus_service9.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 92 "src/service_libraries/pus_services/pus_service9.fin"
    self->exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 94 "src/service_libraries/pus_services/pus_service9.fin"
    Status__i32 status = tc_handler_get_u32_appdata_field(tc_handler, &self->exec_tc_req_status_update.next_OBT.seconds);

    #line 96 "src/service_libraries/pus_services/pus_service9.fin"
    if (status._variant == Status__Success) {
        
        #line 97 "src/service_libraries/pus_services/pus_service9.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.next_OBT.finetime);

    }

    #line 100 "src/service_libraries/pus_services/pus_service9.fin"
    if (status._variant == Status__Success) {
        
        #line 102 "src/service_libraries/pus_services/pus_service9.fin"
        if (subtype == 129U) {
            
            #line 104 "src/service_libraries/pus_services/pus_service9.fin"
            status = CPUSService9__exec9_129TC(termina__ev, self);

        } else
        {
            
            #line 108 "src/service_libraries/pus_services/pus_service9.fin"
            status._variant = Status__Failure;
            #line 108 "src/service_libraries/pus_services/pus_service9.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 116 "src/service_libraries/pus_services/pus_service9.fin"
    if (status._variant == Status__Success) {
        
        #line 118 "src/service_libraries/pus_services/pus_service9.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 121 "src/service_libraries/pus_services/pus_service9.fin"
        const int32_t error_code = status.Failure._0;

        #line 123 "src/service_libraries/pus_services/pus_service9.fin"
        if (error_code == 4L) {
            
            #line 125 "src/service_libraries/pus_services/pus_service9.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 130 "src/service_libraries/pus_services/pus_service9.fin"
        if (error_code == 3L) {
            
            #line 132 "src/service_libraries/pus_services/pus_service9.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 137 "src/service_libraries/pus_services/pus_service9.fin"
        if (error_code == 5L) {
            
            #line 139 "src/service_libraries/pus_services/pus_service9.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        {
            
            #line 147 "src/service_libraries/pus_services/pus_service9.fin"
            (*action_status)._variant = Status__Failure;
            #line 147 "src/service_libraries/pus_services/pus_service9.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 154 "src/service_libraries/pus_services/pus_service9.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 154 "src/service_libraries/pus_services/pus_service9.fin"
    return;

}
