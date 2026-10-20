
#include "obdh/pus/services/service5.h"

static Status__PUSService5Error CPUSService5__exec5_5TC(const termina__event_t * const termina__ev, CPUSService5 * const self, const PS5TCRequest * const tc_request);

static Status__PUSService5Error CPUSService5__exec5_6TC(const termina__event_t * const termina__ev, CPUSService5 * const self, const PS5TCRequest * const tc_request);

static _Bool CPUSService5__is_Ev_ID_enabled(const termina__event_t * const termina__ev, const CPUSService5 * const self, const uint16_t Ev_ID);

static Status__PUSService5Error CPUSService5__exec5_5TC(const termina__event_t * const termina__ev, CPUSService5 * const self, const PS5TCRequest * const tc_request) {
    
    #line 86 "src/obdh/pus/services/service5.fin"
    Status__PUSService5Error status = { ._variant = Status__Success };

    #line 88 "src/obdh/pus/services/service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(tc_request->EvID);

    #line 89 "src/obdh/pus/services/service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(tc_request->EvID);

    #line 91 "src/obdh/pus/services/service5.fin"
    if (tc_request->N != 1U) {
        
        #line 93 "src/obdh/pus/services/service5.fin"
        status._variant = Status__Failure;
        #line 93 "src/obdh/pus/services/service5.fin"
        status.Failure._0._variant = PUSService5Error__NumOfInstrNotValid;
        #line 93 "src/obdh/pus/services/service5.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 95 "src/obdh/pus/services/service5.fin"
    if (config_slot == 0U) {
        
        #line 97 "src/obdh/pus/services/service5.fin"
        status._variant = Status__Failure;
        #line 97 "src/obdh/pus/services/service5.fin"
        status.Failure._0._variant = PUSService5Error__EvIDNotValid;
        #line 97 "src/obdh/pus/services/service5.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->EvID;

    } else
    {
        
        #line 101 "src/obdh/pus/services/service5.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 106 "src/obdh/pus/services/service5.fin"
        const uint32_t mask = (uint32_t)0x1U << termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU));

        #line 107 "src/obdh/pus/services/service5.fin"
        self->Ev_ID_enable_config[config_slot - 1U] = self->Ev_ID_enable_config[config_slot - 1U] | mask;

        #line 109 "src/obdh/pus/services/service5.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    }

    #line 116 "src/obdh/pus/services/service5.fin"
    return status;

}

static Status__PUSService5Error CPUSService5__exec5_6TC(const termina__event_t * const termina__ev, CPUSService5 * const self, const PS5TCRequest * const tc_request) {
    
    #line 122 "src/obdh/pus/services/service5.fin"
    Status__PUSService5Error status = { ._variant = Status__Success };

    #line 124 "src/obdh/pus/services/service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(tc_request->EvID);

    #line 125 "src/obdh/pus/services/service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(tc_request->EvID);

    #line 127 "src/obdh/pus/services/service5.fin"
    if (tc_request->N != 1U) {
        
        #line 129 "src/obdh/pus/services/service5.fin"
        status._variant = Status__Failure;
        #line 129 "src/obdh/pus/services/service5.fin"
        status.Failure._0._variant = PUSService5Error__NumOfInstrNotValid;
        #line 129 "src/obdh/pus/services/service5.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 131 "src/obdh/pus/services/service5.fin"
    if (config_slot == 0U) {
        
        #line 133 "src/obdh/pus/services/service5.fin"
        status._variant = Status__Failure;
        #line 133 "src/obdh/pus/services/service5.fin"
        status.Failure._0._variant = PUSService5Error__EvIDNotValid;
        #line 133 "src/obdh/pus/services/service5.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->EvID;

    } else
    {
        
        #line 137 "src/obdh/pus/services/service5.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 142 "src/obdh/pus/services/service5.fin"
        const uint32_t mask = (uint32_t)0x1U << termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU));

        #line 143 "src/obdh/pus/services/service5.fin"
        self->Ev_ID_enable_config[config_slot - 1U] = self->Ev_ID_enable_config[config_slot - 1U] & (uint32_t)(0xFFFFFFFEU ^ mask);

        #line 145 "src/obdh/pus/services/service5.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    }

    #line 152 "src/obdh/pus/services/service5.fin"
    return status;

}

void CPUSService5__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 240 "src/obdh/pus/services/service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 240 "src/obdh/pus/services/service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 242 "src/obdh/pus/services/service5.fin"
    Status__PUSService5Error status = { ._variant = Status__Success };

    #line 243 "src/obdh/pus/services/service5.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 244 "src/obdh/pus/services/service5.fin"
    PS5TCRequest tc_request = { .EvID = 0U, .N = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 246 "src/obdh/pus/services/service5.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 247 "src/obdh/pus/services/service5.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 248 "src/obdh/pus/services/service5.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 249 "src/obdh/pus/services/service5.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 250 "src/obdh/pus/services/service5.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    #line 252 "src/obdh/pus/services/service5.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 253 "src/obdh/pus/services/service5.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.EvID);

    }

    #line 256 "src/obdh/pus/services/service5.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 257 "src/obdh/pus/services/service5.fin"
        status._variant = Status__Failure;
        #line 257 "src/obdh/pus/services/service5.fin"
        status.Failure._0._variant = PUSService5Error__AppDataOutOfRange;
        #line 257 "src/obdh/pus/services/service5.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 260 "src/obdh/pus/services/service5.fin"
    if (status._variant == Status__Success) {
        
        #line 262 "src/obdh/pus/services/service5.fin"
        if (subtype == 5U) {
            
            #line 264 "src/obdh/pus/services/service5.fin"
            status = CPUSService5__exec5_5TC(termina__ev, self, &tc_request);

        } else
        #line 266 "src/obdh/pus/services/service5.fin"
        if (subtype == 6U) {
            
            #line 268 "src/obdh/pus/services/service5.fin"
            status = CPUSService5__exec5_6TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 272 "src/obdh/pus/services/service5.fin"
            status._variant = Status__Failure;
            #line 272 "src/obdh/pus/services/service5.fin"
            status.Failure._0._variant = PUSService5Error__ErrorInAcceptance;

        }

    }

    #line 279 "src/obdh/pus/services/service5.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 282 "src/obdh/pus/services/service5.fin"
        const PUSService5Error error = status.Failure._0;

        #line 286 "src/obdh/pus/services/service5.fin"
        if (error._variant == PUSService5Error__ErrorInAcceptance) {
            
            #line 288 "src/obdh/pus/services/service5.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 293 "src/obdh/pus/services/service5.fin"
        if (error._variant == PUSService5Error__AppDataOutOfRange) {
            
            #line 293 "src/obdh/pus/services/service5.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 295 "src/obdh/pus/services/service5.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 301 "src/obdh/pus/services/service5.fin"
        if (error._variant == PUSService5Error__NumOfInstrNotValid) {
            
            #line 301 "src/obdh/pus/services/service5.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 303 "src/obdh/pus/services/service5.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        {
            
            #line 309 "src/obdh/pus/services/service5.fin"
            const uint16_t EvID = error.EvIDNotValid._0;

            #line 311 "src/obdh/pus/services/service5.fin"
            self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, EvID);

        }

    }

    #line 322 "src/obdh/pus/services/service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 322 "src/obdh/pus/services/service5.fin"
    return;

}

static _Bool CPUSService5__is_Ev_ID_enabled(const termina__event_t * const termina__ev, const CPUSService5 * const self, const uint16_t Ev_ID) {
    
    (void)termina__ev;

    #line 62 "src/obdh/pus/services/service5.fin"
    _Bool enabled = false;

    #line 63 "src/obdh/pus/services/service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(Ev_ID);

    #line 64 "src/obdh/pus/services/service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(Ev_ID);

    #line 66 "src/obdh/pus/services/service5.fin"
    if (config_slot != 0U) {
        
        #line 68 "src/obdh/pus/services/service5.fin"
        size_t config_array_index = config_slot - 1U;

        #line 69 "src/obdh/pus/services/service5.fin"
        if ((uint32_t)((uint32_t)(self->Ev_ID_enable_config[config_array_index] >> termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU))) & 0x1U) != 0U) {
            
            #line 70 "src/obdh/pus/services/service5.fin"
            enabled = true;

        }

    }

    #line 74 "src/obdh/pus/services/service5.fin"
    return enabled;

}

void CPUSService5__is_Ev_ID_enabled_ext(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t Ev_ID, _Bool * const p_enabled) {
    
    #line 77 "src/obdh/pus/services/service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 77 "src/obdh/pus/services/service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 79 "src/obdh/pus/services/service5.fin"
    *p_enabled = CPUSService5__is_Ev_ID_enabled(termina__ev, self, Ev_ID);

    #line 81 "src/obdh/pus/services/service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 81 "src/obdh/pus/services/service5.fin"
    return;

}

void CPUSService5__send_tm_5_2(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 156 "src/obdh/pus/services/service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 156 "src/obdh/pus/services/service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 158 "src/obdh/pus/services/service5.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 159 "src/obdh/pus/services/service5.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 163 "src/obdh/pus/services/service5.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 163 "src/obdh/pus/services/service5.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 165 "src/obdh/pus/services/service5.fin"
        startup_tm((TMHandler *)b_tm_handler.data);

        #line 166 "src/obdh/pus/services/service5.fin"
        const Status__TMHandlerError status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, 0x2100U);

        #line 168 "src/obdh/pus/services/service5.fin"
        if (status._variant == Status__Success) {
            
            #line 170 "src/obdh/pus/services/service5.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 171 "src/obdh/pus/services/service5.fin"
            uint16_t tm_count = 0U;

            #line 173 "src/obdh/pus/services/service5.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 174 "src/obdh/pus/services/service5.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 176 "src/obdh/pus/services/service5.fin"
            close_tm((TMHandler *)b_tm_handler.data, 5U, 2U, tm_count, current_obt);

            #line 178 "src/obdh/pus/services/service5.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 182 "src/obdh/pus/services/service5.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 183 "src/obdh/pus/services/service5.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 187 "src/obdh/pus/services/service5.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 191 "src/obdh/pus/services/service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 191 "src/obdh/pus/services/service5.fin"
    return;

}

void CPUSService5__send_tm_5_x(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID, const FaultInfo * const fault_info) {
    
    #line 195 "src/obdh/pus/services/service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 195 "src/obdh/pus/services/service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 197 "src/obdh/pus/services/service5.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 198 "src/obdh/pus/services/service5.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 202 "src/obdh/pus/services/service5.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 202 "src/obdh/pus/services/service5.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 204 "src/obdh/pus/services/service5.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 205 "src/obdh/pus/services/service5.fin"
        uint16_t tm_count = 0U;

        #line 207 "src/obdh/pus/services/service5.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 208 "src/obdh/pus/services/service5.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 210 "src/obdh/pus/services/service5.fin"
        Status__TMHandlerError status = { ._variant = Status__Success };

        #line 213 "src/obdh/pus/services/service5.fin"
        if ((*fault_info)._variant == FaultInfo__ParamOutOfLimit) {
            
            #line 213 "src/obdh/pus/services/service5.fin"
            const ParamOutOfLimitInfo fault_value_info = (*fault_info).ParamOutOfLimit._0;

            #line 214 "src/obdh/pus/services/service5.fin"
            status = build_tm_5_x_param_out_of_limit((TMHandler *)b_tm_handler.data, tm_count, fault_value_info, evID, current_obt);

        } else
        #line 216 "src/obdh/pus/services/service5.fin"
        if ((*fault_info)._variant == FaultInfo__ParamFaultValue) {
            
            #line 216 "src/obdh/pus/services/service5.fin"
            const ParamFaultValueInfo fault_value_info = (*fault_info).ParamFaultValue._0;

            #line 217 "src/obdh/pus/services/service5.fin"
            status = build_tm_5_x_param_check_value_fail((TMHandler *)b_tm_handler.data, tm_count, fault_value_info, evID, current_obt);

        } else
        {
            

        }

        #line 224 "src/obdh/pus/services/service5.fin"
        if (status._variant == Status__Success) {
            
            #line 225 "src/obdh/pus/services/service5.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 227 "src/obdh/pus/services/service5.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 228 "src/obdh/pus/services/service5.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 233 "src/obdh/pus/services/service5.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 237 "src/obdh/pus/services/service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 237 "src/obdh/pus/services/service5.fin"
    return;

}
