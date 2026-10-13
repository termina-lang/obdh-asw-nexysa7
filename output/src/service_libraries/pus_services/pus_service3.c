
#include "service_libraries/pus_services/pus_service3.h"

static Option__usize CPUSService3__get_SIDindex(const termina__event_t * const termina__ev, const CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update);

static Status__i32 CPUSService3__exec3_31TC(const termina__event_t * const termina__ev, CPUSService3 * const self, PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update);

static Status__i32 CPUSService3__exec3_5TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update);

static Status__i32 CPUSService3__exec3_6TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update);

void CPUSService3__do_hk(const termina__event_t * const termina__ev, void * const termina__this, Status__i32 * const action_status) {
    
    #line 312 "src/service_libraries/pus_services/pus_service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 312 "src/service_libraries/pus_services/pus_service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 314 "src/service_libraries/pus_services/pus_service3.fin"
    for (size_t i = 0U; i < 8U && (*action_status)._variant == Status__Success; i = i + 1U) {
        
        #line 316 "src/service_libraries/pus_services/pus_service3.fin"
        if (self->hk_config_table[i].enabled == true) {
            
            #line 318 "src/service_libraries/pus_services/pus_service3.fin"
            self->hk_config_table[i].interval_control = self->hk_config_table[i].interval_control + 1U;

            #line 320 "src/service_libraries/pus_services/pus_service3.fin"
            if (self->hk_config_table[i].interval_control >= self->hk_config_table[i].interval) {
                
                #line 322 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[i].interval_control = 0U;

                #line 324 "src/service_libraries/pus_services/pus_service3.fin"
                Option__box tm_handler = { ._variant = Option__None };

                #line 325 "src/service_libraries/pus_services/pus_service3.fin"
                self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

                #line 329 "src/service_libraries/pus_services/pus_service3.fin"
                if (tm_handler._variant == Option__Some) {
                    
                    #line 329 "src/service_libraries/pus_services/pus_service3.fin"
                    const termina__box_t b_tm_handler = tm_handler.Some._0;

                    #line 331 "src/service_libraries/pus_services/pus_service3.fin"
                    uint16_t tm_count = 0U;

                    #line 332 "src/service_libraries/pus_services/pus_service3.fin"
                    self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

                    #line 334 "src/service_libraries/pus_services/pus_service3.fin"
                    startup_tm((TMHandler *)b_tm_handler.data);

                    #line 335 "src/service_libraries/pus_services/pus_service3.fin"
                    Status__i32 do_hk_status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, self->hk_config_table[i].SID);

                    #line 337 "src/service_libraries/pus_services/pus_service3.fin"
                    size_t num_params = (size_t)self->hk_config_table[i].num_params;

                    #line 339 "src/service_libraries/pus_services/pus_service3.fin"
                    for (size_t j = 0U; j < 16U && (j < num_params && do_hk_status._variant == Status__Success); j = j + 1U) {
                        
                        #line 341 "src/service_libraries/pus_services/pus_service3.fin"
                        uint16_t PID = self->hk_config_table[i].params_def[j];

                        #line 342 "src/service_libraries/pus_services/pus_service3.fin"
                        DataPoolItemType item_type = sys_data_pool_get_item_type(PID);

                        #line 345 "src/service_libraries/pus_services/pus_service3.fin"
                        if (item_type._variant == DataPoolItemType__u8_t) {
                            
                            #line 346 "src/service_libraries/pus_services/pus_service3.fin"
                            uint8_t u8_SDP_value = 0U;

                            #line 347 "src/service_libraries/pus_services/pus_service3.fin"
                            u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)PID)]);

                            #line 348 "src/service_libraries/pus_services/pus_service3.fin"
                            do_hk_status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, u8_SDP_value);

                        } else
                        #line 350 "src/service_libraries/pus_services/pus_service3.fin"
                        if (item_type._variant == DataPoolItemType__u32_t) {
                            
                            #line 351 "src/service_libraries/pus_services/pus_service3.fin"
                            uint32_t u32_SDP_value = 0U;

                            #line 352 "src/service_libraries/pus_services/pus_service3.fin"
                            u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)PID)]);

                            #line 353 "src/service_libraries/pus_services/pus_service3.fin"
                            do_hk_status = append_u32_appdata_field((TMHandler *)b_tm_handler.data, u32_SDP_value);

                        } else
                        {
                            
                            #line 356 "src/service_libraries/pus_services/pus_service3.fin"
                            do_hk_status._variant = Status__Failure;
                            #line 356 "src/service_libraries/pus_services/pus_service3.fin"
                            do_hk_status.Failure._0 = 9L;

                        }

                    }

                    #line 362 "src/service_libraries/pus_services/pus_service3.fin"
                    MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

                    #line 363 "src/service_libraries/pus_services/pus_service3.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

                    #line 365 "src/service_libraries/pus_services/pus_service3.fin"
                    if (do_hk_status._variant == Status__Success) {
                        
                        #line 366 "src/service_libraries/pus_services/pus_service3.fin"
                        close_tm((TMHandler *)b_tm_handler.data, 3U, 25U, tm_count, current_obt);

                        #line 367 "src/service_libraries/pus_services/pus_service3.fin"
                        self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &do_hk_status);

                    } else
                    {
                        
                        #line 371 "src/service_libraries/pus_services/pus_service3.fin"
                        self->pus_service_5.send_tm_5_2(termina__ev, self->pus_service_5._that, &do_hk_status);

                        #line 372 "src/service_libraries/pus_services/pus_service3.fin"
                        self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                    }

                } else
                {
                    
                    #line 378 "src/service_libraries/pus_services/pus_service3.fin"
                    (*action_status)._variant = Status__Failure;
                    #line 378 "src/service_libraries/pus_services/pus_service3.fin"
                    (*action_status).Failure._0 = 1L;

                }

            }

        }

    }

    #line 386 "src/service_libraries/pus_services/pus_service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 386 "src/service_libraries/pus_services/pus_service3.fin"
    return;

}

static Option__usize CPUSService3__get_SIDindex(const termina__event_t * const termina__ev, const CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    (void)termina__ev;

    #line 37 "src/service_libraries/pus_services/pus_service3.fin"
    Option__usize index_found = { ._variant = Option__None };

    #line 39 "src/service_libraries/pus_services/pus_service3.fin"
    for (size_t i = 0U; i < 8U && index_found._variant == Option__None; i = i + 1U) {
        
        #line 41 "src/service_libraries/pus_services/pus_service3.fin"
        if (exec_tc_req_status_update->SID == self->hk_config_table[i].SID) {
            
            #line 43 "src/service_libraries/pus_services/pus_service3.fin"
            index_found._variant = Option__Some;
            #line 43 "src/service_libraries/pus_services/pus_service3.fin"
            index_found.Some._0 = i;

        }

    }

    #line 47 "src/service_libraries/pus_services/pus_service3.fin"
    return index_found;

}

static Status__i32 CPUSService3__exec3_31TC(const termina__event_t * const termina__ev, CPUSService3 * const self, PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    #line 168 "src/service_libraries/pus_services/pus_service3.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 170 "src/service_libraries/pus_services/pus_service3.fin"
    if (exec_tc_req_status_update->N != 1U) {
        
        #line 172 "src/service_libraries/pus_services/pus_service3.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->N, &status);

    } else
    {
        
        #line 180 "src/service_libraries/pus_services/pus_service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, exec_tc_req_status_update);

        #line 184 "src/service_libraries/pus_services/pus_service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 184 "src/service_libraries/pus_services/pus_service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 186 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            #line 192 "src/service_libraries/pus_services/pus_service3.fin"
            if (status._variant == Status__Success) {
                
                #line 194 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].interval = exec_tc_req_status_update->collection_interval;

                #line 195 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

                #line 197 "src/service_libraries/pus_services/pus_service3.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            }

        } else
        {
            
            #line 208 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_4_SID_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->SID, &status);

        }

    }

    #line 220 "src/service_libraries/pus_services/pus_service3.fin"
    return status;

}

static Status__i32 CPUSService3__exec3_5TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    #line 52 "src/service_libraries/pus_services/pus_service3.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 54 "src/service_libraries/pus_services/pus_service3.fin"
    if (exec_tc_req_status_update->N != 1U) {
        
        #line 56 "src/service_libraries/pus_services/pus_service3.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->N, &status);

    } else
    {
        
        #line 64 "src/service_libraries/pus_services/pus_service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, exec_tc_req_status_update);

        #line 68 "src/service_libraries/pus_services/pus_service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 68 "src/service_libraries/pus_services/pus_service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 70 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            #line 76 "src/service_libraries/pus_services/pus_service3.fin"
            if (status._variant == Status__Success) {
                
                #line 78 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].enabled = true;

                #line 79 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

                #line 81 "src/service_libraries/pus_services/pus_service3.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            }

        } else
        {
            
            #line 93 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_4_SID_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->SID, &status);

        }

    }

    #line 105 "src/service_libraries/pus_services/pus_service3.fin"
    return status;

}

static Status__i32 CPUSService3__exec3_6TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    #line 110 "src/service_libraries/pus_services/pus_service3.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 112 "src/service_libraries/pus_services/pus_service3.fin"
    if (exec_tc_req_status_update->N != 1U) {
        
        #line 114 "src/service_libraries/pus_services/pus_service3.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->N, &status);

    } else
    {
        
        #line 122 "src/service_libraries/pus_services/pus_service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, exec_tc_req_status_update);

        #line 126 "src/service_libraries/pus_services/pus_service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 126 "src/service_libraries/pus_services/pus_service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 128 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            #line 134 "src/service_libraries/pus_services/pus_service3.fin"
            if (status._variant == Status__Success) {
                
                #line 136 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].enabled = false;

                #line 137 "src/service_libraries/pus_services/pus_service3.fin"
                self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

                #line 139 "src/service_libraries/pus_services/pus_service3.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            }

        } else
        {
            
            #line 151 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_4_SID_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->SID, &status);

        }

    }

    #line 162 "src/service_libraries/pus_services/pus_service3.fin"
    return status;

}

void CPUSService3__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 225 "src/service_libraries/pus_services/pus_service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 225 "src/service_libraries/pus_services/pus_service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 227 "src/service_libraries/pus_services/pus_service3.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 228 "src/service_libraries/pus_services/pus_service3.fin"
    PS3ExecTCReqStatusUpdate exec_tc_req_status_update = { .N = 0U, .SID = 0U, .collection_interval = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 230 "src/service_libraries/pus_services/pus_service3.fin"
    exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 231 "src/service_libraries/pus_services/pus_service3.fin"
    exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 232 "src/service_libraries/pus_services/pus_service3.fin"
    exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 233 "src/service_libraries/pus_services/pus_service3.fin"
    exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 235 "src/service_libraries/pus_services/pus_service3.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &exec_tc_req_status_update.N);

    #line 237 "src/service_libraries/pus_services/pus_service3.fin"
    if (status._variant == Status__Success) {
        
        #line 238 "src/service_libraries/pus_services/pus_service3.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &exec_tc_req_status_update.SID);

    }

    #line 241 "src/service_libraries/pus_services/pus_service3.fin"
    if (status._variant == Status__Success && subtype == 31U) {
        
        #line 242 "src/service_libraries/pus_services/pus_service3.fin"
        status = tc_handler_get_u8_appdata_field(tc_handler, &exec_tc_req_status_update.collection_interval);

    }

    #line 245 "src/service_libraries/pus_services/pus_service3.fin"
    if (status._variant == Status__Success) {
        
        #line 247 "src/service_libraries/pus_services/pus_service3.fin"
        if (subtype == 5U) {
            
            #line 249 "src/service_libraries/pus_services/pus_service3.fin"
            status = CPUSService3__exec3_5TC(termina__ev, self, &exec_tc_req_status_update);

        } else
        #line 251 "src/service_libraries/pus_services/pus_service3.fin"
        if (subtype == 6U) {
            
            #line 253 "src/service_libraries/pus_services/pus_service3.fin"
            status = CPUSService3__exec3_6TC(termina__ev, self, &exec_tc_req_status_update);

        } else
        #line 255 "src/service_libraries/pus_services/pus_service3.fin"
        if (subtype == 31U) {
            
            #line 257 "src/service_libraries/pus_services/pus_service3.fin"
            status = CPUSService3__exec3_31TC(termina__ev, self, &exec_tc_req_status_update);

        } else
        {
            
            #line 261 "src/service_libraries/pus_services/pus_service3.fin"
            status._variant = Status__Failure;
            #line 261 "src/service_libraries/pus_services/pus_service3.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 269 "src/service_libraries/pus_services/pus_service3.fin"
    if (status._variant == Status__Success) {
        
        #line 271 "src/service_libraries/pus_services/pus_service3.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 274 "src/service_libraries/pus_services/pus_service3.fin"
        const int32_t error_code = status.Failure._0;

        #line 277 "src/service_libraries/pus_services/pus_service3.fin"
        if (error_code == 4L) {
            
            #line 279 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 284 "src/service_libraries/pus_services/pus_service3.fin"
        if (error_code == 3L) {
            
            #line 286 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 291 "src/service_libraries/pus_services/pus_service3.fin"
        if (error_code == 5L) {
            
            #line 293 "src/service_libraries/pus_services/pus_service3.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        {
            
            #line 301 "src/service_libraries/pus_services/pus_service3.fin"
            (*action_status)._variant = Status__Failure;
            #line 301 "src/service_libraries/pus_services/pus_service3.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 308 "src/service_libraries/pus_services/pus_service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 308 "src/service_libraries/pus_services/pus_service3.fin"
    return;

}

void CPUSService3__update_params(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 389 "src/service_libraries/pus_services/pus_service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 389 "src/service_libraries/pus_services/pus_service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 391 "src/service_libraries/pus_services/pus_service3.fin"
    for (size_t i = 0U; i < 5U; i = i + 1U) {
        
        #line 393 "src/service_libraries/pus_services/pus_service3.fin"
        uint32_t random_noise = (uint32_t)(rand_r(&self->random_seed) % 11U) - 5U;

        #line 394 "src/service_libraries/pus_services/pus_service3.fin"
        uint32_t data = 0U;

        #line 396 "src/service_libraries/pus_services/pus_service3.fin"
        data = atomic_load(&self->system_data_pool_u32[i]);

        #line 397 "src/service_libraries/pus_services/pus_service3.fin"
        data = data + random_noise;

        #line 399 "src/service_libraries/pus_services/pus_service3.fin"
        atomic_store(&self->system_data_pool_u32[i], data);

    }

    #line 402 "src/service_libraries/pus_services/pus_service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 402 "src/service_libraries/pus_services/pus_service3.fin"
    return;

}
