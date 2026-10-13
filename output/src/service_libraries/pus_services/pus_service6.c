
#include "service_libraries/pus_services/pus_service6.h"

static uint16_t CPUSService6__check_data(const termina__event_t * const termina__ev, CPUSService6 * const self);

static _Bool CPUSService6__is_address_valid(const termina__event_t * const termina__ev, const CPUSService6 * const self);

static _Bool CPUSService6__is_mem_id_write_enabled(const termina__event_t * const termina__ev, const CPUSService6 * const self);

static Status__i32 CPUSService6__write_data(const termina__event_t * const termina__ev, CPUSService6 * const self);

static Status__i32 CPUSService6__exec6_2TC(const termina__event_t * const termina__ev, CPUSService6 * const self);

static Status__i32 CPUSService6__read_data(const termina__event_t * const termina__ev, CPUSService6 * const self);

static Status__i32 CPUSService6__exec6_5TC(const termina__event_t * const termina__ev, CPUSService6 * const self);

static Status__i32 CPUSService6__exec6_9TC(const termina__event_t * const termina__ev, CPUSService6 * const self);

static uint16_t CPUSService6__check_data(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    (void)termina__ev;

    #line 86 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t bank_index = (size_t)self->exec_tc_req_status_update.mem_id;

    #line 87 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t start_address = (size_t)self->exec_tc_req_status_update.address;

    #line 88 "src/service_libraries/pus_services/pus_service6.fin"
    uint8_t data[256U] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

    #line 89 "src/service_libraries/pus_services/pus_service6.fin"
    for (size_t i = 0U; i < 256U && i < (size_t)self->exec_tc_req_status_update.length; i = i + 1U) {
        
        #line 90 "src/service_libraries/pus_services/pus_service6.fin"
        data[i] = self->memory[termina__check__array_index(8U, bank_index)][termina__check__array_index(16777216U, start_address + i)];

    }

    #line 93 "src/service_libraries/pus_services/pus_service6.fin"
    uint16_t checksum = cal_crc_16(data, (size_t)self->exec_tc_req_status_update.length);

    #line 96 "src/service_libraries/pus_services/pus_service6.fin"
    return checksum;

}

static _Bool CPUSService6__is_address_valid(const termina__event_t * const termina__ev, const CPUSService6 * const self) {
    
    (void)termina__ev;

    #line 33 "src/service_libraries/pus_services/pus_service6.fin"
    _Bool is_valid = true;

    #line 35 "src/service_libraries/pus_services/pus_service6.fin"
    if ((size_t)self->exec_tc_req_status_update.mem_id >= 8U) {
        
        #line 36 "src/service_libraries/pus_services/pus_service6.fin"
        is_valid = false;

    } else
    #line 37 "src/service_libraries/pus_services/pus_service6.fin"
    if ((size_t)self->exec_tc_req_status_update.address >= 16777216U) {
        
        #line 38 "src/service_libraries/pus_services/pus_service6.fin"
        is_valid = false;

    } else
    #line 39 "src/service_libraries/pus_services/pus_service6.fin"
    if ((size_t)((size_t)self->exec_tc_req_status_update.address + (size_t)self->exec_tc_req_status_update.length) > 16777216U) {
        
        #line 40 "src/service_libraries/pus_services/pus_service6.fin"
        is_valid = false;

    } else
    #line 41 "src/service_libraries/pus_services/pus_service6.fin"
    if ((size_t)self->exec_tc_req_status_update.length > 256U) {
        
        #line 42 "src/service_libraries/pus_services/pus_service6.fin"
        is_valid = false;

    } else
    {
        

    }

    #line 47 "src/service_libraries/pus_services/pus_service6.fin"
    return is_valid;

}

static _Bool CPUSService6__is_mem_id_write_enabled(const termina__event_t * const termina__ev, const CPUSService6 * const self) {
    
    (void)termina__ev;

    #line 53 "src/service_libraries/pus_services/pus_service6.fin"
    return self->mem_id_write_permissions[termina__check__array_index(8U, (size_t)self->exec_tc_req_status_update.mem_id)] == true;

}

static Status__i32 CPUSService6__write_data(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    (void)termina__ev;

    #line 59 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 61 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t bank_index = (size_t)self->exec_tc_req_status_update.mem_id;

    #line 62 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t start_address = (size_t)self->exec_tc_req_status_update.address;

    #line 64 "src/service_libraries/pus_services/pus_service6.fin"
    for (size_t i = 0U; i < 256U && i < (size_t)self->exec_tc_req_status_update.length; i = i + 1U) {
        
        #line 65 "src/service_libraries/pus_services/pus_service6.fin"
        self->memory[termina__check__array_index(8U, bank_index)][termina__check__array_index(16777216U, start_address + i)] = self->exec_tc_req_status_update.data[i];

    }

    #line 68 "src/service_libraries/pus_services/pus_service6.fin"
    return status;

}

static Status__i32 CPUSService6__exec6_2TC(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    #line 101 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 103 "src/service_libraries/pus_services/pus_service6.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 105 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 111 "src/service_libraries/pus_services/pus_service6.fin"
    if (CPUSService6__is_address_valid(termina__ev, self) == false) {
        
        #line 113 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_mem_address_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, self->exec_tc_req_status_update.address, &status);

    } else
    #line 120 "src/service_libraries/pus_services/pus_service6.fin"
    if (CPUSService6__is_mem_id_write_enabled(termina__ev, self) == false) {
        
        #line 122 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_mem_id_read_only(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, &status);

    } else
    {
        
        #line 130 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 136 "src/service_libraries/pus_services/pus_service6.fin"
        if (status._variant == Status__Success) {
            
            #line 137 "src/service_libraries/pus_services/pus_service6.fin"
            status = CPUSService6__write_data(termina__ev, self);

        }

        #line 140 "src/service_libraries/pus_services/pus_service6.fin"
        if (status._variant == Status__Success) {
            
            #line 142 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        } else
        {
            
            #line 150 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.send_tm_1_8_mem_access_error(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, &status);

        }

    }

    #line 160 "src/service_libraries/pus_services/pus_service6.fin"
    return status;

}

static Status__i32 CPUSService6__read_data(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    (void)termina__ev;

    #line 73 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 74 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t bank_index = (size_t)self->exec_tc_req_status_update.mem_id;

    #line 75 "src/service_libraries/pus_services/pus_service6.fin"
    const size_t start_address = (size_t)self->exec_tc_req_status_update.address;

    #line 77 "src/service_libraries/pus_services/pus_service6.fin"
    for (size_t i = 0U; i < 256U && i < (size_t)self->exec_tc_req_status_update.length; i = i + 1U) {
        
        #line 78 "src/service_libraries/pus_services/pus_service6.fin"
        self->exec_tc_req_status_update.data[i] = self->memory[termina__check__array_index(8U, bank_index)][termina__check__array_index(16777216U, start_address + i)];

    }

    #line 81 "src/service_libraries/pus_services/pus_service6.fin"
    return status;

}

static Status__i32 CPUSService6__exec6_5TC(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    #line 166 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 168 "src/service_libraries/pus_services/pus_service6.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 170 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 176 "src/service_libraries/pus_services/pus_service6.fin"
    if (CPUSService6__is_address_valid(termina__ev, self) == false) {
        
        #line 178 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_mem_address_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, self->exec_tc_req_status_update.address, &status);

    } else
    {
        
        #line 187 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 193 "src/service_libraries/pus_services/pus_service6.fin"
        if (status._variant == Status__Success) {
            
            #line 195 "src/service_libraries/pus_services/pus_service6.fin"
            status = CPUSService6__read_data(termina__ev, self);

        }

        #line 199 "src/service_libraries/pus_services/pus_service6.fin"
        if (status._variant == Status__Success) {
            
            #line 201 "src/service_libraries/pus_services/pus_service6.fin"
            Option__box tm_handler = { ._variant = Option__None };

            #line 202 "src/service_libraries/pus_services/pus_service6.fin"
            self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

            #line 206 "src/service_libraries/pus_services/pus_service6.fin"
            if (tm_handler._variant == Option__Some) {
                
                #line 206 "src/service_libraries/pus_services/pus_service6.fin"
                const termina__box_t b_tm_handler = tm_handler.Some._0;

                #line 208 "src/service_libraries/pus_services/pus_service6.fin"
                MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

                #line 209 "src/service_libraries/pus_services/pus_service6.fin"
                uint16_t tm_count = 0U;

                #line 211 "src/service_libraries/pus_services/pus_service6.fin"
                self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

                #line 212 "src/service_libraries/pus_services/pus_service6.fin"
                self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

                #line 214 "src/service_libraries/pus_services/pus_service6.fin"
                status = build_tm_6_6((TMHandler *)b_tm_handler.data, tm_count, current_obt, &self->exec_tc_req_status_update);

                #line 216 "src/service_libraries/pus_services/pus_service6.fin"
                if (status._variant == Status__Success) {
                    
                    #line 217 "src/service_libraries/pus_services/pus_service6.fin"
                    self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &status);

                } else
                {
                    
                    #line 219 "src/service_libraries/pus_services/pus_service6.fin"
                    self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                }

                #line 222 "src/service_libraries/pus_services/pus_service6.fin"
                if (status._variant == Status__Success) {
                    
                    #line 224 "src/service_libraries/pus_services/pus_service6.fin"
                    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

                }

            } else
            {
                
                #line 235 "src/service_libraries/pus_services/pus_service6.fin"
                status._variant = Status__Failure;
                #line 235 "src/service_libraries/pus_services/pus_service6.fin"
                status.Failure._0 = 1L;

            }

        } else
        {
            
            #line 241 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.send_tm_1_8_mem_access_error(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, &status);

        }

    }

    #line 251 "src/service_libraries/pus_services/pus_service6.fin"
    return status;

}

static Status__i32 CPUSService6__exec6_9TC(const termina__event_t * const termina__ev, CPUSService6 * const self) {
    
    #line 257 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 259 "src/service_libraries/pus_services/pus_service6.fin"
    if (self->exec_tc_req_status_update.N != 1U) {
        
        #line 261 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.N, &status);

    } else
    #line 267 "src/service_libraries/pus_services/pus_service6.fin"
    if (CPUSService6__is_address_valid(termina__ev, self) == false) {
        
        #line 269 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.send_tm_1_4_mem_address_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.mem_id, self->exec_tc_req_status_update.address, &status);

    } else
    {
        
        #line 278 "src/service_libraries/pus_services/pus_service6.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

        #line 283 "src/service_libraries/pus_services/pus_service6.fin"
        const uint16_t checksum = CPUSService6__check_data(termina__ev, self);

        #line 285 "src/service_libraries/pus_services/pus_service6.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 286 "src/service_libraries/pus_services/pus_service6.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 290 "src/service_libraries/pus_services/pus_service6.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 290 "src/service_libraries/pus_services/pus_service6.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 292 "src/service_libraries/pus_services/pus_service6.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 293 "src/service_libraries/pus_services/pus_service6.fin"
            uint16_t tm_count = 0U;

            #line 294 "src/service_libraries/pus_services/pus_service6.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 295 "src/service_libraries/pus_services/pus_service6.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 297 "src/service_libraries/pus_services/pus_service6.fin"
            status = build_tm_6_10((TMHandler *)b_tm_handler.data, tm_count, current_obt, &self->exec_tc_req_status_update, checksum);

            #line 299 "src/service_libraries/pus_services/pus_service6.fin"
            if (status._variant == Status__Success) {
                
                #line 300 "src/service_libraries/pus_services/pus_service6.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, &status);

            } else
            {
                
                #line 302 "src/service_libraries/pus_services/pus_service6.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            }

            #line 305 "src/service_libraries/pus_services/pus_service6.fin"
            if (status._variant == Status__Success) {
                
                #line 307 "src/service_libraries/pus_services/pus_service6.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.flags_ack, &status);

            }

        } else
        {
            
            #line 318 "src/service_libraries/pus_services/pus_service6.fin"
            status._variant = Status__Failure;
            #line 318 "src/service_libraries/pus_services/pus_service6.fin"
            status.Failure._0 = 1L;

        }

    }

    #line 324 "src/service_libraries/pus_services/pus_service6.fin"
    return status;

}

void CPUSService6__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 328 "src/service_libraries/pus_services/pus_service6.fin"
    CPUSService6 * self = (CPUSService6 *)termina__this;

    #line 328 "src/service_libraries/pus_services/pus_service6.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 330 "src/service_libraries/pus_services/pus_service6.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 332 "src/service_libraries/pus_services/pus_service6.fin"
    self->exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 333 "src/service_libraries/pus_services/pus_service6.fin"
    self->exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 334 "src/service_libraries/pus_services/pus_service6.fin"
    self->exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 335 "src/service_libraries/pus_services/pus_service6.fin"
    self->exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 337 "src/service_libraries/pus_services/pus_service6.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.mem_id);

    #line 339 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success) {
        
        #line 340 "src/service_libraries/pus_services/pus_service6.fin"
        status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.N);

    }

    #line 343 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success) {
        
        #line 344 "src/service_libraries/pus_services/pus_service6.fin"
        status = tc_handler_get_u32_appdata_field(tc_handler, &self->exec_tc_req_status_update.address);

    }

    #line 347 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success) {
        
        #line 348 "src/service_libraries/pus_services/pus_service6.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.length);

    }

    #line 351 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success && subtype == 2U) {
        
        #line 352 "src/service_libraries/pus_services/pus_service6.fin"
        for (size_t j = 0U; j < 256U && (j < (size_t)self->exec_tc_req_status_update.length && status._variant == Status__Success); j = j + 1U) {
            
            #line 353 "src/service_libraries/pus_services/pus_service6.fin"
            status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.data[j]);

        }

    }

    #line 357 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success) {
        
        #line 359 "src/service_libraries/pus_services/pus_service6.fin"
        if (subtype == 2U) {
            
            #line 361 "src/service_libraries/pus_services/pus_service6.fin"
            status = CPUSService6__exec6_2TC(termina__ev, self);

        } else
        #line 363 "src/service_libraries/pus_services/pus_service6.fin"
        if (subtype == 5U) {
            
            #line 365 "src/service_libraries/pus_services/pus_service6.fin"
            status = CPUSService6__exec6_5TC(termina__ev, self);

        } else
        #line 367 "src/service_libraries/pus_services/pus_service6.fin"
        if (subtype == 9U) {
            
            #line 369 "src/service_libraries/pus_services/pus_service6.fin"
            status = CPUSService6__exec6_9TC(termina__ev, self);

        } else
        {
            
            #line 373 "src/service_libraries/pus_services/pus_service6.fin"
            status._variant = Status__Failure;
            #line 373 "src/service_libraries/pus_services/pus_service6.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 380 "src/service_libraries/pus_services/pus_service6.fin"
    if (status._variant == Status__Success) {
        
        #line 382 "src/service_libraries/pus_services/pus_service6.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 385 "src/service_libraries/pus_services/pus_service6.fin"
        const int32_t error_code = status.Failure._0;

        #line 387 "src/service_libraries/pus_services/pus_service6.fin"
        if (error_code == 4L) {
            
            #line 389 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 394 "src/service_libraries/pus_services/pus_service6.fin"
        if (error_code == 3L) {
            
            #line 396 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 401 "src/service_libraries/pus_services/pus_service6.fin"
        if (error_code == 5L) {
            
            #line 403 "src/service_libraries/pus_services/pus_service6.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.packet_id, self->exec_tc_req_status_update.packet_seq_ctrl, self->exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        {
            
            #line 411 "src/service_libraries/pus_services/pus_service6.fin"
            (*action_status)._variant = Status__Failure;
            #line 411 "src/service_libraries/pus_services/pus_service6.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 418 "src/service_libraries/pus_services/pus_service6.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 418 "src/service_libraries/pus_services/pus_service6.fin"
    return;

}
