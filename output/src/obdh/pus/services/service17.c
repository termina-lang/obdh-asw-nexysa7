
#include "obdh/pus/services/service17.h"

static void CPUSService17__exec17_1TC(const termina__event_t * const termina__ev, CPUSService17 * const self, const PS17TCRequest * const tc_request);

static void CPUSService17__exec17_1TC(const termina__event_t * const termina__ev, CPUSService17 * const self, const PS17TCRequest * const tc_request) {
    
    #line 68 "src/obdh/pus/services/service17.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 73 "src/obdh/pus/services/service17.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 74 "src/obdh/pus/services/service17.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 78 "src/obdh/pus/services/service17.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 78 "src/obdh/pus/services/service17.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 80 "src/obdh/pus/services/service17.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 81 "src/obdh/pus/services/service17.fin"
        uint16_t tm_count = 0U;

        #line 83 "src/obdh/pus/services/service17.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 84 "src/obdh/pus/services/service17.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 85 "src/obdh/pus/services/service17.fin"
        build_tm_17_2((TMHandler *)b_tm_handler.data, tm_count, current_obt);

        #line 86 "src/obdh/pus/services/service17.fin"
        self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

    } else
    {
        
        #line 91 "src/obdh/pus/services/service17.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 97 "src/obdh/pus/services/service17.fin"
    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 102 "src/obdh/pus/services/service17.fin"
    return;

}

void CPUSService17__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 113 "src/obdh/pus/services/service17.fin"
    CPUSService17 * self = (CPUSService17 *)termina__this;

    #line 113 "src/obdh/pus/services/service17.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 115 "src/obdh/pus/services/service17.fin"
    Status__PUSService17Error status = { ._variant = Status__Success };

    #line 116 "src/obdh/pus/services/service17.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 117 "src/obdh/pus/services/service17.fin"
    PS17TCRequest tc_request = { .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U };

    #line 119 "src/obdh/pus/services/service17.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 120 "src/obdh/pus/services/service17.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 121 "src/obdh/pus/services/service17.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 124 "src/obdh/pus/services/service17.fin"
    if (subtype == 1U) {
        
        #line 126 "src/obdh/pus/services/service17.fin"
        CPUSService17__exec17_1TC(termina__ev, self, &tc_request);

    } else
    {
        
        #line 130 "src/obdh/pus/services/service17.fin"
        status._variant = Status__Failure;
        #line 130 "src/obdh/pus/services/service17.fin"
        status.Failure._0._variant = PUSService17Error__ErrorInAcceptance;

    }

    #line 136 "src/obdh/pus/services/service17.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 139 "src/obdh/pus/services/service17.fin"
        const PUSService17Error error = status.Failure._0;

        (void)error;

        #line 145 "src/obdh/pus/services/service17.fin"
        self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

    }

    #line 155 "src/obdh/pus/services/service17.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 155 "src/obdh/pus/services/service17.fin"
    return;

}
