
#include "obdh/pus/services/service128.h"

void exec128_1TC(PS128TCRequest * const tc_request) {
    
    #line 17 "src/obdh/pus/services/service128.fin"
    tc_request->reboot_requested = true;

    #line 19 "src/obdh/pus/services/service128.fin"
    return;

}

void CPUSService128__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested) {
    
    #line 27 "src/obdh/pus/services/service128.fin"
    CPUSService128 * self = (CPUSService128 *)termina__this;

    #line 27 "src/obdh/pus/services/service128.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 29 "src/obdh/pus/services/service128.fin"
    Status__PUSService128Error status = { ._variant = Status__Success };

    #line 30 "src/obdh/pus/services/service128.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 31 "src/obdh/pus/services/service128.fin"
    PS128TCRequest tc_request = { .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .reboot_requested = false };

    #line 33 "src/obdh/pus/services/service128.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 34 "src/obdh/pus/services/service128.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 35 "src/obdh/pus/services/service128.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 37 "src/obdh/pus/services/service128.fin"
    if (subtype == 1U) {
        
        #line 39 "src/obdh/pus/services/service128.fin"
        exec128_1TC(&tc_request);

    } else
    {
        
        #line 43 "src/obdh/pus/services/service128.fin"
        status._variant = Status__Failure;
        #line 43 "src/obdh/pus/services/service128.fin"
        status.Failure._0._variant = PUSService128Error__ErrorInAcceptance;

    }

    #line 49 "src/obdh/pus/services/service128.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 52 "src/obdh/pus/services/service128.fin"
        const PUSService128Error error = status.Failure._0;

        (void)error;

        #line 58 "src/obdh/pus/services/service128.fin"
        self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

    }

    #line 68 "src/obdh/pus/services/service128.fin"
    *reboot_requested = tc_request.reboot_requested;

    #line 70 "src/obdh/pus/services/service128.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 70 "src/obdh/pus/services/service128.fin"
    return;

}
