
#include "obdh/pus/services/service4.h"

static uint32_t CPUSService4__SDP_get_mean(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static _Bool CPUSService4__SDP_param_higher_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static _Bool CPUSService4__SDP_param_lower_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index);

static Status__PUSService4Error CPUSService4__get_PID_defined_stats_index(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request);

static IndexStatus CPUSService4__get_free_index(const termina__event_t * const termina__ev, const CPUSService4 * const self, const PS4TCRequest * const tc_request);

static Status__PUSService4Error CPUSService4__add_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request);

static Status__PUSService4Error CPUSService4__delete_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request);

static Status__PUSService4Error CPUSService4__exec4_1TC(const termina__event_t * const termina__ev, CPUSService4 * const self, const PS4TCRequest * const tc_request);

static Status__PUSService4Error CPUSService4__exec4_6TC(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request);

static Status__PUSService4Error CPUSService4__exec4_7TC(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request);

static uint32_t CPUSService4__get_data_pool_item(const termina__event_t * const termina__ev, const CPUSService4 * const self, const uint16_t PID);

static _Bool CPUSService4__is_stats_index_defined(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t stats_index);

static uint32_t CPUSService4__SDP_get_mean(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 467 "src/obdh/pus/services/service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 468 "src/obdh/pus/services/service4.fin"
    uint32_t mean_value = 0U;

    #line 470 "src/obdh/pus/services/service4.fin"
    DataPoolItem item_type = sys_data_pool_get_item(PID);

    #line 473 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U8Item) {
        
        #line 473 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U8Item._0;

        #line 474 "src/obdh/pus/services/service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 475 "src/obdh/pus/services/service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 476 "src/obdh/pus/services/service4.fin"
        mean_value = (uint32_t)((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].mean_value * self->param_stats[termina__check__array_index(4U, pid_index)].samples) + (uint32_t)u8_SDP_value) / termina__check__divisor_u32((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].samples + 1U));

    } else
    #line 478 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U32Item) {
        
        #line 478 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U32Item._0;

        #line 479 "src/obdh/pus/services/service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 480 "src/obdh/pus/services/service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        #line 481 "src/obdh/pus/services/service4.fin"
        mean_value = (uint32_t)((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].mean_value * self->param_stats[termina__check__array_index(4U, pid_index)].samples) + u32_SDP_value) / termina__check__divisor_u32((uint32_t)(self->param_stats[termina__check__array_index(4U, pid_index)].samples + 1U));

    } else
    {
        

    }

    #line 488 "src/obdh/pus/services/service4.fin"
    return mean_value;

}

static _Bool CPUSService4__SDP_param_higher_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 383 "src/obdh/pus/services/service4.fin"
    _Bool is_higher = false;

    #line 384 "src/obdh/pus/services/service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 386 "src/obdh/pus/services/service4.fin"
    DataPoolItem item_type = sys_data_pool_get_item(PID);

    #line 389 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U8Item) {
        
        #line 389 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U8Item._0;

        #line 390 "src/obdh/pus/services/service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 391 "src/obdh/pus/services/service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 392 "src/obdh/pus/services/service4.fin"
        if ((uint32_t)u8_SDP_value > self->param_stats[termina__check__array_index(4U, pid_index)].max) {
            
            #line 393 "src/obdh/pus/services/service4.fin"
            is_higher = true;

        }

    } else
    #line 396 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U32Item) {
        
        #line 396 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U32Item._0;

        #line 397 "src/obdh/pus/services/service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 398 "src/obdh/pus/services/service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        #line 399 "src/obdh/pus/services/service4.fin"
        if (u32_SDP_value > self->param_stats[termina__check__array_index(4U, pid_index)].max) {
            
            #line 400 "src/obdh/pus/services/service4.fin"
            is_higher = true;

        }

    } else
    {
        

    }

    #line 408 "src/obdh/pus/services/service4.fin"
    return is_higher;

}

static _Bool CPUSService4__SDP_param_lower_than_limit(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t pid_index) {
    
    (void)termina__ev;

    #line 414 "src/obdh/pus/services/service4.fin"
    _Bool is_lower = false;

    #line 415 "src/obdh/pus/services/service4.fin"
    uint16_t PID = self->stats_config_table.PID[termina__check__array_index(4U, pid_index)];

    #line 417 "src/obdh/pus/services/service4.fin"
    DataPoolItem item_type = sys_data_pool_get_item(PID);

    #line 420 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U8Item) {
        
        #line 420 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U8Item._0;

        #line 421 "src/obdh/pus/services/service4.fin"
        uint8_t u8_SDP_value = 0U;

        #line 422 "src/obdh/pus/services/service4.fin"
        u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 423 "src/obdh/pus/services/service4.fin"
        if ((uint32_t)u8_SDP_value < self->param_stats[termina__check__array_index(4U, pid_index)].min) {
            
            #line 424 "src/obdh/pus/services/service4.fin"
            is_lower = true;

        }

    } else
    #line 427 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U32Item) {
        
        #line 427 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U32Item._0;

        #line 428 "src/obdh/pus/services/service4.fin"
        uint32_t u32_SDP_value = 0U;

        #line 429 "src/obdh/pus/services/service4.fin"
        u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        #line 430 "src/obdh/pus/services/service4.fin"
        if (u32_SDP_value < self->param_stats[termina__check__array_index(4U, pid_index)].min) {
            
            #line 431 "src/obdh/pus/services/service4.fin"
            is_lower = true;

        }

    } else
    {
        

    }

    #line 439 "src/obdh/pus/services/service4.fin"
    return is_lower;

}

static Status__PUSService4Error CPUSService4__get_PID_defined_stats_index(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request) {
    
    (void)termina__ev;

    #line 34 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status = { ._variant = Status__Failure, .Failure = { ._0 = { ._variant = PUSService4Error__PIDStatsUndefined, .PIDStatsUndefined = { ._0 = tc_request->PID } } } };

    #line 36 "src/obdh/pus/services/service4.fin"
    for (size_t i = 0U; i < 4U && status._variant == Status__Failure; i = i + 1U) {
        
        #line 38 "src/obdh/pus/services/service4.fin"
        if (tc_request->PID == self->stats_config_table.PID[i]) {
            
            #line 40 "src/obdh/pus/services/service4.fin"
            if (self->stats_config_table.defined[i] == true) {
                
                #line 42 "src/obdh/pus/services/service4.fin"
                if (sys_data_pool_is_valid_PID(tc_request->PID)) {
                    
                    #line 44 "src/obdh/pus/services/service4.fin"
                    tc_request->valid_index = i;

                    #line 45 "src/obdh/pus/services/service4.fin"
                    status._variant = Status__Success;

                } else
                {
                    
                    #line 48 "src/obdh/pus/services/service4.fin"
                    self->stats_config_table.defined[i] = false;

                }

            }

        }

    }

    #line 55 "src/obdh/pus/services/service4.fin"
    return status;

}

static IndexStatus CPUSService4__get_free_index(const termina__event_t * const termina__ev, const CPUSService4 * const self, const PS4TCRequest * const tc_request) {
    
    (void)termina__ev;

    #line 60 "src/obdh/pus/services/service4.fin"
    IndexStatus id_status = { .index = 0U, .status = { ._variant = Status__Failure, .Failure = { ._0 = { ._variant = PUSService4Error__NotFreeStatsConfig, .NotFreeStatsConfig = { ._0 = tc_request->PID } } } } };

    #line 62 "src/obdh/pus/services/service4.fin"
    for (size_t i = 0U; i < 4U && id_status.status._variant == Status__Failure; i = i + 1U) {
        
        #line 64 "src/obdh/pus/services/service4.fin"
        _Bool pid_is_valid = sys_data_pool_is_valid_PID(self->stats_config_table.PID[i]);

        #line 66 "src/obdh/pus/services/service4.fin"
        if (self->stats_config_table.defined[i] == false || pid_is_valid == false) {
            
            #line 68 "src/obdh/pus/services/service4.fin"
            id_status.index = i;

            #line 69 "src/obdh/pus/services/service4.fin"
            id_status.status._variant = Status__Success;

        }

    }

    #line 72 "src/obdh/pus/services/service4.fin"
    return id_status;

}

static Status__PUSService4Error CPUSService4__add_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request) {
    
    #line 98 "src/obdh/pus/services/service4.fin"
    IndexStatus index_status = { .index = 0U, .status = { ._variant = Status__Success } };

    #line 99 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status = CPUSService4__get_PID_defined_stats_index(termina__ev, self, tc_request);

    #line 101 "src/obdh/pus/services/service4.fin"
    if (status._variant == Status__Failure) {
        
        #line 103 "src/obdh/pus/services/service4.fin"
        index_status = CPUSService4__get_free_index(termina__ev, self, tc_request);

        #line 104 "src/obdh/pus/services/service4.fin"
        tc_request->valid_index = index_status.index;

    }

    #line 107 "src/obdh/pus/services/service4.fin"
    if (index_status.status._variant == Status__Success) {
        
        #line 109 "src/obdh/pus/services/service4.fin"
        size_t PID_index = tc_request->valid_index;

        #line 111 "src/obdh/pus/services/service4.fin"
        self->stats_config_table.defined[termina__check__array_index(4U, PID_index)] = true;

        #line 112 "src/obdh/pus/services/service4.fin"
        self->stats_config_table.PID[termina__check__array_index(4U, PID_index)] = tc_request->PID;

        #line 114 "src/obdh/pus/services/service4.fin"
        self->param_stats[termina__check__array_index(4U, PID_index)].samples = 0U;

        #line 115 "src/obdh/pus/services/service4.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 116 "src/obdh/pus/services/service4.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 117 "src/obdh/pus/services/service4.fin"
        self->stats_config_table.start_time[termina__check__array_index(4U, PID_index)] = current_obt;

        #line 118 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Success;

    } else
    {
        
        #line 122 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Failure;
        #line 122 "src/obdh/pus/services/service4.fin"
        status.Failure._0._variant = PUSService4Error__NotFreeStatsConfig;
        #line 122 "src/obdh/pus/services/service4.fin"
        status.Failure._0.NotFreeStatsConfig._0 = tc_request->PID;

    }

    #line 125 "src/obdh/pus/services/service4.fin"
    return status;

}

static Status__PUSService4Error CPUSService4__delete_PID_stats(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request) {
    
    #line 130 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status = CPUSService4__get_PID_defined_stats_index(termina__ev, self, tc_request);

    #line 132 "src/obdh/pus/services/service4.fin"
    if (status._variant == Status__Success) {
        
        #line 133 "src/obdh/pus/services/service4.fin"
        self->stats_config_table.defined[termina__check__array_index(4U, tc_request->valid_index)] = false;

    }

    #line 136 "src/obdh/pus/services/service4.fin"
    return status;

}

static Status__PUSService4Error CPUSService4__exec4_1TC(const termina__event_t * const termina__ev, CPUSService4 * const self, const PS4TCRequest * const tc_request) {
    
    #line 143 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status = { ._variant = Status__Success };

    #line 145 "src/obdh/pus/services/service4.fin"
    self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 150 "src/obdh/pus/services/service4.fin"
    for (size_t i = 0U; i < 4U; i = i + 1U) {
        
        #line 152 "src/obdh/pus/services/service4.fin"
        if (self->stats_config_table.defined[i] == true) {
            
            #line 154 "src/obdh/pus/services/service4.fin"
            Option__box tm_handler = { ._variant = Option__None };

            #line 155 "src/obdh/pus/services/service4.fin"
            self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

            #line 159 "src/obdh/pus/services/service4.fin"
            if (tm_handler._variant == Option__Some) {
                
                #line 159 "src/obdh/pus/services/service4.fin"
                const termina__box_t b_tm_handler = tm_handler.Some._0;

                #line 161 "src/obdh/pus/services/service4.fin"
                CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

                #line 162 "src/obdh/pus/services/service4.fin"
                uint16_t tm_count = 0U;

                #line 164 "src/obdh/pus/services/service4.fin"
                self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

                #line 165 "src/obdh/pus/services/service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

                #line 167 "src/obdh/pus/services/service4.fin"
                const Status__TMHandlerError tm_status = build_tm_4_2((TMHandler *)b_tm_handler.data, tm_count, i, 1U, &self->stats_config_table, self->param_stats, current_obt);

                #line 169 "src/obdh/pus/services/service4.fin"
                if (tm_status._variant == Status__Success) {
                    
                    #line 171 "src/obdh/pus/services/service4.fin"
                    self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

                } else
                {
                    
                    #line 175 "src/obdh/pus/services/service4.fin"
                    self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                    #line 176 "src/obdh/pus/services/service4.fin"
                    self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

                }

                #line 180 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].samples = 0U;

                #line 181 "src/obdh/pus/services/service4.fin"
                CUCTime current_obt_update = { .finetime = 0U, .seconds = 0U };

                #line 182 "src/obdh/pus/services/service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt_update);

                #line 183 "src/obdh/pus/services/service4.fin"
                self->stats_config_table.start_time[i] = current_obt_update;

            } else
            {
                
                #line 186 "src/obdh/pus/services/service4.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        }

    }

    #line 192 "src/obdh/pus/services/service4.fin"
    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    #line 197 "src/obdh/pus/services/service4.fin"
    return status;

}

static Status__PUSService4Error CPUSService4__exec4_6TC(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request) {
    
    #line 203 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status;

    #line 205 "src/obdh/pus/services/service4.fin"
    if (tc_request->N != 1U) {
        
        #line 207 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Failure;
        #line 207 "src/obdh/pus/services/service4.fin"
        status.Failure._0._variant = PUSService4Error__NumOfInstrNotValid;
        #line 207 "src/obdh/pus/services/service4.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 209 "src/obdh/pus/services/service4.fin"
    if (sys_data_pool_is_valid_PID(tc_request->PID) == false) {
        
        #line 211 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Failure;
        #line 211 "src/obdh/pus/services/service4.fin"
        status.Failure._0._variant = PUSService4Error__PIDNotValid;
        #line 211 "src/obdh/pus/services/service4.fin"
        status.Failure._0.PIDNotValid._0 = tc_request->PID;

    } else
    {
        
        #line 215 "src/obdh/pus/services/service4.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 220 "src/obdh/pus/services/service4.fin"
        status = CPUSService4__add_PID_stats(termina__ev, self, tc_request);

        #line 222 "src/obdh/pus/services/service4.fin"
        if (status._variant == Status__Success) {
            
            #line 224 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        }

    }

    #line 233 "src/obdh/pus/services/service4.fin"
    return status;

}

static Status__PUSService4Error CPUSService4__exec4_7TC(const termina__event_t * const termina__ev, CPUSService4 * const self, PS4TCRequest * const tc_request) {
    
    #line 239 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status;

    #line 241 "src/obdh/pus/services/service4.fin"
    if (tc_request->N != 1U) {
        
        #line 243 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Failure;
        #line 243 "src/obdh/pus/services/service4.fin"
        status.Failure._0._variant = PUSService4Error__NumOfInstrNotValid;
        #line 243 "src/obdh/pus/services/service4.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 245 "src/obdh/pus/services/service4.fin"
    if (sys_data_pool_is_valid_PID(tc_request->PID) == false) {
        
        #line 247 "src/obdh/pus/services/service4.fin"
        status._variant = Status__Failure;
        #line 247 "src/obdh/pus/services/service4.fin"
        status.Failure._0._variant = PUSService4Error__PIDNotValid;
        #line 247 "src/obdh/pus/services/service4.fin"
        status.Failure._0.PIDNotValid._0 = tc_request->PID;

    } else
    {
        
        #line 251 "src/obdh/pus/services/service4.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 256 "src/obdh/pus/services/service4.fin"
        status = CPUSService4__delete_PID_stats(termina__ev, self, tc_request);

        #line 258 "src/obdh/pus/services/service4.fin"
        if (status._variant == Status__Success) {
            
            #line 260 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        }

    }

    #line 268 "src/obdh/pus/services/service4.fin"
    return status;

}

void CPUSService4__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 271 "src/obdh/pus/services/service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 271 "src/obdh/pus/services/service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 273 "src/obdh/pus/services/service4.fin"
    Status__PUSService4Error status = { ._variant = Status__Success };

    #line 274 "src/obdh/pus/services/service4.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 275 "src/obdh/pus/services/service4.fin"
    PS4TCRequest tc_request = { .N = 0U, .PID = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U, .valid_index = 0U };

    #line 277 "src/obdh/pus/services/service4.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 278 "src/obdh/pus/services/service4.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 279 "src/obdh/pus/services/service4.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 280 "src/obdh/pus/services/service4.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 282 "src/obdh/pus/services/service4.fin"
    if (subtype == 6U || subtype == 7U) {
        
        #line 284 "src/obdh/pus/services/service4.fin"
        Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

        #line 285 "src/obdh/pus/services/service4.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 286 "src/obdh/pus/services/service4.fin"
            tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.PID);

        }

        #line 289 "src/obdh/pus/services/service4.fin"
        if (tc_data_status._variant == Status__Failure) {
            
            #line 290 "src/obdh/pus/services/service4.fin"
            status._variant = Status__Failure;
            #line 290 "src/obdh/pus/services/service4.fin"
            status.Failure._0._variant = PUSService4Error__AppDataOutOfRange;
            #line 290 "src/obdh/pus/services/service4.fin"
            status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

        }

    }

    #line 295 "src/obdh/pus/services/service4.fin"
    if (status._variant == Status__Success) {
        
        #line 297 "src/obdh/pus/services/service4.fin"
        if (subtype == 1U) {
            
            #line 299 "src/obdh/pus/services/service4.fin"
            status = CPUSService4__exec4_1TC(termina__ev, self, &tc_request);

        } else
        #line 301 "src/obdh/pus/services/service4.fin"
        if (subtype == 6U) {
            
            #line 303 "src/obdh/pus/services/service4.fin"
            status = CPUSService4__exec4_6TC(termina__ev, self, &tc_request);

        } else
        #line 305 "src/obdh/pus/services/service4.fin"
        if (subtype == 7U) {
            
            #line 307 "src/obdh/pus/services/service4.fin"
            status = CPUSService4__exec4_7TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 311 "src/obdh/pus/services/service4.fin"
            status._variant = Status__Failure;
            #line 311 "src/obdh/pus/services/service4.fin"
            status.Failure._0._variant = PUSService4Error__ErrorInAcceptance;

        }

    }

    #line 318 "src/obdh/pus/services/service4.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 321 "src/obdh/pus/services/service4.fin"
        const PUSService4Error error = status.Failure._0;

        #line 325 "src/obdh/pus/services/service4.fin"
        if (error._variant == PUSService4Error__ErrorInAcceptance) {
            
            #line 327 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 332 "src/obdh/pus/services/service4.fin"
        if (error._variant == PUSService4Error__AppDataOutOfRange) {
            
            #line 332 "src/obdh/pus/services/service4.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 334 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 340 "src/obdh/pus/services/service4.fin"
        if (error._variant == PUSService4Error__NumOfInstrNotValid) {
            
            #line 340 "src/obdh/pus/services/service4.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 342 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        #line 348 "src/obdh/pus/services/service4.fin"
        if (error._variant == PUSService4Error__PIDNotValid) {
            
            #line 348 "src/obdh/pus/services/service4.fin"
            const uint16_t PID = error.PIDNotValid._0;

            #line 350 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        } else
        #line 356 "src/obdh/pus/services/service4.fin"
        if (error._variant == PUSService4Error__PIDStatsUndefined) {
            
            #line 356 "src/obdh/pus/services/service4.fin"
            const uint16_t PID = error.PIDStatsUndefined._0;

            #line 358 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_4_PID_stats_undefined(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        } else
        {
            
            #line 364 "src/obdh/pus/services/service4.fin"
            const uint16_t PID = error.NotFreeStatsConfig._0;

            #line 366 "src/obdh/pus/services/service4.fin"
            self->pus_service_1.send_tm_1_8_not_free_stats_config(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        }

    }

    #line 377 "src/obdh/pus/services/service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 377 "src/obdh/pus/services/service4.fin"
    return;

}

static uint32_t CPUSService4__get_data_pool_item(const termina__event_t * const termina__ev, const CPUSService4 * const self, const uint16_t PID) {
    
    (void)termina__ev;

    #line 444 "src/obdh/pus/services/service4.fin"
    DataPoolItem item_type = sys_data_pool_get_item(PID);

    #line 445 "src/obdh/pus/services/service4.fin"
    uint32_t SDP_value = 0U;

    #line 448 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U8Item) {
        
        #line 448 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U8Item._0;

        #line 449 "src/obdh/pus/services/service4.fin"
        uint8_t aux_value = 0U;

        #line 450 "src/obdh/pus/services/service4.fin"
        aux_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 451 "src/obdh/pus/services/service4.fin"
        SDP_value = (uint32_t)aux_value;

    } else
    #line 453 "src/obdh/pus/services/service4.fin"
    if (item_type._variant == DataPoolItem__U32Item) {
        
        #line 453 "src/obdh/pus/services/service4.fin"
        const size_t sdp_index = item_type.U32Item._0;

        #line 454 "src/obdh/pus/services/service4.fin"
        SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

    } else
    {
        

    }

    #line 460 "src/obdh/pus/services/service4.fin"
    return SDP_value;

}

static _Bool CPUSService4__is_stats_index_defined(const termina__event_t * const termina__ev, const CPUSService4 * const self, const size_t stats_index) {
    
    (void)termina__ev;

    #line 77 "src/obdh/pus/services/service4.fin"
    _Bool is_defined = false;

    #line 79 "src/obdh/pus/services/service4.fin"
    if (stats_index < 4U) {
        
        #line 81 "src/obdh/pus/services/service4.fin"
        if (self->stats_config_table.defined[stats_index] == true) {
            
            #line 83 "src/obdh/pus/services/service4.fin"
            if (sys_data_pool_is_valid_PID(self->stats_config_table.PID[stats_index])) {
                
                #line 85 "src/obdh/pus/services/service4.fin"
                is_defined = true;

            } else
            {
                

            }

        }

    }

    #line 93 "src/obdh/pus/services/service4.fin"
    return is_defined;

}

void CPUSService4__startup(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 564 "src/obdh/pus/services/service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 564 "src/obdh/pus/services/service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 566 "src/obdh/pus/services/service4.fin"
    for (size_t i = 0U; i < 4U; i = i + 1U) {
        
        #line 568 "src/obdh/pus/services/service4.fin"
        if (CPUSService4__is_stats_index_defined(termina__ev, self, i) == true) {
            
            #line 570 "src/obdh/pus/services/service4.fin"
            self->param_stats[i].samples = 0U;

            #line 571 "src/obdh/pus/services/service4.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 572 "src/obdh/pus/services/service4.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 573 "src/obdh/pus/services/service4.fin"
            self->stats_config_table.start_time[i] = current_obt;

        } else
        {
            
            #line 577 "src/obdh/pus/services/service4.fin"
            self->stats_config_table.defined[i] = false;

        }

    }

    #line 582 "src/obdh/pus/services/service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 582 "src/obdh/pus/services/service4.fin"
    return;

}

void CPUSService4__update_all_stats(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 491 "src/obdh/pus/services/service4.fin"
    CPUSService4 * self = (CPUSService4 *)termina__this;

    #line 491 "src/obdh/pus/services/service4.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 493 "src/obdh/pus/services/service4.fin"
    for (size_t i = 0U; i < 4U; i = i + 1U) {
        
        #line 495 "src/obdh/pus/services/service4.fin"
        if (CPUSService4__is_stats_index_defined(termina__ev, self, i) == true) {
            
            #line 497 "src/obdh/pus/services/service4.fin"
            uint16_t PID = self->stats_config_table.PID[i];

            #line 499 "src/obdh/pus/services/service4.fin"
            if (self->param_stats[i].samples > 0U) {
                
                #line 501 "src/obdh/pus/services/service4.fin"
                if (CPUSService4__SDP_param_higher_than_limit(termina__ev, self, i) == true) {
                    
                    #line 503 "src/obdh/pus/services/service4.fin"
                    uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                    #line 504 "src/obdh/pus/services/service4.fin"
                    self->param_stats[i].max = system_data_pool_item;

                    #line 505 "src/obdh/pus/services/service4.fin"
                    CUCTime current_time = { .finetime = 0U, .seconds = 0U };

                    #line 509 "src/obdh/pus/services/service4.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                    #line 510 "src/obdh/pus/services/service4.fin"
                    self->param_stats[i].max_obt = current_time;

                } else
                #line 513 "src/obdh/pus/services/service4.fin"
                if (CPUSService4__SDP_param_lower_than_limit(termina__ev, self, i) == true) {
                    
                    #line 515 "src/obdh/pus/services/service4.fin"
                    uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                    #line 516 "src/obdh/pus/services/service4.fin"
                    self->param_stats[i].min = system_data_pool_item;

                    #line 517 "src/obdh/pus/services/service4.fin"
                    CUCTime current_time = { .finetime = 0U, .seconds = 0U };

                    #line 521 "src/obdh/pus/services/service4.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                    #line 522 "src/obdh/pus/services/service4.fin"
                    self->param_stats[i].min_obt = current_time;

                } else
                {
                    

                }

                #line 528 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].mean_value = CPUSService4__SDP_get_mean(termina__ev, self, i);

            } else
            {
                
                #line 533 "src/obdh/pus/services/service4.fin"
                uint32_t system_data_pool_item = CPUSService4__get_data_pool_item(termina__ev, self, PID);

                #line 534 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].max = system_data_pool_item;

                #line 535 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].min = system_data_pool_item;

                #line 536 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].mean_value = system_data_pool_item;

                #line 537 "src/obdh/pus/services/service4.fin"
                CUCTime current_time = { .finetime = 0U, .seconds = 0U };

                #line 541 "src/obdh/pus/services/service4.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_time);

                #line 542 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].max_obt = current_time;

                #line 543 "src/obdh/pus/services/service4.fin"
                self->param_stats[i].min_obt = current_time;

            }

            #line 548 "src/obdh/pus/services/service4.fin"
            self->param_stats[i].samples = self->param_stats[i].samples + 1U;

        } else
        {
            
            #line 553 "src/obdh/pus/services/service4.fin"
            self->stats_config_table.defined[i] = false;

        }

    }

    #line 560 "src/obdh/pus/services/service4.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 560 "src/obdh/pus/services/service4.fin"
    return;

}
