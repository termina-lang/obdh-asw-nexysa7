
#include "service_libraries/pus_services/pus_service4.h"

static uint32_t CPUSService4__SDP_get_mean(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static _Bool CPUSService4__SDP_param_higher_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static _Bool CPUSService4__SDP_param_lower_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static Status__i32 CPUSService4__get_PID_defined_stats_index(const termina__event_t * const termina__ev, CPUSService4 * const self);

static IndexStatus CPUSService4__get_free_index(const termina__event_t * const termina__ev, const CPUSService4 * const self);

static Status__i32 CPUSService4__add_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self);

static Status__i32 CPUSService4__delete_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self);

static Status__i32 CPUSService4__exec4_1TC(const termina__event_t * const termina__ev, CPUSService4 * const self);

static Status__i32 CPUSService4__exec4_6TC(const termina__event_t * const termina__ev, CPUSService4 * const self);

static Status__i32 CPUSService4__exec4_7TC(const termina__event_t * const termina__ev, CPUSService4 * const self);

static uint32_t CPUSService4__get_data_pool_item(const termina__event_t * const termina__ev, const CPUSService4 * const self, const uint16_t PID);

static _Bool CPUSService4__is_stats_index_defined(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t stats_index);

static uint32_t CPUSService4__SDP_get_mean(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 493 "src/service_libraries/pus_services/pus_service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 494 "src/service_libraries/pus_services/pus_service4.fin"
    uint32_t mean_value = 0U;

    #line 496 "src/service_libraries/pus_services/pus_service4.fin"
    DataPoolItemType item_type = sys_data_pool_get_item_type(PID);

    #line 499 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u8_t) {
        
        #line 500 "src/service_libraries/pus_services/pus_service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 501 "src/service_libraries/pus_services/pus_service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)PID)]);

        #line 502 "src/service_libraries/pus_services/pus_service4.fin"
        mean_value = (uint32_t)((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].mean_value * self->param_stats[termina__check__array_index(4U, pid_index)].samples) + (uint32_t)u8_SDP_value) / termina__check__divisor_u32((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].samples + 1U));

    } else
    #line 504 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u32_t) {
        
        #line 505 "src/service_libraries/pus_services/pus_service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 506 "src/service_libraries/pus_services/pus_service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)PID)]);

        #line 507 "src/service_libraries/pus_services/pus_service4.fin"
        mean_value = (uint32_t)((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].mean_value * self->param_stats[termina__check__array_index(4U, pid_index)].samples) + u32_SDP_value) / termina__check__divisor_u32((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].samples + 1U));

    } else
    {
        

    }

    #line 514 "src/service_libraries/pus_services/pus_service4.fin"
    return mean_value;

}

static _Bool CPUSService4__SDP_param_higher_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 409 "src/service_libraries/pus_services/pus_service4.fin"
    _Bool is_higher = false;

    #line 410 "src/service_libraries/pus_services/pus_service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 412 "src/service_libraries/pus_services/pus_service4.fin"
    DataPoolItemType item_type = sys_data_pool_get_item_type(PID);

    #line 415 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u8_t) {
        
        #line 416 "src/service_libraries/pus_services/pus_service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 417 "src/service_libraries/pus_services/pus_service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)PID)]);

        #line 418 "src/service_libraries/pus_services/pus_service4.fin"
        if ((uint32_t)u8_SDP_value > self->param_stats[termina__check__array_index(4U, pid_index)].max) {
            
            #line 419 "src/service_libraries/pus_services/pus_service4.fin"
            is_higher = true;

        }

    } else
    #line 422 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u32_t) {
        
        #line 423 "src/service_libraries/pus_services/pus_service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 424 "src/service_libraries/pus_services/pus_service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)PID)]);

        #line 425 "src/service_libraries/pus_services/pus_service4.fin"
        if (u32_SDP_value > self->param_stats[termina__check__array_index(4U, pid_index)].max) {
            
            #line 426 "src/service_libraries/pus_services/pus_service4.fin"
            is_higher = true;

        }

    } else
    {
        

    }

    #line 434 "src/service_libraries/pus_services/pus_service4.fin"
    return is_higher;

}

static _Bool CPUSService4__SDP_param_lower_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 440 "src/service_libraries/pus_services/pus_service4.fin"
    _Bool is_lower = false;

    #line 441 "src/service_libraries/pus_services/pus_service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 443 "src/service_libraries/pus_services/pus_service4.fin"
    DataPoolItemType item_type = sys_data_pool_get_item_type(PID);

    #line 446 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u8_t) {
        
        #line 447 "src/service_libraries/pus_services/pus_service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 448 "src/service_libraries/pus_services/pus_service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)PID)]);

        #line 449 "src/service_libraries/pus_services/pus_service4.fin"
        if ((uint32_t)u8_SDP_value < self->param_stats[termina__check__array_index(4U, pid_index)].min) {
            
            #line 450 "src/service_libraries/pus_services/pus_service4.fin"
            is_lower = true;

        }

    } else
    #line 453 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u32_t) {
        
        #line 454 "src/service_libraries/pus_services/pus_service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 455 "src/service_libraries/pus_services/pus_service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)PID)]);

        #line 456 "src/service_libraries/pus_services/pus_service4.fin"
        if (u32_SDP_value < self->param_stats[termina__check__array_index(4U, pid_index)].min) {
            
            #line 457 "src/service_libraries/pus_services/pus_service4.fin"
            is_lower = true;

        }

    } else
    {
        

    }

    #line 465 "src/service_libraries/pus_services/pus_service4.fin"
    return is_lower;

}

static Status__i32 CPUSService4__get_PID_defined_stats_index(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    (void)termina__ev;

    #line 36 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = { ._variant = Status__Failure, .Failure = { ._0 = 10L } };

    #line 38 "src/service_libraries/pus_services/pus_service4.fin"
    for (size_t i = 0U; i < 4U && status._variant == Status__Failure; i = i + 1U) {
        
        #line 40 "src/service_libraries/pus_services/pus_service4.fin"
        if (self->exec_tc_req_status_update.PID == self->stats_config_table.PID[i]) {
            
            #line 42 "src/service_libraries/pus_services/pus_service4.fin"
            if (self->stats_config_table.defined[i] == true) {
                
                #line 44 "src/service_libraries/pus_services/pus_service4.fin"
                if (sys_data_pool_is_valid_PID(self->exec_tc_req_status_update.PID)) {
                    
                    #line 46 "src/service_libraries/pus_services/pus_service4.fin"
                    self->exec_tc_req_status_update.valid_index = i;

                    #line 47 "src/service_libraries/pus_services/pus_service4.fin"
                    status._variant = Status__Success;

                } else
                {
                    
                    #line 50 "src/service_libraries/pus_services/pus_service4.fin"
                    self->stats_config_table.defined[i] = false;

                }

            }

        }

    }

    #line 57 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

static IndexStatus CPUSService4__get_free_index(const termina__event_t * const termina__ev, const CPUSService4 * const self) {
    
    (void)termina__ev;

    #line 62 "src/service_libraries/pus_services/pus_service4.fin"
    IndexStatus id_status = { .index = 0U, .status = { ._variant = Status__Failure, .Failure = { ._0 = 12L } } };

    #line 64 "src/service_libraries/pus_services/pus_service4.fin"
    for (size_t i = 0U; i < 4U && id_status.status._variant == Status__Failure; i = i + 1U) {
        
        #line 66 "src/service_libraries/pus_services/pus_service4.fin"
        _Bool pid_is_valid = sys_data_pool_is_valid_PID(self->stats_config_table.PID[i]);

        #line 68 "src/service_libraries/pus_services/pus_service4.fin"
        if (self->stats_config_table.defined[i] == false || pid_is_valid == false) {
            
            #line 70 "src/service_libraries/pus_services/pus_service4.fin"
            id_status.index = i;

            #line 71 "src/service_libraries/pus_services/pus_service4.fin"
            id_status.status._variant = Status__Success;

        }

    }

    #line 74 "src/service_libraries/pus_services/pus_service4.fin"
    return id_status;

}

static Status__i32 CPUSService4__add_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    #line 100 "src/service_libraries/pus_services/pus_service4.fin"
    IndexStatus index_status = { .index = 0U, .status = { ._variant = Status__Success } };

    #line 101 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = CPUSService4__get_PID_defined_stats_index(termina__ev, self);

    #line 103 "src/service_libraries/pus_services/pus_service4.fin"
    if (status._variant == Status__Failure) {
        
        #line 105 "src/service_libraries/pus_services/pus_service4.fin"
        index_status = CPUSService4__get_free_index(termina__ev, self);

        #line 106 "src/service_libraries/pus_services/pus_service4.fin"
        self->exec_tc_req_status_update.valid_index = index_status.index;

    }

    #line 109 "src/service_libraries/pus_services/pus_service4.fin"
    if (index_status.status._variant == Status__Success) {
        
        #line 111 "src/service_libraries/pus_services/pus_service4.fin"
        size_t PID_index = self->exec_tc_req_status_update.valid_index;

        #line 113 "src/service_libraries/pus_services/pus_service4.fin"
        self->stats_config_table.defined[termina__check__array_index(4U, PID_index)] = true;

        #line 114 "src/service_libraries/pus_services/pus_service4.fin"
        self->stats_config_table.PID[termina__check__array_index(4U, PID_index)] = self->exec_tc_req_status_update.PID;

        #line 116 "src/service_libraries/pus_services/pus_service4.fin"
        self->param_stats[termina__check__array_index(4U, PID_index)].samples = 0U;

        #line 117 "src/service_libraries/pus_services/pus_service4.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 118 "src/service_libraries/pus_services/pus_service4.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 119 "src/service_libraries/pus_services/pus_service4.fin"
        self->stats_config_table.start_time[termina__check__array_index(4U, PID_index)] = current_obt;

        #line 120 "src/service_libraries/pus_services/pus_service4.fin"
        status._variant = Status__Success;

    } else
    {
        
        #line 124 "src/service_libraries/pus_services/pus_service4.fin"
        status._variant = Status__Failure;
        #line 124 "src/service_libraries/pus_services/pus_service4.fin"
        status.Failure._0 = 12L;

    }

    #line 127 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

static Status__i32 CPUSService4__delete_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    #line 132 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = CPUSService4__get_PID_defined_stats_index(termina__ev, self);

    #line 134 "src/service_libraries/pus_services/pus_service4.fin"
    if (status._variant == Status__Success) {
        
        #line 135 "src/service_libraries/pus_services/pus_service4.fin"
        self->stats_config_table.defined[termina__check__array_index(4U, self->exec_tc_req_status_update.valid_index)] = false;

    }

    #line 138 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

static Status__i32 CPUSService4__exec4_1TC(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    #line 145 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 147 "src/service_libraries/pus_services/pus_service4.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    #line 153 "src/service_libraries/pus_services/pus_service4.fin"
    for (size_t i = 0U; i < 4U && status._variant == Status__Success; i = i + 1U) {
        
        #line 155 "src/service_libraries/pus_services/pus_service4.fin"
        if (self->stats_config_table.defined[i] == true) {
            
            #line 157 "src/service_libraries/pus_services/pus_service4.fin"
            Option__box tm_handler = { ._variant = Option__None };

            #line 158 "src/service_libraries/pus_services/pus_service4.fin"
            self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

            #line 162 "src/service_libraries/pus_services/pus_service4.fin"
            if (tm_handler._variant == Option__Some) {
                
                #line 162 "src/service_libraries/pus_services/pus_service4.fin"
                const termina__box_t b_tm_handler = tm_handler.Some._0;

                #line 164 "src/service_libraries/pus_services/pus_service4.fin"
                MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

                #line 165 "src/service_libraries/pus_services/pus_service4.fin"
                uint16_t tm_count = 0U;

                #line 167 "src/service_libraries/pus_services/pus_service4.fin"
                self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

                #line 168 "src/service_libraries/pus_services/pus_service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

                #line 170 "src/service_libraries/pus_services/pus_service4.fin"
                status = build_tm_4_2((TMHandler *)b_tm_handler.data, tm_count, i, self->exec_tc_req_status_update.N, &self->stats_config_table, self->param_stats, current_obt);

                #line 172 "src/service_libraries/pus_services/pus_service4.fin"
                if (status._variant == Status__Success) {
                    
                    #line 174 "src/service_libraries/pus_services/pus_service4.fin"
                    self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &status);

                } else
                {
                    
                    #line 178 "src/service_libraries/pus_services/pus_service4.fin"
                    self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                }

                #line 183 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].samples = 0U;

                #line 184 "src/service_libraries/pus_services/pus_service4.fin"
                MissionOBT current_obt_update = { .finetime = 0U, .seconds = 0U };

                #line 185 "src/service_libraries/pus_services/pus_service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt_update);

                #line 186 "src/service_libraries/pus_services/pus_service4.fin"
                self->stats_config_table.start_time[i] = current_obt_update;

            } else
            {
                
                #line 189 "src/service_libraries/pus_services/pus_service4.fin"
                status._variant = Status__Failure;
                #line 189 "src/service_libraries/pus_services/pus_service4.fin"
                status.Failure._0 = 1L;

            }

        }

    }

    #line 195 "src/service_libraries/pus_services/pus_service4.fin"
    if (status._variant == Status__Success) {
        
        #line 197 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

    } else
    {
        

    }

    #line 210 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

static Status__i32 CPUSService4__exec4_6TC(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    #line 216 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 218 "src/service_libraries/pus_services/pus_service4.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 220 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 226 "src/service_libraries/pus_services/pus_service4.fin"
    if (sys_data_pool_is_valid_PID(self->exec_tc_req_status_update.PID) == false) {
        
        #line 228 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

    } else
    {
        
        #line 236 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 242 "src/service_libraries/pus_services/pus_service4.fin"
        if (status._variant == Status__Success) {
            
            #line 243 "src/service_libraries/pus_services/pus_service4.fin"
            status = CPUSService4__add_PID_stats(termina__ev, self);

        }

        #line 246 "src/service_libraries/pus_services/pus_service4.fin"
        if (status._variant == Status__Success) {
            
            #line 248 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        } else
        {
            
            #line 256 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.send_tm_1_8_not_free_stats_config(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

        }

    }

    #line 266 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

static Status__i32 CPUSService4__exec4_7TC(const termina__event_t * const termina__ev, CPUSService4 * const self) {
    
    #line 272 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 274 "src/service_libraries/pus_services/pus_service4.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 276 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 282 "src/service_libraries/pus_services/pus_service4.fin"
    if (sys_data_pool_is_valid_PID(self->exec_tc_req_status_update.PID) == false) {
        
        #line 284 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

    } else
    {
        
        #line 292 "src/service_libraries/pus_services/pus_service4.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 298 "src/service_libraries/pus_services/pus_service4.fin"
        if (status._variant == Status__Success) {
            
            #line 299 "src/service_libraries/pus_services/pus_service4.fin"
            status = CPUSService4__delete_PID_stats(termina__ev, self);

        }

        #line 302 "src/service_libraries/pus_services/pus_service4.fin"
        if (status._variant == Status__Success) {
            
            #line 304 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        } else
        {
            
            #line 312 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.send_tm_1_4_PID_stats_undefined(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.PID, &status);

        }

    }

    #line 321 "src/service_libraries/pus_services/pus_service4.fin"
    return status;

}

void CPUSService4__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 324 "src/service_libraries/pus_services/pus_service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 324 "src/service_libraries/pus_services/pus_service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 326 "src/service_libraries/pus_services/pus_service4.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 327 "src/service_libraries/pus_services/pus_service4.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 329 "src/service_libraries/pus_services/pus_service4.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 330 "src/service_libraries/pus_services/pus_service4.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 331 "src/service_libraries/pus_services/pus_service4.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 332 "src/service_libraries/pus_services/pus_service4.fin"
    self->exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 334 "src/service_libraries/pus_services/pus_service4.fin"
    if (subtype == 6U || subtype == 7U) {
        
        #line 336 "src/service_libraries/pus_services/pus_service4.fin"
        status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.N);

        #line 337 "src/service_libraries/pus_services/pus_service4.fin"
        if (status._variant == Status__Success) {
            
            #line 338 "src/service_libraries/pus_services/pus_service4.fin"
            status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.PID);

        }

    }

    #line 343 "src/service_libraries/pus_services/pus_service4.fin"
    if (status._variant == Status__Success) {
        
        #line 345 "src/service_libraries/pus_services/pus_service4.fin"
        if (subtype == 1U) {
            
            #line 347 "src/service_libraries/pus_services/pus_service4.fin"
            status = CPUSService4__exec4_1TC(termina__ev, self);

        } else
        #line 349 "src/service_libraries/pus_services/pus_service4.fin"
        if (subtype == 6U) {
            
            #line 351 "src/service_libraries/pus_services/pus_service4.fin"
            status = CPUSService4__exec4_6TC(termina__ev, self);

        } else
        #line 353 "src/service_libraries/pus_services/pus_service4.fin"
        if (subtype == 7U) {
            
            #line 355 "src/service_libraries/pus_services/pus_service4.fin"
            status = CPUSService4__exec4_7TC(termina__ev, self);

        } else
        {
            
            #line 359 "src/service_libraries/pus_services/pus_service4.fin"
            status._variant = Status__Failure;
            #line 359 "src/service_libraries/pus_services/pus_service4.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 366 "src/service_libraries/pus_services/pus_service4.fin"
    if (status._variant == Status__Success) {
        
        #line 368 "src/service_libraries/pus_services/pus_service4.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 371 "src/service_libraries/pus_services/pus_service4.fin"
        const int32_t error_code = status.Failure._0;

        #line 373 "src/service_libraries/pus_services/pus_service4.fin"
        if (error_code == 4L) {
            
            #line 375 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, &status);

        } else
        #line 380 "src/service_libraries/pus_services/pus_service4.fin"
        if (error_code == 3L) {
            
            #line 382 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, &status);

        } else
        #line 387 "src/service_libraries/pus_services/pus_service4.fin"
        if (error_code == 5L) {
            
            #line 389 "src/service_libraries/pus_services/pus_service4.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.tc_num_bytes, &status);

        } else
        {
            
            #line 397 "src/service_libraries/pus_services/pus_service4.fin"
            (*action_status)._variant = Status__Failure;
            #line 397 "src/service_libraries/pus_services/pus_service4.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 403 "src/service_libraries/pus_services/pus_service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 403 "src/service_libraries/pus_services/pus_service4.fin"
    return;

}

static uint32_t CPUSService4__get_data_pool_item(const termina__event_t * const termina__ev, const CPUSService4 * const self, const uint16_t PID) {
    
    (void)termina__ev;

    #line 470 "src/service_libraries/pus_services/pus_service4.fin"
    DataPoolItemType item_type = sys_data_pool_get_item_type(PID);

    #line 471 "src/service_libraries/pus_services/pus_service4.fin"
    uint32_t SDP_value = 0U;

    #line 474 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u8_t) {
        
        #line 475 "src/service_libraries/pus_services/pus_service4.fin"
        uint8_t aux_value = 0U;

        #line 476 "src/service_libraries/pus_services/pus_service4.fin"
        aux_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, (size_t)PID)]);

        #line 477 "src/service_libraries/pus_services/pus_service4.fin"
        SDP_value = (uint32_t)aux_value;

    } else
    #line 479 "src/service_libraries/pus_services/pus_service4.fin"
    if (item_type._variant == DataPoolItemType__u32_t) {
        
        #line 480 "src/service_libraries/pus_services/pus_service4.fin"
        SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, (size_t)PID)]);

    } else
    {
        

    }

    #line 486 "src/service_libraries/pus_services/pus_service4.fin"
    return SDP_value;

}

static _Bool CPUSService4__is_stats_index_defined(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t stats_index) {
    
    (void)termina__ev;

    #line 79 "src/service_libraries/pus_services/pus_service4.fin"
    _Bool is_defined = false;

    #line 81 "src/service_libraries/pus_services/pus_service4.fin"
    if (stats_index < 4U) {
        
        #line 83 "src/service_libraries/pus_services/pus_service4.fin"
        if (self->stats_config_table.defined[stats_index] == true) {
            
            #line 85 "src/service_libraries/pus_services/pus_service4.fin"
            if (sys_data_pool_is_valid_PID(self->stats_config_table.PID[stats_index])) {
                
                #line 87 "src/service_libraries/pus_services/pus_service4.fin"
                is_defined = true;

            } else
            {
                

            }

        }

    }

    #line 95 "src/service_libraries/pus_services/pus_service4.fin"
    return is_defined;

}

void CPUSService4__startup(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 590 "src/service_libraries/pus_services/pus_service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 590 "src/service_libraries/pus_services/pus_service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 592 "src/service_libraries/pus_services/pus_service4.fin"
    for (size_t i = 0U; i < 4U; i = i + 1U) {
        
        #line 594 "src/service_libraries/pus_services/pus_service4.fin"
        if (CPUSService4__is_stats_index_defined(termina__ev, self, i) == true) {
            
            #line 596 "src/service_libraries/pus_services/pus_service4.fin"
            self->param_stats[i].samples = 0U;

            #line 597 "src/service_libraries/pus_services/pus_service4.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 598 "src/service_libraries/pus_services/pus_service4.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 599 "src/service_libraries/pus_services/pus_service4.fin"
            self->stats_config_table.start_time[i] = current_obt;

        } else
        {
            
            #line 603 "src/service_libraries/pus_services/pus_service4.fin"
            self->stats_config_table.defined[i] = false;

        }

    }

    #line 608 "src/service_libraries/pus_services/pus_service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 608 "src/service_libraries/pus_services/pus_service4.fin"
    return;

}

void CPUSService4__update_all_stats(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 517 "src/service_libraries/pus_services/pus_service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 517 "src/service_libraries/pus_services/pus_service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 519 "src/service_libraries/pus_services/pus_service4.fin"
    for (size_t i = 0U; i < 4U; i = i + 1U) {
        
        #line 521 "src/service_libraries/pus_services/pus_service4.fin"
        if (CPUSService4__is_stats_index_defined(termina__ev, self, i) == true) {
            
            #line 523 "src/service_libraries/pus_services/pus_service4.fin"
            uint16_t PID = self->stats_config_table.PID[i];

            #line 525 "src/service_libraries/pus_services/pus_service4.fin"
            if (self->param_stats[i].samples > 0U) {
                
                #line 527 "src/service_libraries/pus_services/pus_service4.fin"
                if (CPUSService4__SDP_param_higher_than_limit(termina__ev, self, i) == true) {
                    
                    #line 529 "src/service_libraries/pus_services/pus_service4.fin"
                    uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                    #line 530 "src/service_libraries/pus_services/pus_service4.fin"
                    self->param_stats[i].max = system_data_pool_item;

                    #line 531 "src/service_libraries/pus_services/pus_service4.fin"
                    MissionOBT current_time = { .finetime = 0U, .seconds = 0U };

                    #line 535 "src/service_libraries/pus_services/pus_service4.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                    #line 536 "src/service_libraries/pus_services/pus_service4.fin"
                    self->param_stats[i].max_obt = current_time;

                } else
                #line 539 "src/service_libraries/pus_services/pus_service4.fin"
                if (CPUSService4__SDP_param_lower_than_limit(termina__ev, self, i) == true) {
                    
                    #line 541 "src/service_libraries/pus_services/pus_service4.fin"
                    uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                    #line 542 "src/service_libraries/pus_services/pus_service4.fin"
                    self->param_stats[i].min = system_data_pool_item;

                    #line 543 "src/service_libraries/pus_services/pus_service4.fin"
                    MissionOBT current_time = { .finetime = 0U, .seconds = 0U };

                    #line 547 "src/service_libraries/pus_services/pus_service4.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                    #line 548 "src/service_libraries/pus_services/pus_service4.fin"
                    self->param_stats[i].min_obt = current_time;

                } else
                {
                    

                }

                #line 554 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].mean_value = CPUSService4__SDP_get_mean(termina__ev, self, i);

            } else
            {
                
                #line 559 "src/service_libraries/pus_services/pus_service4.fin"
                uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                #line 560 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].max = system_data_pool_item;

                #line 561 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].min = system_data_pool_item;

                #line 562 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].mean_value = system_data_pool_item;

                #line 563 "src/service_libraries/pus_services/pus_service4.fin"
                MissionOBT current_time = { .finetime = 0U, .seconds = 0U };

                #line 567 "src/service_libraries/pus_services/pus_service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                #line 568 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].max_obt = current_time;

                #line 569 "src/service_libraries/pus_services/pus_service4.fin"
                self->param_stats[i].min_obt = current_time;

            }

            #line 574 "src/service_libraries/pus_services/pus_service4.fin"
            self->param_stats[i].samples = self->param_stats[i].samples + 1U;

        } else
        {
            
            #line 579 "src/service_libraries/pus_services/pus_service4.fin"
            self->stats_config_table.defined[i] = false;

        }

    }

    #line 586 "src/service_libraries/pus_services/pus_service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 586 "src/service_libraries/pus_services/pus_service4.fin"
    return;

}
