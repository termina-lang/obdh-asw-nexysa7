
#include "obdh/pus/services/service3.h"

static Option__usize CPUSService3__get_SIDindex(const termina__event_t * const termina__ev, const CPUSService3 * const self, const PS3TCRequest * const tc_request);

static Status__PUSService3Error CPUSService3__exec3_31TC(const termina__event_t * const termina__ev, CPUSService3 * const self, PS3TCRequest * const tc_request);

static Status__PUSService3Error CPUSService3__exec3_5TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3TCRequest * const tc_request);

static Status__PUSService3Error CPUSService3__exec3_6TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3TCRequest * const tc_request);

void CPUSService3__do_hk(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 280 "src/obdh/pus/services/service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 280 "src/obdh/pus/services/service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 282 "src/obdh/pus/services/service3.fin"
    for (size_t i = 0U; i < 8U; i = i + 1U) {
        
        #line 284 "src/obdh/pus/services/service3.fin"
        if (self->hk_config_table[i].enabled == true) {
            
            #line 286 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[i].interval_control = self->hk_config_table[i].interval_control + 1U;

            #line 288 "src/obdh/pus/services/service3.fin"
            if (self->hk_config_table[i].interval_control >= self->hk_config_table[i].interval) {
                
                #line 290 "src/obdh/pus/services/service3.fin"
                self->hk_config_table[i].interval_control = 0U;

                #line 292 "src/obdh/pus/services/service3.fin"
                Option__box tm_handler = { ._variant = Option__None };

                #line 293 "src/obdh/pus/services/service3.fin"
                self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

                #line 297 "src/obdh/pus/services/service3.fin"
                if (tm_handler._variant == Option__Some) {
                    
                    #line 297 "src/obdh/pus/services/service3.fin"
                    const termina__box_t b_tm_handler = tm_handler.Some._0;

                    #line 299 "src/obdh/pus/services/service3.fin"
                    uint16_t tm_count = 0U;

                    #line 300 "src/obdh/pus/services/service3.fin"
                    self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

                    #line 302 "src/obdh/pus/services/service3.fin"
                    startup_tm((TMHandler *)b_tm_handler.data);

                    #line 303 "src/obdh/pus/services/service3.fin"
                    Status__TMHandlerError do_hk_status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, self->hk_config_table[i].SID);

                    #line 304 "src/obdh/pus/services/service3.fin"
                    _Bool valid_PIDs = true;

                    #line 306 "src/obdh/pus/services/service3.fin"
                    size_t num_params = (size_t)self->hk_config_table[i].num_params;

                    #line 308 "src/obdh/pus/services/service3.fin"
                    for (size_t j = 0U; j < 16U && (j < num_params && do_hk_status._variant == Status__Success && valid_PIDs); j = j + 1U) {
                        
                        #line 310 "src/obdh/pus/services/service3.fin"
                        uint16_t PID = self->hk_config_table[i].params_def[j];

                        #line 311 "src/obdh/pus/services/service3.fin"
                        DataPoolItem item_type = sys_data_pool_get_item(PID);

                        #line 314 "src/obdh/pus/services/service3.fin"
                        if (item_type._variant == DataPoolItem__U8Item) {
                            
                            #line 314 "src/obdh/pus/services/service3.fin"
                            const size_t sdp_index = item_type.U8Item._0;

                            #line 315 "src/obdh/pus/services/service3.fin"
                            uint8_t u8_SDP_value = 0U;

                            #line 316 "src/obdh/pus/services/service3.fin"
                            u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

                            #line 317 "src/obdh/pus/services/service3.fin"
                            do_hk_status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, u8_SDP_value);

                        } else
                        #line 319 "src/obdh/pus/services/service3.fin"
                        if (item_type._variant == DataPoolItem__U32Item) {
                            
                            #line 319 "src/obdh/pus/services/service3.fin"
                            const size_t sdp_index = item_type.U32Item._0;

                            #line 320 "src/obdh/pus/services/service3.fin"
                            uint32_t u32_SDP_value = 0U;

                            #line 321 "src/obdh/pus/services/service3.fin"
                            u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

                            #line 322 "src/obdh/pus/services/service3.fin"
                            do_hk_status = append_u32_appdata_field((TMHandler *)b_tm_handler.data, u32_SDP_value);

                        } else
                        {
                            
                            #line 325 "src/obdh/pus/services/service3.fin"
                            valid_PIDs = false;

                        }

                    }

                    #line 331 "src/obdh/pus/services/service3.fin"
                    CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

                    #line 332 "src/obdh/pus/services/service3.fin"
                    self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

                    #line 334 "src/obdh/pus/services/service3.fin"
                    if (do_hk_status._variant == Status__Success && valid_PIDs) {
                        
                        #line 335 "src/obdh/pus/services/service3.fin"
                        close_tm((TMHandler *)b_tm_handler.data, 3U, 25U, tm_count, current_obt);

                        #line 336 "src/obdh/pus/services/service3.fin"
                        self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

                    } else
                    {
                        
                        #line 339 "src/obdh/pus/services/service3.fin"
                        self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                        #line 341 "src/obdh/pus/services/service3.fin"
                        self->pus_service_5.send_tm_5_2(termina__ev, self->pus_service_5._that);

                    }

                } else
                {
                    
                    #line 347 "src/obdh/pus/services/service3.fin"
                    self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

                }

            }

        }

    }

    #line 355 "src/obdh/pus/services/service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 355 "src/obdh/pus/services/service3.fin"
    return;

}

static Option__usize CPUSService3__get_SIDindex(const termina__event_t * const termina__ev, const CPUSService3 * const self, const PS3TCRequest * const tc_request) {
    
    (void)termina__ev;

    #line 37 "src/obdh/pus/services/service3.fin"
    Option__usize index_found = { ._variant = Option__None };

    #line 39 "src/obdh/pus/services/service3.fin"
    for (size_t i = 0U; i < 8U && index_found._variant == Option__None; i = i + 1U) {
        
        #line 41 "src/obdh/pus/services/service3.fin"
        if (tc_request->SID == self->hk_config_table[i].SID) {
            
            #line 43 "src/obdh/pus/services/service3.fin"
            index_found._variant = Option__Some;
            #line 43 "src/obdh/pus/services/service3.fin"
            index_found.Some._0 = i;

        }

    }

    #line 47 "src/obdh/pus/services/service3.fin"
    return index_found;

}

static Status__PUSService3Error CPUSService3__exec3_31TC(const termina__event_t * const termina__ev, CPUSService3 * const self, PS3TCRequest * const tc_request) {
    
    #line 140 "src/obdh/pus/services/service3.fin"
    Status__PUSService3Error status = { ._variant = Status__Success };

    #line 142 "src/obdh/pus/services/service3.fin"
    if (tc_request->N != 1U) {
        
        #line 144 "src/obdh/pus/services/service3.fin"
        status._variant = Status__Failure;
        #line 144 "src/obdh/pus/services/service3.fin"
        status.Failure._0._variant = PUSService3Error__NumOfInstrNotValid;
        #line 144 "src/obdh/pus/services/service3.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 148 "src/obdh/pus/services/service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, tc_request);

        #line 152 "src/obdh/pus/services/service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 152 "src/obdh/pus/services/service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 154 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            #line 159 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].interval = tc_request->collection_interval;

            #line 160 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

            #line 162 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 171 "src/obdh/pus/services/service3.fin"
            status._variant = Status__Failure;
            #line 171 "src/obdh/pus/services/service3.fin"
            status.Failure._0._variant = PUSService3Error__SIDNotValid;
            #line 171 "src/obdh/pus/services/service3.fin"
            status.Failure._0.SIDNotValid._0 = tc_request->SID;

        }

    }

    #line 179 "src/obdh/pus/services/service3.fin"
    return status;

}

static Status__PUSService3Error CPUSService3__exec3_5TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3TCRequest * const tc_request) {
    
    #line 52 "src/obdh/pus/services/service3.fin"
    Status__PUSService3Error status = { ._variant = Status__Success };

    #line 54 "src/obdh/pus/services/service3.fin"
    if (tc_request->N != 1U) {
        
        #line 56 "src/obdh/pus/services/service3.fin"
        status._variant = Status__Failure;
        #line 56 "src/obdh/pus/services/service3.fin"
        status.Failure._0._variant = PUSService3Error__NumOfInstrNotValid;
        #line 56 "src/obdh/pus/services/service3.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 60 "src/obdh/pus/services/service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, tc_request);

        #line 64 "src/obdh/pus/services/service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 64 "src/obdh/pus/services/service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 66 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            #line 71 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].enabled = true;

            #line 72 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

            #line 74 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 83 "src/obdh/pus/services/service3.fin"
            status._variant = Status__Failure;
            #line 83 "src/obdh/pus/services/service3.fin"
            status.Failure._0._variant = PUSService3Error__SIDNotValid;
            #line 83 "src/obdh/pus/services/service3.fin"
            status.Failure._0.SIDNotValid._0 = tc_request->SID;

        }

    }

    #line 91 "src/obdh/pus/services/service3.fin"
    return status;

}

static Status__PUSService3Error CPUSService3__exec3_6TC(const termina__event_t * const termina__ev, CPUSService3 * const self, const PS3TCRequest * const tc_request) {
    
    #line 96 "src/obdh/pus/services/service3.fin"
    Status__PUSService3Error status = { ._variant = Status__Success };

    #line 98 "src/obdh/pus/services/service3.fin"
    if (tc_request->N != 1U) {
        
        #line 100 "src/obdh/pus/services/service3.fin"
        status._variant = Status__Failure;
        #line 100 "src/obdh/pus/services/service3.fin"
        status.Failure._0._variant = PUSService3Error__NumOfInstrNotValid;
        #line 100 "src/obdh/pus/services/service3.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    {
        
        #line 104 "src/obdh/pus/services/service3.fin"
        Option__usize opt_index = CPUSService3__get_SIDindex(termina__ev, self, tc_request);

        #line 108 "src/obdh/pus/services/service3.fin"
        if (opt_index._variant == Option__Some) {
            
            #line 108 "src/obdh/pus/services/service3.fin"
            const size_t sid_index = opt_index.Some._0;

            #line 110 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            #line 115 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].enabled = false;

            #line 116 "src/obdh/pus/services/service3.fin"
            self->hk_config_table[termina__check__array_index(8U, sid_index)].interval_control = 0U;

            #line 118 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 127 "src/obdh/pus/services/service3.fin"
            status._variant = Status__Failure;
            #line 127 "src/obdh/pus/services/service3.fin"
            status.Failure._0._variant = PUSService3Error__SIDNotValid;
            #line 127 "src/obdh/pus/services/service3.fin"
            status.Failure._0.SIDNotValid._0 = tc_request->SID;

        }

    }

    #line 134 "src/obdh/pus/services/service3.fin"
    return status;

}

void CPUSService3__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 184 "src/obdh/pus/services/service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 184 "src/obdh/pus/services/service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 186 "src/obdh/pus/services/service3.fin"
    Status__PUSService3Error status = { ._variant = Status__Success };

    #line 187 "src/obdh/pus/services/service3.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 188 "src/obdh/pus/services/service3.fin"
    PS3TCRequest tc_request = { .N = 0U, .SID = 0U, .collection_interval = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 190 "src/obdh/pus/services/service3.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 191 "src/obdh/pus/services/service3.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 192 "src/obdh/pus/services/service3.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 193 "src/obdh/pus/services/service3.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 195 "src/obdh/pus/services/service3.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    #line 197 "src/obdh/pus/services/service3.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 198 "src/obdh/pus/services/service3.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.SID);

    }

    #line 201 "src/obdh/pus/services/service3.fin"
    if (tc_data_status._variant == Status__Success && subtype == 31U) {
        
        #line 202 "src/obdh/pus/services/service3.fin"
        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.collection_interval);

    }

    #line 205 "src/obdh/pus/services/service3.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 206 "src/obdh/pus/services/service3.fin"
        status._variant = Status__Failure;
        #line 206 "src/obdh/pus/services/service3.fin"
        status.Failure._0._variant = PUSService3Error__AppDataOutOfRange;
        #line 206 "src/obdh/pus/services/service3.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 209 "src/obdh/pus/services/service3.fin"
    if (status._variant == Status__Success) {
        
        #line 211 "src/obdh/pus/services/service3.fin"
        if (subtype == 5U) {
            
            #line 213 "src/obdh/pus/services/service3.fin"
            status = CPUSService3__exec3_5TC(termina__ev, self, &tc_request);

        } else
        #line 215 "src/obdh/pus/services/service3.fin"
        if (subtype == 6U) {
            
            #line 217 "src/obdh/pus/services/service3.fin"
            status = CPUSService3__exec3_6TC(termina__ev, self, &tc_request);

        } else
        #line 219 "src/obdh/pus/services/service3.fin"
        if (subtype == 31U) {
            
            #line 221 "src/obdh/pus/services/service3.fin"
            status = CPUSService3__exec3_31TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 225 "src/obdh/pus/services/service3.fin"
            status._variant = Status__Failure;
            #line 225 "src/obdh/pus/services/service3.fin"
            status.Failure._0._variant = PUSService3Error__ErrorInAcceptance;

        }

    }

    #line 233 "src/obdh/pus/services/service3.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 236 "src/obdh/pus/services/service3.fin"
        const PUSService3Error error = status.Failure._0;

        #line 240 "src/obdh/pus/services/service3.fin"
        if (error._variant == PUSService3Error__ErrorInAcceptance) {
            
            #line 242 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 247 "src/obdh/pus/services/service3.fin"
        if (error._variant == PUSService3Error__AppDataOutOfRange) {
            
            #line 247 "src/obdh/pus/services/service3.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 249 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 255 "src/obdh/pus/services/service3.fin"
        if (error._variant == PUSService3Error__NumOfInstrNotValid) {
            
            #line 255 "src/obdh/pus/services/service3.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 257 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        {
            
            #line 263 "src/obdh/pus/services/service3.fin"
            const uint16_t SID = error.SIDNotValid._0;

            #line 265 "src/obdh/pus/services/service3.fin"
            self->pus_service_1.send_tm_1_4_SID_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, SID);

        }

    }

    #line 276 "src/obdh/pus/services/service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 276 "src/obdh/pus/services/service3.fin"
    return;

}

void CPUSService3__update_params(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 358 "src/obdh/pus/services/service3.fin"
    CPUSService3 * self = (CPUSService3 *)termina__this;

    #line 358 "src/obdh/pus/services/service3.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 360 "src/obdh/pus/services/service3.fin"
    for (size_t i = 0U; i < 5U; i = i + 1U) {
        
        #line 362 "src/obdh/pus/services/service3.fin"
        uint32_t random_noise = (uint32_t)(rand_r(&self->random_seed) % 11U) - 5U;

        #line 363 "src/obdh/pus/services/service3.fin"
        uint32_t data = 0U;

        #line 365 "src/obdh/pus/services/service3.fin"
        data = atomic_load(&self->system_data_pool_u32[i]);

        #line 366 "src/obdh/pus/services/service3.fin"
        data = data + random_noise;

        #line 368 "src/obdh/pus/services/service3.fin"
        atomic_store(&self->system_data_pool_u32[i], data);

    }

    #line 371 "src/obdh/pus/services/service3.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 371 "src/obdh/pus/services/service3.fin"
    return;

}
