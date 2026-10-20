
#include "obdh/pus/services/service9.h"

static void CPUSService9__exec9_129TC(const termina__event_t * const termina__ev, CPUSService9 * const self, const PS9TCRequest * const tc_request);

static void CPUSService9__exec9_129TC(const termina__event_t * const termina__ev, CPUSService9 * const self, const PS9TCRequest * const tc_request) {
    
    #line 50 "src/obdh/pus/services/service9.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 55 "src/obdh/pus/services/service9.fin"
    self->obt_manager.set_obt(termina__ev, self->obt_manager._that, tc_request->next_OBT);

    #line 57 "src/obdh/pus/services/service9.fin"
    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 62 "src/obdh/pus/services/service9.fin"
    return;

}

void CPUSService9__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 74 "src/obdh/pus/services/service9.fin"
    CPUSService9 * self = (CPUSService9 *)termina__this;

    #line 74 "src/obdh/pus/services/service9.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 76 "src/obdh/pus/services/service9.fin"
    Status__PUSService9Error status = { ._variant = Status__Success };

    #line 77 "src/obdh/pus/services/service9.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 78 "src/obdh/pus/services/service9.fin"
    PS9TCRequest tc_request = { .flags_ack = 0U, .next_OBT = { .finetime = 0U, .seconds = 0U }, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 80 "src/obdh/pus/services/service9.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 81 "src/obdh/pus/services/service9.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 82 "src/obdh/pus/services/service9.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 83 "src/obdh/pus/services/service9.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 85 "src/obdh/pus/services/service9.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &tc_request.next_OBT.seconds);

    #line 87 "src/obdh/pus/services/service9.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 88 "src/obdh/pus/services/service9.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.next_OBT.finetime);

    }

    #line 91 "src/obdh/pus/services/service9.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 92 "src/obdh/pus/services/service9.fin"
        status._variant = Status__Failure;
        #line 92 "src/obdh/pus/services/service9.fin"
        status.Failure._0._variant = PUSService9Error__AppDataOutOfRange;
        #line 92 "src/obdh/pus/services/service9.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 95 "src/obdh/pus/services/service9.fin"
    if (status._variant == Status__Success) {
        
        #line 97 "src/obdh/pus/services/service9.fin"
        if (subtype == 129U) {
            
            #line 99 "src/obdh/pus/services/service9.fin"
            CPUSService9__exec9_129TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 103 "src/obdh/pus/services/service9.fin"
            status._variant = Status__Failure;
            #line 103 "src/obdh/pus/services/service9.fin"
            status.Failure._0._variant = PUSService9Error__ErrorInAcceptance;

        }

    }

    #line 111 "src/obdh/pus/services/service9.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 114 "src/obdh/pus/services/service9.fin"
        const PUSService9Error error = status.Failure._0;

        #line 118 "src/obdh/pus/services/service9.fin"
        if (error._variant == PUSService9Error__ErrorInAcceptance) {
            
            #line 120 "src/obdh/pus/services/service9.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        {
            
            #line 125 "src/obdh/pus/services/service9.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 127 "src/obdh/pus/services/service9.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        }

    }

    #line 138 "src/obdh/pus/services/service9.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 138 "src/obdh/pus/services/service9.fin"
    return;

}
