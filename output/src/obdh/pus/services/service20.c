
#include "obdh/pus/services/service20.h"

static Status__PUSService20Error CPUSService20__exec20_1TC(const termina__event_t * const termina__ev, CPUSService20 * const self, const PS20TCRequest * const tc_request);

static Status__PUSService20Error CPUSService20__exec20_3TC(const termina__event_t * const termina__ev, CPUSService20 * const self, const PS20TCRequest * const tc_request);

static Status__PUSService20Error CPUSService20__exec20_1TC(const termina__event_t * const termina__ev, CPUSService20 * const self, const PS20TCRequest * const tc_request) {
    
    #line 26 "src/obdh/pus/services/service20.fin"
    Status__PUSService20Error status = { ._variant = Status__Success };

    #line 28 "src/obdh/pus/services/service20.fin"
    if (tc_request->N != 1U) {
        
        #line 30 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 30 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__NumOfInstrNotValid;
        #line 30 "src/obdh/pus/services/service20.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 32 "src/obdh/pus/services/service20.fin"
    if (sys_data_pool_is_valid_PID(tc_request->PID) == false) {
        
        #line 34 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 34 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__PIDNotValid;
        #line 34 "src/obdh/pus/services/service20.fin"
        status.Failure._0.PIDNotValid._0 = tc_request->PID;

    } else
    {
        
        #line 38 "src/obdh/pus/services/service20.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 43 "src/obdh/pus/services/service20.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 44 "src/obdh/pus/services/service20.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 48 "src/obdh/pus/services/service20.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 48 "src/obdh/pus/services/service20.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 50 "src/obdh/pus/services/service20.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 51 "src/obdh/pus/services/service20.fin"
            uint16_t tm_count = 0U;

            #line 53 "src/obdh/pus/services/service20.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 55 "src/obdh/pus/services/service20.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 57 "src/obdh/pus/services/service20.fin"
            Status__TMHandlerError tm_status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, 1U);

            #line 58 "src/obdh/pus/services/service20.fin"
            _Bool valid_PID = true;

            #line 60 "src/obdh/pus/services/service20.fin"
            if (tm_status._variant == Status__Success) {
                
                #line 61 "src/obdh/pus/services/service20.fin"
                tm_status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, (uint16_t)tc_request->PID);

            }

            #line 64 "src/obdh/pus/services/service20.fin"
            if (tm_status._variant == Status__Success) {
                
                #line 65 "src/obdh/pus/services/service20.fin"
                DataPoolItem item_type = sys_data_pool_get_item(tc_request->PID);

                #line 68 "src/obdh/pus/services/service20.fin"
                if (item_type._variant == DataPoolItem__U8Item) {
                    
                    #line 68 "src/obdh/pus/services/service20.fin"
                    const size_t sdp_index = item_type.U8Item._0;

                    #line 69 "src/obdh/pus/services/service20.fin"
                    uint8_t u8_SDP_value = 0U;

                    #line 70 "src/obdh/pus/services/service20.fin"
                    u8_SDP_value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

                    #line 71 "src/obdh/pus/services/service20.fin"
                    tm_status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, u8_SDP_value);

                } else
                #line 73 "src/obdh/pus/services/service20.fin"
                if (item_type._variant == DataPoolItem__U32Item) {
                    
                    #line 73 "src/obdh/pus/services/service20.fin"
                    const size_t sdp_index = item_type.U32Item._0;

                    #line 74 "src/obdh/pus/services/service20.fin"
                    uint32_t u32_SDP_value = 0U;

                    #line 75 "src/obdh/pus/services/service20.fin"
                    u32_SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

                    #line 76 "src/obdh/pus/services/service20.fin"
                    tm_status = append_u32_appdata_field((TMHandler *)b_tm_handler.data, u32_SDP_value);

                } else
                {
                    
                    #line 79 "src/obdh/pus/services/service20.fin"
                    valid_PID = false;

                }

            }

            #line 84 "src/obdh/pus/services/service20.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 86 "src/obdh/pus/services/service20.fin"
            if (tm_status._variant == Status__Success && valid_PID) {
                
                #line 87 "src/obdh/pus/services/service20.fin"
                close_tm((TMHandler *)b_tm_handler.data, 20U, 2U, tm_count, current_obt);

                #line 88 "src/obdh/pus/services/service20.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 90 "src/obdh/pus/services/service20.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 91 "src/obdh/pus/services/service20.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        } else
        {
            
            #line 97 "src/obdh/pus/services/service20.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

        #line 102 "src/obdh/pus/services/service20.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    }

    #line 109 "src/obdh/pus/services/service20.fin"
    return status;

}

static Status__PUSService20Error CPUSService20__exec20_3TC(const termina__event_t * const termina__ev, CPUSService20 * const self, const PS20TCRequest * const tc_request) {
    
    #line 116 "src/obdh/pus/services/service20.fin"
    Status__PUSService20Error status = { ._variant = Status__Success };

    #line 118 "src/obdh/pus/services/service20.fin"
    if (tc_request->N != 1U) {
        
        #line 120 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 120 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__NumOfInstrNotValid;
        #line 120 "src/obdh/pus/services/service20.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 122 "src/obdh/pus/services/service20.fin"
    if (sys_data_pool_is_valid_PID(tc_request->PID) == false) {
        
        #line 124 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 124 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__PIDNotValid;
        #line 124 "src/obdh/pus/services/service20.fin"
        status.Failure._0.PIDNotValid._0 = tc_request->PID;

    } else
    #line 126 "src/obdh/pus/services/service20.fin"
    if (sys_data_pool_is_PID_update_via_TC_enabled(tc_request->PID) == false) {
        
        #line 128 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 128 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__PIDReadOnlyViaTC;
        #line 128 "src/obdh/pus/services/service20.fin"
        status.Failure._0.PIDReadOnlyViaTC._0 = tc_request->PID;

    } else
    {
        
        #line 132 "src/obdh/pus/services/service20.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 137 "src/obdh/pus/services/service20.fin"
        DataPoolItem item_type = sys_data_pool_get_item(tc_request->PID);

        #line 140 "src/obdh/pus/services/service20.fin"
        if (item_type._variant == DataPoolItem__U8Item) {
            
            #line 140 "src/obdh/pus/services/service20.fin"
            const size_t sdp_index = item_type.U8Item._0;

            #line 141 "src/obdh/pus/services/service20.fin"
            atomic_store(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)], tc_request->tc_20_3_data.PID_value_u8);

        } else
        #line 143 "src/obdh/pus/services/service20.fin"
        if (item_type._variant == DataPoolItem__U32Item) {
            
            #line 143 "src/obdh/pus/services/service20.fin"
            const size_t sdp_index = item_type.U32Item._0;

            #line 144 "src/obdh/pus/services/service20.fin"
            atomic_store(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)], tc_request->tc_20_3_data.PID_value_u32);

        } else
        {
            
            #line 147 "src/obdh/pus/services/service20.fin"
            status._variant = Status__Failure;
            #line 147 "src/obdh/pus/services/service20.fin"
            status.Failure._0._variant = PUSService20Error__PIDNotValid;
            #line 147 "src/obdh/pus/services/service20.fin"
            status.Failure._0.PIDNotValid._0 = tc_request->PID;

        }

        #line 151 "src/obdh/pus/services/service20.fin"
        if (status._variant == Status__Success) {
            
            #line 153 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        }

    }

    #line 162 "src/obdh/pus/services/service20.fin"
    return status;

}

void CPUSService20__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 166 "src/obdh/pus/services/service20.fin"
    CPUSService20 * self = (CPUSService20 *)termina__this;

    #line 166 "src/obdh/pus/services/service20.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 168 "src/obdh/pus/services/service20.fin"
    Status__PUSService20Error status = { ._variant = Status__Success };

    #line 169 "src/obdh/pus/services/service20.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 170 "src/obdh/pus/services/service20.fin"
    PS20TCRequest tc_request = { .N = 0U, .PID = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_20_3_data = { .PID_value_u32 = 0U, .PID_value_u8 = 0U }, .tc_num_bytes = 0U };

    #line 172 "src/obdh/pus/services/service20.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 173 "src/obdh/pus/services/service20.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 174 "src/obdh/pus/services/service20.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 175 "src/obdh/pus/services/service20.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 177 "src/obdh/pus/services/service20.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    #line 179 "src/obdh/pus/services/service20.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 180 "src/obdh/pus/services/service20.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.PID);

    }

    #line 183 "src/obdh/pus/services/service20.fin"
    if (tc_data_status._variant == Status__Success && subtype == 3U) {
        
        #line 185 "src/obdh/pus/services/service20.fin"
        DataPoolItem item_type = sys_data_pool_get_item(tc_request.PID);

        #line 188 "src/obdh/pus/services/service20.fin"
        if (item_type._variant == DataPoolItem__U8Item) {
            
            #line 188 "src/obdh/pus/services/service20.fin"
            const size_t sdp_index = item_type.U8Item._0;

            #line 189 "src/obdh/pus/services/service20.fin"
            tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_20_3_data.PID_value_u8);

        } else
        #line 191 "src/obdh/pus/services/service20.fin"
        if (item_type._variant == DataPoolItem__U32Item) {
            
            #line 191 "src/obdh/pus/services/service20.fin"
            const size_t sdp_index = item_type.U32Item._0;

            #line 192 "src/obdh/pus/services/service20.fin"
            tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &tc_request.tc_20_3_data.PID_value_u32);

        } else
        {
            
            #line 195 "src/obdh/pus/services/service20.fin"
            status._variant = Status__Failure;
            #line 195 "src/obdh/pus/services/service20.fin"
            status.Failure._0._variant = PUSService20Error__PIDNotValid;
            #line 195 "src/obdh/pus/services/service20.fin"
            status.Failure._0.PIDNotValid._0 = tc_request.PID;

        }

    }

    #line 201 "src/obdh/pus/services/service20.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 202 "src/obdh/pus/services/service20.fin"
        status._variant = Status__Failure;
        #line 202 "src/obdh/pus/services/service20.fin"
        status.Failure._0._variant = PUSService20Error__AppDataOutOfRange;
        #line 202 "src/obdh/pus/services/service20.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 205 "src/obdh/pus/services/service20.fin"
    if (status._variant == Status__Success) {
        
        #line 207 "src/obdh/pus/services/service20.fin"
        if (subtype == 1U) {
            
            #line 209 "src/obdh/pus/services/service20.fin"
            status = CPUSService20__exec20_1TC(termina__ev, self, &tc_request);

        } else
        #line 211 "src/obdh/pus/services/service20.fin"
        if (subtype == 3U) {
            
            #line 213 "src/obdh/pus/services/service20.fin"
            status = CPUSService20__exec20_3TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 217 "src/obdh/pus/services/service20.fin"
            status._variant = Status__Failure;
            #line 217 "src/obdh/pus/services/service20.fin"
            status.Failure._0._variant = PUSService20Error__ErrorInAcceptance;

        }

    }

    #line 225 "src/obdh/pus/services/service20.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 228 "src/obdh/pus/services/service20.fin"
        const PUSService20Error error = status.Failure._0;

        #line 232 "src/obdh/pus/services/service20.fin"
        if (error._variant == PUSService20Error__ErrorInAcceptance) {
            
            #line 234 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 239 "src/obdh/pus/services/service20.fin"
        if (error._variant == PUSService20Error__AppDataOutOfRange) {
            
            #line 239 "src/obdh/pus/services/service20.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 241 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 247 "src/obdh/pus/services/service20.fin"
        if (error._variant == PUSService20Error__NumOfInstrNotValid) {
            
            #line 247 "src/obdh/pus/services/service20.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 249 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        #line 255 "src/obdh/pus/services/service20.fin"
        if (error._variant == PUSService20Error__PIDNotValid) {
            
            #line 255 "src/obdh/pus/services/service20.fin"
            const uint16_t PID = error.PIDNotValid._0;

            #line 257 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        } else
        {
            
            #line 263 "src/obdh/pus/services/service20.fin"
            const uint16_t PID = error.PIDReadOnlyViaTC._0;

            #line 265 "src/obdh/pus/services/service20.fin"
            self->pus_service_1.send_tm_1_4_PID_read_only_via_TC(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        }

    }

    #line 276 "src/obdh/pus/services/service20.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 276 "src/obdh/pus/services/service20.fin"
    return;

}
