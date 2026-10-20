
#include "obdh/pus/services/service6.h"

static Status__PUSService6Error CPUSService6__check_memory_access(const termina__event_t * const termina__ev, const CPUSService6 * const self, const PS6TCRequest * const tc_request, const _Bool write);

static Status__PUSService6Error CPUSService6__exec6_2TC(const termina__event_t * const termina__ev, CPUSService6 * const self, const PS6TCRequest * const tc_request);

static Status__PUSService6Error CPUSService6__exec6_5TC(const termina__event_t * const termina__ev, CPUSService6 * const self, PS6TCRequest * const tc_request);

static Status__PUSService6Error CPUSService6__exec6_9TC(const termina__event_t * const termina__ev, CPUSService6 * const self, const PS6TCRequest * const tc_request);

static Status__PUSService6Error CPUSService6__check_memory_access(const termina__event_t * const termina__ev, const CPUSService6 * const self, const PS6TCRequest * const tc_request, const _Bool write) {
    
    #line 31 "src/obdh/pus/services/service6.fin"
    Status__PUSService6Error status = { ._variant = Status__Success };

    #line 33 "src/obdh/pus/services/service6.fin"
    Status__MemAccessError access_status = { ._variant = Status__Success };

    #line 35 "src/obdh/pus/services/service6.fin"
    self->memory.check_access(termina__ev, self->memory._that, tc_request->mem_id, (size_t)tc_request->address, (size_t)tc_request->length, write, &access_status);

    #line 39 "src/obdh/pus/services/service6.fin"
    if (access_status._variant == Status__Success) {
        

    } else
    {
        
        #line 41 "src/obdh/pus/services/service6.fin"
        const MemAccessError error = access_status.Failure._0;

        #line 43 "src/obdh/pus/services/service6.fin"
        if (error._variant == MemAccessError__InvalidAccess) {
            
            #line 44 "src/obdh/pus/services/service6.fin"
            status._variant = Status__Failure;
            #line 44 "src/obdh/pus/services/service6.fin"
            status.Failure._0._variant = PUSService6Error__MemAddressNotValid;
            #line 44 "src/obdh/pus/services/service6.fin"
            status.Failure._0.MemAddressNotValid._0 = tc_request->mem_id;
            #line 44 "src/obdh/pus/services/service6.fin"
            status.Failure._0.MemAddressNotValid._1 = tc_request->address;

        } else
        {
            
            #line 48 "src/obdh/pus/services/service6.fin"
            status._variant = Status__Failure;
            #line 48 "src/obdh/pus/services/service6.fin"
            status.Failure._0._variant = PUSService6Error__MemIDReadOnly;
            #line 48 "src/obdh/pus/services/service6.fin"
            status.Failure._0.MemIDReadOnly._0 = tc_request->mem_id;

        }

    }

    #line 54 "src/obdh/pus/services/service6.fin"
    return status;

}

static Status__PUSService6Error CPUSService6__exec6_2TC(const termina__event_t * const termina__ev, CPUSService6 * const self, const PS6TCRequest * const tc_request) {
    
    #line 59 "src/obdh/pus/services/service6.fin"
    Status__PUSService6Error status;

    #line 61 "src/obdh/pus/services/service6.fin"
    if (tc_request->N != 1U) {
        
        #line 63 "src/obdh/pus/services/service6.fin"
        status._variant = Status__Failure;
        #line 63 "src/obdh/pus/services/service6.fin"
        status.Failure._0._variant = PUSService6Error__NumOfInstrNotValid;
        #line 63 "src/obdh/pus/services/service6.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 67 "src/obdh/pus/services/service6.fin"
        status = CPUSService6__check_memory_access(termina__ev, self, tc_request, true);

    }

    #line 71 "src/obdh/pus/services/service6.fin"
    if (status._variant == Status__Success) {
        
        #line 73 "src/obdh/pus/services/service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 78 "src/obdh/pus/services/service6.fin"
        self->memory.write(termina__ev, self->memory._that, tc_request->mem_id, (size_t)tc_request->address, (size_t)tc_request->length, tc_request->data);

        #line 81 "src/obdh/pus/services/service6.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    }

    #line 88 "src/obdh/pus/services/service6.fin"
    return status;

}

static Status__PUSService6Error CPUSService6__exec6_5TC(const termina__event_t * const termina__ev, CPUSService6 * const self, PS6TCRequest * const tc_request) {
    
    #line 94 "src/obdh/pus/services/service6.fin"
    Status__PUSService6Error status;

    #line 96 "src/obdh/pus/services/service6.fin"
    if (tc_request->N != 1U) {
        
        #line 98 "src/obdh/pus/services/service6.fin"
        status._variant = Status__Failure;
        #line 98 "src/obdh/pus/services/service6.fin"
        status.Failure._0._variant = PUSService6Error__NumOfInstrNotValid;
        #line 98 "src/obdh/pus/services/service6.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 102 "src/obdh/pus/services/service6.fin"
        status = CPUSService6__check_memory_access(termina__ev, self, tc_request, false);

    }

    #line 106 "src/obdh/pus/services/service6.fin"
    if (status._variant == Status__Success) {
        
        #line 108 "src/obdh/pus/services/service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 113 "src/obdh/pus/services/service6.fin"
        self->memory.read(termina__ev, self->memory._that, tc_request->mem_id, (size_t)tc_request->address, (size_t)tc_request->length, tc_request->data);

        #line 116 "src/obdh/pus/services/service6.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 117 "src/obdh/pus/services/service6.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 121 "src/obdh/pus/services/service6.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 121 "src/obdh/pus/services/service6.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 123 "src/obdh/pus/services/service6.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 124 "src/obdh/pus/services/service6.fin"
            uint16_t tm_count = 0U;

            #line 126 "src/obdh/pus/services/service6.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 127 "src/obdh/pus/services/service6.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 129 "src/obdh/pus/services/service6.fin"
            const Status__TMHandlerError tm_status = build_tm_6_6((TMHandler *)b_tm_handler.data, tm_count, current_obt, tc_request);

            #line 131 "src/obdh/pus/services/service6.fin"
            if (tm_status._variant == Status__Success) {
                
                #line 132 "src/obdh/pus/services/service6.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 134 "src/obdh/pus/services/service6.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 135 "src/obdh/pus/services/service6.fin"
                status._variant = Status__Failure;
                #line 135 "src/obdh/pus/services/service6.fin"
                status.Failure._0._variant = PUSService6Error__AppDataOverflow;

            }

        } else
        {
            
            #line 141 "src/obdh/pus/services/service6.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

        #line 145 "src/obdh/pus/services/service6.fin"
        if (status._variant == Status__Success) {
            
            #line 147 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        }

    }

    #line 156 "src/obdh/pus/services/service6.fin"
    return status;

}

static Status__PUSService6Error CPUSService6__exec6_9TC(const termina__event_t * const termina__ev, CPUSService6 * const self, const PS6TCRequest * const tc_request) {
    
    #line 162 "src/obdh/pus/services/service6.fin"
    Status__PUSService6Error status;

    #line 164 "src/obdh/pus/services/service6.fin"
    if (tc_request->N != 1U) {
        
        #line 166 "src/obdh/pus/services/service6.fin"
        status._variant = Status__Failure;
        #line 166 "src/obdh/pus/services/service6.fin"
        status.Failure._0._variant = PUSService6Error__NumOfInstrNotValid;
        #line 166 "src/obdh/pus/services/service6.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 170 "src/obdh/pus/services/service6.fin"
        status = CPUSService6__check_memory_access(termina__ev, self, tc_request, false);

    }

    #line 174 "src/obdh/pus/services/service6.fin"
    if (status._variant == Status__Success) {
        
        #line 176 "src/obdh/pus/services/service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 180 "src/obdh/pus/services/service6.fin"
        uint16_t checksum = 0U;

        #line 181 "src/obdh/pus/services/service6.fin"
        self->memory.checksum(termina__ev, self->memory._that, tc_request->mem_id, (size_t)tc_request->address, (size_t)tc_request->length, &checksum);

        #line 184 "src/obdh/pus/services/service6.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 185 "src/obdh/pus/services/service6.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 189 "src/obdh/pus/services/service6.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 189 "src/obdh/pus/services/service6.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 191 "src/obdh/pus/services/service6.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 192 "src/obdh/pus/services/service6.fin"
            uint16_t tm_count = 0U;

            #line 193 "src/obdh/pus/services/service6.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 194 "src/obdh/pus/services/service6.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 196 "src/obdh/pus/services/service6.fin"
            const Status__TMHandlerError tm_status = build_tm_6_10((TMHandler *)b_tm_handler.data, tm_count, current_obt, tc_request, checksum);

            #line 198 "src/obdh/pus/services/service6.fin"
            if (tm_status._variant == Status__Success) {
                
                #line 199 "src/obdh/pus/services/service6.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 201 "src/obdh/pus/services/service6.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 202 "src/obdh/pus/services/service6.fin"
                status._variant = Status__Failure;
                #line 202 "src/obdh/pus/services/service6.fin"
                status.Failure._0._variant = PUSService6Error__AppDataOverflow;

            }

        } else
        {
            
            #line 208 "src/obdh/pus/services/service6.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

        #line 212 "src/obdh/pus/services/service6.fin"
        if (status._variant == Status__Success) {
            
            #line 214 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        }

    }

    #line 223 "src/obdh/pus/services/service6.fin"
    return status;

}

void CPUSService6__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 227 "src/obdh/pus/services/service6.fin"
    CPUSService6 * self = (CPUSService6 *)termina__this;

    #line 227 "src/obdh/pus/services/service6.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 229 "src/obdh/pus/services/service6.fin"
    Status__PUSService6Error status = { ._variant = Status__Success };

    #line 230 "src/obdh/pus/services/service6.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 231 "src/obdh/pus/services/service6.fin"
    PS6TCRequest tc_request = { .N = 0U, .address = 0U, .data = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, .flags_ack = 0U, .length = 0U, .mem_id = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 233 "src/obdh/pus/services/service6.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 234 "src/obdh/pus/services/service6.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 235 "src/obdh/pus/services/service6.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 236 "src/obdh/pus/services/service6.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 238 "src/obdh/pus/services/service6.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.mem_id);

    #line 240 "src/obdh/pus/services/service6.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 241 "src/obdh/pus/services/service6.fin"
        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    }

    #line 244 "src/obdh/pus/services/service6.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 245 "src/obdh/pus/services/service6.fin"
        tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &tc_request.address);

    }

    #line 248 "src/obdh/pus/services/service6.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 249 "src/obdh/pus/services/service6.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.length);

    }

    #line 252 "src/obdh/pus/services/service6.fin"
    if (tc_data_status._variant == Status__Success && subtype == 2U) {
        
        #line 253 "src/obdh/pus/services/service6.fin"
        for (size_t j = 0U; j < 256U && (j < (size_t)tc_request.length && tc_data_status._variant == Status__Success); j = j + 1U) {
            
            #line 254 "src/obdh/pus/services/service6.fin"
            tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.data[j]);

        }

    }

    #line 258 "src/obdh/pus/services/service6.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 259 "src/obdh/pus/services/service6.fin"
        status._variant = Status__Failure;
        #line 259 "src/obdh/pus/services/service6.fin"
        status.Failure._0._variant = PUSService6Error__AppDataOutOfRange;
        #line 259 "src/obdh/pus/services/service6.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 262 "src/obdh/pus/services/service6.fin"
    if (status._variant == Status__Success) {
        
        #line 264 "src/obdh/pus/services/service6.fin"
        if (subtype == 2U) {
            
            #line 266 "src/obdh/pus/services/service6.fin"
            status = CPUSService6__exec6_2TC(termina__ev, self, &tc_request);

        } else
        #line 268 "src/obdh/pus/services/service6.fin"
        if (subtype == 5U) {
            
            #line 270 "src/obdh/pus/services/service6.fin"
            status = CPUSService6__exec6_5TC(termina__ev, self, &tc_request);

        } else
        #line 272 "src/obdh/pus/services/service6.fin"
        if (subtype == 9U) {
            
            #line 274 "src/obdh/pus/services/service6.fin"
            status = CPUSService6__exec6_9TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 278 "src/obdh/pus/services/service6.fin"
            status._variant = Status__Failure;
            #line 278 "src/obdh/pus/services/service6.fin"
            status.Failure._0._variant = PUSService6Error__ErrorInAcceptance;

        }

    }

    #line 285 "src/obdh/pus/services/service6.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 288 "src/obdh/pus/services/service6.fin"
        const PUSService6Error error = status.Failure._0;

        #line 292 "src/obdh/pus/services/service6.fin"
        if (error._variant == PUSService6Error__ErrorInAcceptance) {
            
            #line 294 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 299 "src/obdh/pus/services/service6.fin"
        if (error._variant == PUSService6Error__AppDataOutOfRange) {
            
            #line 299 "src/obdh/pus/services/service6.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 301 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 307 "src/obdh/pus/services/service6.fin"
        if (error._variant == PUSService6Error__AppDataOverflow) {
            
            #line 309 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 314 "src/obdh/pus/services/service6.fin"
        if (error._variant == PUSService6Error__NumOfInstrNotValid) {
            
            #line 314 "src/obdh/pus/services/service6.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 316 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        #line 322 "src/obdh/pus/services/service6.fin"
        if (error._variant == PUSService6Error__MemAddressNotValid) {
            
            #line 322 "src/obdh/pus/services/service6.fin"
            const uint8_t mem_id = error.MemAddressNotValid._0;
            #line 322 "src/obdh/pus/services/service6.fin"
            const uint32_t address = error.MemAddressNotValid._1;

            #line 324 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_4_mem_address_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, mem_id, address);

        } else
        {
            
            #line 331 "src/obdh/pus/services/service6.fin"
            const uint8_t mem_id = error.MemIDReadOnly._0;

            #line 333 "src/obdh/pus/services/service6.fin"
            self->pus_service_1.send_tm_1_4_mem_id_read_only(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, mem_id);

        }

    }

    #line 344 "src/obdh/pus/services/service6.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 344 "src/obdh/pus/services/service6.fin"
    return;

}
