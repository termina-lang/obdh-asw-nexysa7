
#include "service_libraries/pus_services/pus_service5.h"

static Status__i32 CPUSService5__exec5_5TC(const termina__event_t * const termina__ev, CPUSService5 * const self);

static Status__i32 CPUSService5__exec5_6TC(const termina__event_t * const termina__ev, CPUSService5 * const self);

static _Bool CPUSService5__is_Ev_ID_enabled(const termina__event_t * const termina__ev, const CPUSService5 * const self, const uint16_t Ev_ID);

static Status__i32 CPUSService5__exec5_5TC(const termina__event_t * const termina__ev, CPUSService5 * const self) {
    
    #line 88 "src/service_libraries/pus_services/pus_service5.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 90 "src/service_libraries/pus_services/pus_service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(self->exec_tc_req_status_update.EvID);

    #line 91 "src/service_libraries/pus_services/pus_service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(self->exec_tc_req_status_update.EvID);

    #line 93 "src/service_libraries/pus_services/pus_service5.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 95 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 100 "src/service_libraries/pus_services/pus_service5.fin"
    if (config_slot == 0U) {
        
        #line 102 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.EvID, &status);

    } else
    {
        
        #line 109 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 115 "src/service_libraries/pus_services/pus_service5.fin"
        if (status._variant == Status__Success) {
            
            #line 117 "src/service_libraries/pus_services/pus_service5.fin"
            const uint32_t mask = (uint32_t)0x1U << termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU));

            #line 118 "src/service_libraries/pus_services/pus_service5.fin"
            self->Ev_ID_enable_config[config_slot - 1U] = self->Ev_ID_enable_config[config_slot - 1U] | mask;

            #line 120 "src/service_libraries/pus_services/pus_service5.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        }

    }

    #line 130 "src/service_libraries/pus_services/pus_service5.fin"
    return status;

}

static Status__i32 CPUSService5__exec5_6TC(const termina__event_t * const termina__ev, CPUSService5 * const self) {
    
    #line 136 "src/service_libraries/pus_services/pus_service5.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 138 "src/service_libraries/pus_services/pus_service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(self->exec_tc_req_status_update.EvID);

    #line 139 "src/service_libraries/pus_services/pus_service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(self->exec_tc_req_status_update.EvID);

    #line 141 "src/service_libraries/pus_services/pus_service5.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 143 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 148 "src/service_libraries/pus_services/pus_service5.fin"
    if (config_slot == 0U) {
        
        #line 150 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.EvID, &status);

    } else
    {
        
        #line 158 "src/service_libraries/pus_services/pus_service5.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 164 "src/service_libraries/pus_services/pus_service5.fin"
        if (status._variant == Status__Success) {
            
            #line 166 "src/service_libraries/pus_services/pus_service5.fin"
            const uint32_t mask = (uint32_t)0x1U << termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU));

            #line 167 "src/service_libraries/pus_services/pus_service5.fin"
            self->Ev_ID_enable_config[config_slot - 1U] = self->Ev_ID_enable_config[config_slot - 1U] & (uint32_t)(0xFFFFFFFEU ^ mask);

            #line 169 "src/service_libraries/pus_services/pus_service5.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        }

    }

    #line 178 "src/service_libraries/pus_services/pus_service5.fin"
    return status;

}

void CPUSService5__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 262 "src/service_libraries/pus_services/pus_service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 262 "src/service_libraries/pus_services/pus_service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 264 "src/service_libraries/pus_services/pus_service5.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 266 "src/service_libraries/pus_services/pus_service5.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 267 "src/service_libraries/pus_services/pus_service5.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 268 "src/service_libraries/pus_services/pus_service5.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 269 "src/service_libraries/pus_services/pus_service5.fin"
    self->exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 270 "src/service_libraries/pus_services/pus_service5.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.N);

    #line 272 "src/service_libraries/pus_services/pus_service5.fin"
    if (status._variant == Status__Success) {
        
        #line 273 "src/service_libraries/pus_services/pus_service5.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.EvID);

    }

    #line 276 "src/service_libraries/pus_services/pus_service5.fin"
    if (status._variant == Status__Success) {
        
        #line 278 "src/service_libraries/pus_services/pus_service5.fin"
        if (subtype == 5U) {
            
            #line 280 "src/service_libraries/pus_services/pus_service5.fin"
            status = CPUSService5__exec5_5TC(termina__ev, self);

        } else
        #line 282 "src/service_libraries/pus_services/pus_service5.fin"
        if (subtype == 6U) {
            
            #line 284 "src/service_libraries/pus_services/pus_service5.fin"
            status = CPUSService5__exec5_6TC(termina__ev, self);

        } else
        {
            
            #line 288 "src/service_libraries/pus_services/pus_service5.fin"
            status._variant = Status__Failure;
            #line 288 "src/service_libraries/pus_services/pus_service5.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 295 "src/service_libraries/pus_services/pus_service5.fin"
    if (status._variant == Status__Success) {
        
        #line 297 "src/service_libraries/pus_services/pus_service5.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 300 "src/service_libraries/pus_services/pus_service5.fin"
        const int32_t error_code = status.Failure._0;

        #line 302 "src/service_libraries/pus_services/pus_service5.fin"
        if (error_code == 4L) {
            
            #line 304 "src/service_libraries/pus_services/pus_service5.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 309 "src/service_libraries/pus_services/pus_service5.fin"
        if (error_code == 3L) {
            
            #line 311 "src/service_libraries/pus_services/pus_service5.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 316 "src/service_libraries/pus_services/pus_service5.fin"
        if (error_code == 5L) {
            
            #line 318 "src/service_libraries/pus_services/pus_service5.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        {
            
            #line 326 "src/service_libraries/pus_services/pus_service5.fin"
            (*action_status)._variant = Status__Failure;
            #line 326 "src/service_libraries/pus_services/pus_service5.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 333 "src/service_libraries/pus_services/pus_service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 333 "src/service_libraries/pus_services/pus_service5.fin"
    return;

}

static _Bool CPUSService5__is_Ev_ID_enabled(const termina__event_t * const termina__ev, const CPUSService5 * const self, const uint16_t Ev_ID) {
    
    (void)termina__ev;

    #line 64 "src/service_libraries/pus_services/pus_service5.fin"
    _Bool enabled = false;

    #line 65 "src/service_libraries/pus_services/pus_service5.fin"
    size_t config_slot = get_Ev_ID_enable_config_index(Ev_ID);

    #line 66 "src/service_libraries/pus_services/pus_service5.fin"
    uint8_t offset = get_Ev_ID_enable_config_offset(Ev_ID);

    #line 68 "src/service_libraries/pus_services/pus_service5.fin"
    if (config_slot != 0U) {
        
        #line 70 "src/service_libraries/pus_services/pus_service5.fin"
        size_t config_array_index = config_slot - 1U;

        #line 71 "src/service_libraries/pus_services/pus_service5.fin"
        if ((uint32_t)((uint32_t)(self->Ev_ID_enable_config[config_array_index] >> termina__check__shift_amount(32U, (uint8_t)((offset - 1U) & 0xFFU))) & 0x1U) != 0U) {
            
            #line 72 "src/service_libraries/pus_services/pus_service5.fin"
            enabled = true;

        }

    }

    #line 76 "src/service_libraries/pus_services/pus_service5.fin"
    return enabled;

}

void CPUSService5__is_Ev_ID_enabled_ext(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t Ev_ID, _Bool * const p_enabled) {
    
    #line 79 "src/service_libraries/pus_services/pus_service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 79 "src/service_libraries/pus_services/pus_service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 81 "src/service_libraries/pus_services/pus_service5.fin"
    *p_enabled = CPUSService5__is_Ev_ID_enabled(termina__ev, self, Ev_ID);

    #line 83 "src/service_libraries/pus_services/pus_service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 83 "src/service_libraries/pus_services/pus_service5.fin"
    return;

}

void CPUSService5__send_tm_5_2(const termina__event_t * const termina__ev, void * const termina__this, Status__i32 * const status) {
    
    #line 182 "src/service_libraries/pus_services/pus_service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 182 "src/service_libraries/pus_services/pus_service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 184 "src/service_libraries/pus_services/pus_service5.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 185 "src/service_libraries/pus_services/pus_service5.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 189 "src/service_libraries/pus_services/pus_service5.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 189 "src/service_libraries/pus_services/pus_service5.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 191 "src/service_libraries/pus_services/pus_service5.fin"
        startup_tm((TMHandler *)b_tm_handler.data);

        #line 192 "src/service_libraries/pus_services/pus_service5.fin"
        *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, 0x2100U);

        #line 194 "src/service_libraries/pus_services/pus_service5.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 196 "src/service_libraries/pus_services/pus_service5.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 197 "src/service_libraries/pus_services/pus_service5.fin"
            uint16_t tm_count = 0U;

            #line 199 "src/service_libraries/pus_services/pus_service5.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 200 "src/service_libraries/pus_services/pus_service5.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 202 "src/service_libraries/pus_services/pus_service5.fin"
            close_tm((TMHandler *)b_tm_handler.data, 5U, 2U, tm_count, current_obt);

            #line 204 "src/service_libraries/pus_services/pus_service5.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 208 "src/service_libraries/pus_services/pus_service5.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 212 "src/service_libraries/pus_services/pus_service5.fin"
        (*status)._variant = Status__Failure;
        #line 212 "src/service_libraries/pus_services/pus_service5.fin"
        (*status).Failure._0 = 1L;

    }

    #line 216 "src/service_libraries/pus_services/pus_service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 216 "src/service_libraries/pus_services/pus_service5.fin"
    return;

}

void CPUSService5__send_tm_5_x(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID, const FaultInfo * const fault_info, Status__i32 * const status) {
    
    #line 220 "src/service_libraries/pus_services/pus_service5.fin"
    CPUSService5 * self = (CPUSService5 *)termina__this;

    #line 220 "src/service_libraries/pus_services/pus_service5.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 222 "src/service_libraries/pus_services/pus_service5.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 223 "src/service_libraries/pus_services/pus_service5.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 227 "src/service_libraries/pus_services/pus_service5.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 227 "src/service_libraries/pus_services/pus_service5.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 229 "src/service_libraries/pus_services/pus_service5.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 230 "src/service_libraries/pus_services/pus_service5.fin"
        uint16_t tm_count = 0U;

        #line 232 "src/service_libraries/pus_services/pus_service5.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 233 "src/service_libraries/pus_services/pus_service5.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 236 "src/service_libraries/pus_services/pus_service5.fin"
        if ((*fault_info)._variant == FaultInfo__ParamOutOfLimit) {
            
            #line 236 "src/service_libraries/pus_services/pus_service5.fin"
            const ParamOutOfLimitInfo fault_value_info = (*fault_info).ParamOutOfLimit._0;

            #line 237 "src/service_libraries/pus_services/pus_service5.fin"
            *status = build_tm_5_x_param_out_of_limit((TMHandler *)b_tm_handler.data, tm_count, fault_value_info, evID, current_obt);

        } else
        #line 239 "src/service_libraries/pus_services/pus_service5.fin"
        if ((*fault_info)._variant == FaultInfo__ParamFaultValue) {
            
            #line 239 "src/service_libraries/pus_services/pus_service5.fin"
            const ParamFaultValueInfo fault_value_info = (*fault_info).ParamFaultValue._0;

            #line 240 "src/service_libraries/pus_services/pus_service5.fin"
            *status = build_tm_5_x_param_check_value_fail((TMHandler *)b_tm_handler.data, tm_count, fault_value_info, evID, current_obt);

        } else
        {
            

        }

        #line 247 "src/service_libraries/pus_services/pus_service5.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 248 "src/service_libraries/pus_services/pus_service5.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 250 "src/service_libraries/pus_services/pus_service5.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 255 "src/service_libraries/pus_services/pus_service5.fin"
        (*status)._variant = Status__Failure;
        #line 255 "src/service_libraries/pus_services/pus_service5.fin"
        (*status).Failure._0 = 1L;

    }

    #line 259 "src/service_libraries/pus_services/pus_service5.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 259 "src/service_libraries/pus_services/pus_service5.fin"
    return;

}
