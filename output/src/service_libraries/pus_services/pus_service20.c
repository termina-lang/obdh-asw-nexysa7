
#include "service_libraries/pus_services/pus_service20.h"

static Status__i32 CPUSService20__exec20_1TC(const termina__event_t * const termina__ev, CPUSService20 * const self);

static Status__i32 CPUSService20__exec20_3TC(const termina__event_t * const termina__ev, CPUSService20 * const self);

static Status__i32 CPUSService20__exec20_1TC(const termina__event_t * const termina__ev, CPUSService20 * const self) {
    
    #line 28 "src/service_libraries/pus_services/pus_service20.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 30 "src/service_libraries/pus_services/pus_service20.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 32 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 38 "src/service_libraries/pus_services/pus_service20.fin"
    if (sys_data_pool_is_valid_PID(self->exec_tc_req_status_update.PID) == false) {
        
        #line 40 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

    } else
    {
        
        #line 48 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 54 "src/service_libraries/pus_services/pus_service20.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 55 "src/service_libraries/pus_services/pus_service20.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 59 "src/service_libraries/pus_services/pus_service20.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 59 "src/service_libraries/pus_services/pus_service20.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 61 "src/service_libraries/pus_services/pus_service20.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 62 "src/service_libraries/pus_services/pus_service20.fin"
            uint16_t tm_count = 0U;

            #line 64 "src/service_libraries/pus_services/pus_service20.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 66 "src/service_libraries/pus_services/pus_service20.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 68 "src/service_libraries/pus_services/pus_service20.fin"
            status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, 1U);

            #line 70 "src/service_libraries/pus_services/pus_service20.fin"
            if (status._variant == Status__Success) {
                
                #line 71 "src/service_libraries/pus_services/pus_service20.fin"
                status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, (uint16_t)self->exec_tc_req_status_update.PID);

            }

            #line 74 "src/service_libraries/pus_services/pus_service20.fin"
            if (status._variant == Status__Success) {
                
                #line 75 "src/service_libraries/pus_services/pus_service20.fin"
                DataPoolItemType item_type = sys_data_pool_get_item_type(self->exec_tc_req_status_update.PID);

                #line 78 "src/service_libraries/pus_services/pus_service20.fin"
                if (item_type._variant == DataPoolItemType__u8_t) {
                    
                    #line 79 "src/service_libraries/pus_services/pus_service20.fin"
                    uint8_t u8_SDP_value = 0U;

                    #line 80 "src/service_libraries/pus_services/pus_service20.fin"
                    u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)self->exec_tc_req_status_update.PID)]);

                    #line 81 "src/service_libraries/pus_services/pus_service20.fin"
                    status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, u8_SDP_value);

                } else
                #line 83 "src/service_libraries/pus_services/pus_service20.fin"
                if (item_type._variant == DataPoolItemType__u32_t) {
                    
                    #line 84 "src/service_libraries/pus_services/pus_service20.fin"
                    uint32_t u32_SDP_value = 0U;

                    #line 85 "src/service_libraries/pus_services/pus_service20.fin"
                    u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)self->exec_tc_req_status_update.PID)]);

                    #line 86 "src/service_libraries/pus_services/pus_service20.fin"
                    status = append_u32_appdata_field((TMHandler *)b_tm_handler.data, u32_SDP_value);

                } else
                {
                    
                    #line 89 "src/service_libraries/pus_services/pus_service20.fin"
                    status._variant = Status__Failure;
                    #line 89 "src/service_libraries/pus_services/pus_service20.fin"
                    status.Failure._0 = 10L;

                }

            }

            #line 94 "src/service_libraries/pus_services/pus_service20.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 96 "src/service_libraries/pus_services/pus_service20.fin"
            if (status._variant == Status__Success) {
                
                #line 97 "src/service_libraries/pus_services/pus_service20.fin"
                close_tm((TMHandler *)b_tm_handler.data, 20U, 2U, tm_count, current_obt);

                #line 98 "src/service_libraries/pus_services/pus_service20.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &status);

            } else
            {
                
                #line 100 "src/service_libraries/pus_services/pus_service20.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            }

        } else
        {
            
            #line 106 "src/service_libraries/pus_services/pus_service20.fin"
            status._variant = Status__Failure;
            #line 106 "src/service_libraries/pus_services/pus_service20.fin"
            status.Failure._0 = 1L;

        }

        #line 111 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    }

    #line 119 "src/service_libraries/pus_services/pus_service20.fin"
    return status;

}

static Status__i32 CPUSService20__exec20_3TC(const termina__event_t * const termina__ev, CPUSService20 * const self) {
    
    #line 126 "src/service_libraries/pus_services/pus_service20.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 128 "src/service_libraries/pus_services/pus_service20.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 130 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 136 "src/service_libraries/pus_services/pus_service20.fin"
    if (sys_data_pool_is_valid_PID(self->exec_tc_req_status_update.PID) == false) {
        
        #line 138 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

    } else
    #line 144 "src/service_libraries/pus_services/pus_service20.fin"
    if (sys_data_pool_is_PID_update_via_TC_enabled(self->exec_tc_req_status_update.PID) == false) {
        
        #line 146 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.send_tm_1_4_PID_read_only_via_TC(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

    } else
    {
        
        #line 154 "src/service_libraries/pus_services/pus_service20.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 160 "src/service_libraries/pus_services/pus_service20.fin"
        if (status._variant == Status__Success) {
            
            #line 162 "src/service_libraries/pus_services/pus_service20.fin"
            DataPoolItemType item_type = sys_data_pool_get_item_type(self->exec_tc_req_status_update.PID);

            #line 165 "src/service_libraries/pus_services/pus_service20.fin"
            if (item_type._variant == DataPoolItemType__u8_t) {
                
                #line 166 "src/service_libraries/pus_services/pus_service20.fin"
                atomic_store(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)self->exec_tc_req_status_update.PID - 11U)], self->exec_tc_req_status_update.tc_20_3_data.PID_value_u8);

            } else
            #line 168 "src/service_libraries/pus_services/pus_service20.fin"
            if (item_type._variant == DataPoolItemType__u32_t) {
                
                #line 169 "src/service_libraries/pus_services/pus_service20.fin"
                atomic_store(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)self->exec_tc_req_status_update.PID - 0U)], self->exec_tc_req_status_update.tc_20_3_data.PID_value_u32);

            } else
            {
                
                #line 172 "src/service_libraries/pus_services/pus_service20.fin"
                status._variant = Status__Failure;
                #line 172 "src/service_libraries/pus_services/pus_service20.fin"
                status.Failure._0 = 10L;

            }

        }

        #line 178 "src/service_libraries/pus_services/pus_service20.fin"
        if (status._variant == Status__Success) {
            
            #line 180 "src/service_libraries/pus_services/pus_service20.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        }

    }

    #line 190 "src/service_libraries/pus_services/pus_service20.fin"
    return status;

}

void CPUSService20__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 194 "src/service_libraries/pus_services/pus_service20.fin"
    CPUSService20 * self = (CPUSService20 *)termina__this;

    #line 194 "src/service_libraries/pus_services/pus_service20.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 196 "src/service_libraries/pus_services/pus_service20.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 198 "src/service_libraries/pus_services/pus_service20.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 199 "src/service_libraries/pus_services/pus_service20.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 200 "src/service_libraries/pus_services/pus_service20.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 201 "src/service_libraries/pus_services/pus_service20.fin"
    self->exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 203 "src/service_libraries/pus_services/pus_service20.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.N);

    #line 205 "src/service_libraries/pus_services/pus_service20.fin"
    if (status._variant == Status__Success) {
        
        #line 206 "src/service_libraries/pus_services/pus_service20.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.PID);

    }

    #line 209 "src/service_libraries/pus_services/pus_service20.fin"
    if (status._variant == Status__Success && subtype == 3U) {
        
        #line 211 "src/service_libraries/pus_services/pus_service20.fin"
        DataPoolItemType item_type = sys_data_pool_get_item_type(self->exec_tc_req_status_update.PID);

        #line 214 "src/service_libraries/pus_services/pus_service20.fin"
        if (item_type._variant == DataPoolItemType__u8_t) {
            
            #line 215 "src/service_libraries/pus_services/pus_service20.fin"
            status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.tc_20_3_data.PID_value_u8);

        } else
        #line 217 "src/service_libraries/pus_services/pus_service20.fin"
        if (item_type._variant == DataPoolItemType__u32_t) {
            
            #line 218 "src/service_libraries/pus_services/pus_service20.fin"
            status = tc_handler_get_u32_appdata_field(tc_handler, &self->exec_tc_req_status_update.tc_20_3_data.PID_value_u32);

        } else
        {
            
            #line 221 "src/service_libraries/pus_services/pus_service20.fin"
            status._variant = Status__Failure;
            #line 221 "src/service_libraries/pus_services/pus_service20.fin"
            status.Failure._0 = 10L;

        }

    }

    #line 227 "src/service_libraries/pus_services/pus_service20.fin"
    if (status._variant == Status__Success) {
        
        #line 229 "src/service_libraries/pus_services/pus_service20.fin"
        if (subtype == 1U) {
            
            #line 231 "src/service_libraries/pus_services/pus_service20.fin"
            status = CPUSService20__exec20_1TC(termina__ev, self);

        } else
        #line 233 "src/service_libraries/pus_services/pus_service20.fin"
        if (subtype == 3U) {
            
            #line 235 "src/service_libraries/pus_services/pus_service20.fin"
            status = CPUSService20__exec20_3TC(termina__ev, self);

        } else
        {
            
            #line 239 "src/service_libraries/pus_services/pus_service20.fin"
            status._variant = Status__Failure;
            #line 239 "src/service_libraries/pus_services/pus_service20.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 247 "src/service_libraries/pus_services/pus_service20.fin"
    if (status._variant == Status__Success) {
        
        #line 249 "src/service_libraries/pus_services/pus_service20.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 252 "src/service_libraries/pus_services/pus_service20.fin"
        const int32_t error_code = status.Failure._0;

        #line 254 "src/service_libraries/pus_services/pus_service20.fin"
        if (error_code == 4L) {
            
            #line 256 "src/service_libraries/pus_services/pus_service20.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 261 "src/service_libraries/pus_services/pus_service20.fin"
        if (error_code == 3L) {
            
            #line 263 "src/service_libraries/pus_services/pus_service20.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 268 "src/service_libraries/pus_services/pus_service20.fin"
        if (error_code == 5L) {
            
            #line 270 "src/service_libraries/pus_services/pus_service20.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        #line 276 "src/service_libraries/pus_services/pus_service20.fin"
        if (error_code == 10L) {
            
            #line 278 "src/service_libraries/pus_services/pus_service20.fin"
            self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, action_status);

        } else
        {
            
            #line 285 "src/service_libraries/pus_services/pus_service20.fin"
            (*action_status)._variant = Status__Failure;
            #line 285 "src/service_libraries/pus_services/pus_service20.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 291 "src/service_libraries/pus_services/pus_service20.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 291 "src/service_libraries/pus_services/pus_service20.fin"
    return;

}
