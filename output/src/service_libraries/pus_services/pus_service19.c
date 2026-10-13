
#include "service_libraries/pus_services/pus_service19.h"

static Status__i32 CPUSService19__delete_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__disable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__enable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self);

static FoundID CPUSService19__get_free_event_action_index(const termina__event_t * const termina__ev, const CPUSService19 * const self);

static FoundID CPUSService19__is_ev_action_defined(const termina__event_t * const termina__ev, const CPUSService19 * const self, const uint16_t evID);

static Status__i32 CPUSService19__exec19_1TC(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__exec19_2TC(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__exec19_4TC(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__exec19_5TC(const termina__event_t * const termina__ev, CPUSService19 * const self);

static Status__i32 CPUSService19__delete_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    (void)termina__ev;

    #line 67 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 69 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.EvID == self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].event_ID) {
        
        #line 71 "src/service_libraries/pus_services/pus_service19.fin"
        self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].event_ID = 0U;

        #line 72 "src/service_libraries/pus_services/pus_service19.fin"
        self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].enabled = false;

    } else
    {
        
        #line 77 "src/service_libraries/pus_services/pus_service19.fin"
        status._variant = Status__Failure;
        #line 77 "src/service_libraries/pus_services/pus_service19.fin"
        status.Failure._0 = 11L;

    }

    #line 80 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static Status__i32 CPUSService19__disable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    (void)termina__ev;

    #line 35 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 37 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.EvID == self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].event_ID) {
        
        #line 39 "src/service_libraries/pus_services/pus_service19.fin"
        self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].enabled = false;

    } else
    {
        
        #line 43 "src/service_libraries/pus_services/pus_service19.fin"
        status._variant = Status__Failure;
        #line 43 "src/service_libraries/pus_services/pus_service19.fin"
        status.Failure._0 = 11L;

    }

    #line 46 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static Status__i32 CPUSService19__enable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    (void)termina__ev;

    #line 51 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 53 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.EvID == self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].event_ID) {
        
        #line 55 "src/service_libraries/pus_services/pus_service19.fin"
        self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].enabled = true;

    } else
    {
        
        #line 59 "src/service_libraries/pus_services/pus_service19.fin"
        status._variant = Status__Failure;
        #line 59 "src/service_libraries/pus_services/pus_service19.fin"
        status.Failure._0 = 11L;

    }

    #line 62 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static FoundID CPUSService19__get_free_event_action_index(const termina__event_t * const termina__ev, const CPUSService19 * const self) {
    
    (void)termina__ev;

    #line 85 "src/service_libraries/pus_services/pus_service19.fin"
    FoundID found_and_id = { .enabled = false, .ev_action_index = 0U, .found = false };

    #line 87 "src/service_libraries/pus_services/pus_service19.fin"
    for (size_t i = 0U; i < 16U && found_and_id.found == false; i = i + 1U) {
        
        #line 89 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->event_action_config[i].event_ID == 0U) {
            
            #line 91 "src/service_libraries/pus_services/pus_service19.fin"
            found_and_id.ev_action_index = i;

            #line 92 "src/service_libraries/pus_services/pus_service19.fin"
            found_and_id.found = true;

        }

    }

    #line 95 "src/service_libraries/pus_services/pus_service19.fin"
    return found_and_id;

}

static FoundID CPUSService19__is_ev_action_defined(const termina__event_t * const termina__ev, const CPUSService19 * const self, const uint16_t evID) {
    
    (void)termina__ev;

    #line 100 "src/service_libraries/pus_services/pus_service19.fin"
    FoundID found_and_id = { .enabled = false, .ev_action_index = 0U, .found = false };

    #line 102 "src/service_libraries/pus_services/pus_service19.fin"
    for (size_t i = 0U; i < 16U && found_and_id.found == false; i = i + 1U) {
        
        #line 104 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->event_action_config[i].event_ID == evID) {
            
            #line 106 "src/service_libraries/pus_services/pus_service19.fin"
            found_and_id.ev_action_index = i;

            #line 107 "src/service_libraries/pus_services/pus_service19.fin"
            found_and_id.enabled = self->event_action_config[i].enabled;

            #line 108 "src/service_libraries/pus_services/pus_service19.fin"
            found_and_id.found = true;

        }

    }

    #line 111 "src/service_libraries/pus_services/pus_service19.fin"
    return found_and_id;

}

static Status__i32 CPUSService19__exec19_1TC(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    #line 119 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 121 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.N != 1U) {
        
        #line 123 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.N, &status);

    } else
    #line 129 "src/service_libraries/pus_services/pus_service19.fin"
    if (is_Ev_ID_valid(self->exec_tc_req_status_update.tc_data.EvID) == false) {
        
        #line 131 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

    } else
    {
        
        #line 138 "src/service_libraries/pus_services/pus_service19.fin"
        TC19_1_Error error;

        #line 140 "src/service_libraries/pus_services/pus_service19.fin"
        self->exec_tc_req_status_update.ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, self->exec_tc_req_status_update.tc_data.EvID);

        #line 142 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->exec_tc_req_status_update.ev_action_ID.found) {
            
            #line 144 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->exec_tc_req_status_update.ev_action_ID.enabled) {
                
                #line 146 "src/service_libraries/pus_services/pus_service19.fin"
                error._variant = TC19_1_Error__EvIDEnabled;

            } else
            {
                
                #line 150 "src/service_libraries/pus_services/pus_service19.fin"
                error._variant = TC19_1_Error__NoError;

            }

        } else
        {
            
            #line 155 "src/service_libraries/pus_services/pus_service19.fin"
            self->exec_tc_req_status_update.ev_action_ID = CPUSService19__get_free_event_action_index(termina__ev, self);

            #line 157 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->exec_tc_req_status_update.ev_action_ID.found) {
                
                #line 158 "src/service_libraries/pus_services/pus_service19.fin"
                error._variant = TC19_1_Error__NoError;

            } else
            {
                
                #line 161 "src/service_libraries/pus_services/pus_service19.fin"
                error._variant = TC19_1_Error__MaxEventActionDefinitions;

            }

        }

        #line 167 "src/service_libraries/pus_services/pus_service19.fin"
        if (error._variant == TC19_1_Error__NoError) {
            
            #line 169 "src/service_libraries/pus_services/pus_service19.fin"
            TCHandler action_tc_handler = { .app_data_index = 0U, .df_header = { .flag_ver_ack = 0U, .sourceID = 0U, .subtype = 0U, .type = 0U }, .packet_error_ctrl = 0U, .packet_header = { .packet_id = 0U, .packet_length = 0U, .packet_seq_ctrl = 0U }, .tc_descriptor = self->exec_tc_req_status_update.action_tc_packet };

            #line 186 "src/service_libraries/pus_services/pus_service19.fin"
            tc_handler_build(&action_tc_handler);

            #line 188 "src/service_libraries/pus_services/pus_service19.fin"
            TCStatus tc_status = try_tc_acceptation(&self->exec_tc_req_status_update.action_tc_packet);

            #line 190 "src/service_libraries/pus_services/pus_service19.fin"
            if (tc_status.acceptation_status._variant == TCAcceptationStatus__Accepted) {
                
                #line 192 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

                #line 197 "src/service_libraries/pus_services/pus_service19.fin"
                if (status._variant == Status__Success) {
                    
                    #line 199 "src/service_libraries/pus_services/pus_service19.fin"
                    self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].event_ID = self->exec_tc_req_status_update.tc_data.EvID;

                    #line 200 "src/service_libraries/pus_services/pus_service19.fin"
                    self->event_action_config[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)].enabled = false;

                    #line 201 "src/service_libraries/pus_services/pus_service19.fin"
                    self->event_action_packets[termina__check__array_index(16U, self->exec_tc_req_status_update.ev_action_ID.ev_action_index)] = action_tc_handler;

                    #line 203 "src/service_libraries/pus_services/pus_service19.fin"
                    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

                }

            } else
            {
                
                #line 212 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.send_tm_1_4_ev_action_rejected(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

            }

        } else
        #line 221 "src/service_libraries/pus_services/pus_service19.fin"
        if (error._variant == TC19_1_Error__EvIDEnabled) {
            
            #line 223 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_enabled(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

        } else
        {
            
            #line 232 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_8_max_ev_actions_defined(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

        }

    }

    #line 243 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static Status__i32 CPUSService19__exec19_2TC(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    #line 249 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 251 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.N != 1U) {
        
        #line 253 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.N, &status);

    } else
    #line 259 "src/service_libraries/pus_services/pus_service19.fin"
    if (is_Ev_ID_valid(self->exec_tc_req_status_update.tc_data.EvID) == false) {
        
        #line 261 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

    } else
    {
        
        #line 269 "src/service_libraries/pus_services/pus_service19.fin"
        self->exec_tc_req_status_update.ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, self->exec_tc_req_status_update.tc_data.EvID);

        #line 272 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->exec_tc_req_status_update.ev_action_ID.found) {
            
            #line 274 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->exec_tc_req_status_update.ev_action_ID.enabled) {
                
                #line 276 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.send_tm_1_4_ev_action_enabled(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

            } else
            {
                
                #line 284 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

                #line 290 "src/service_libraries/pus_services/pus_service19.fin"
                if (status._variant == Status__Success) {
                    
                    #line 292 "src/service_libraries/pus_services/pus_service19.fin"
                    status = CPUSService19__delete_event_action(termina__ev, self);

                }

                #line 296 "src/service_libraries/pus_services/pus_service19.fin"
                if (status._variant == Status__Success) {
                    
                    #line 298 "src/service_libraries/pus_services/pus_service19.fin"
                    self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

                }

            }

        } else
        {
            
            #line 310 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_undefined(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

        }

    }

    #line 320 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static Status__i32 CPUSService19__exec19_4TC(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    #line 326 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 328 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.N != 1U) {
        
        #line 330 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.N, &status);

    } else
    #line 336 "src/service_libraries/pus_services/pus_service19.fin"
    if (is_Ev_ID_valid(self->exec_tc_req_status_update.tc_data.EvID) == false) {
        
        #line 338 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

    } else
    {
        
        #line 346 "src/service_libraries/pus_services/pus_service19.fin"
        self->exec_tc_req_status_update.ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, self->exec_tc_req_status_update.tc_data.EvID);

        #line 348 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->exec_tc_req_status_update.ev_action_ID.found) {
            
            #line 350 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

            #line 356 "src/service_libraries/pus_services/pus_service19.fin"
            if (status._variant == Status__Success) {
                
                #line 358 "src/service_libraries/pus_services/pus_service19.fin"
                status = CPUSService19__enable_event_action(termina__ev, self);

            }

            #line 362 "src/service_libraries/pus_services/pus_service19.fin"
            if (status._variant == Status__Success) {
                
                #line 364 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

            }

        } else
        {
            
            #line 374 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_undefined(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

        }

    }

    #line 383 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

static Status__i32 CPUSService19__exec19_5TC(const termina__event_t * const termina__ev, CPUSService19 * const self) {
    
    #line 389 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 392 "src/service_libraries/pus_services/pus_service19.fin"
    if (self->exec_tc_req_status_update.tc_data.N != 1U) {
        
        #line 394 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.N, &status);

    } else
    #line 401 "src/service_libraries/pus_services/pus_service19.fin"
    if (is_Ev_ID_valid(self->exec_tc_req_status_update.tc_data.EvID) == false) {
        
        #line 403 "src/service_libraries/pus_services/pus_service19.fin"
        self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

    } else
    {
        
        #line 411 "src/service_libraries/pus_services/pus_service19.fin"
        self->exec_tc_req_status_update.ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, self->exec_tc_req_status_update.tc_data.EvID);

        #line 414 "src/service_libraries/pus_services/pus_service19.fin"
        if (self->exec_tc_req_status_update.ev_action_ID.found) {
            
            #line 416 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

            #line 422 "src/service_libraries/pus_services/pus_service19.fin"
            if (status._variant == Status__Success) {
                
                #line 424 "src/service_libraries/pus_services/pus_service19.fin"
                status = CPUSService19__disable_event_action(termina__ev, self);

            }

            #line 428 "src/service_libraries/pus_services/pus_service19.fin"
            if (status._variant == Status__Success) {
                
                #line 430 "src/service_libraries/pus_services/pus_service19.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.flags_ack, &status);

            }

        } else
        {
            
            #line 440 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_undefined(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.EvID, &status);

        }

    }

    #line 450 "src/service_libraries/pus_services/pus_service19.fin"
    return status;

}

void CPUSService19__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 453 "src/service_libraries/pus_services/pus_service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 453 "src/service_libraries/pus_services/pus_service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 455 "src/service_libraries/pus_services/pus_service19.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 457 "src/service_libraries/pus_services/pus_service19.fin"
    self->exec_tc_req_status_update.tc_data.packet_id = tc_handler->packet_header.packet_id;

    #line 458 "src/service_libraries/pus_services/pus_service19.fin"
    self->exec_tc_req_status_update.tc_data.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 459 "src/service_libraries/pus_services/pus_service19.fin"
    self->exec_tc_req_status_update.tc_data.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 460 "src/service_libraries/pus_services/pus_service19.fin"
    self->exec_tc_req_status_update.tc_data.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 462 "src/service_libraries/pus_services/pus_service19.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &self->exec_tc_req_status_update.tc_data.N);

    #line 464 "src/service_libraries/pus_services/pus_service19.fin"
    if (status._variant == Status__Success) {
        
        #line 465 "src/service_libraries/pus_services/pus_service19.fin"
        status = tc_handler_get_u16_appdata_field(tc_handler, &self->exec_tc_req_status_update.tc_data.EvID);

    }

    #line 468 "src/service_libraries/pus_services/pus_service19.fin"
    if (status._variant == Status__Success && subtype == 1U) {
        
        #line 470 "src/service_libraries/pus_services/pus_service19.fin"
        self->exec_tc_req_status_update.action_tc_packet.tc_num_bytes = (size_t)(tc_handler->tc_descriptor.tc_num_bytes - 2U) - tc_handler->app_data_index;

        #line 472 "src/service_libraries/pus_services/pus_service19.fin"
        for (size_t j = 0U; j < 242U && j < self->exec_tc_req_status_update.action_tc_packet.tc_num_bytes; j = j + 1U) {
            
            #line 474 "src/service_libraries/pus_services/pus_service19.fin"
            self->exec_tc_req_status_update.action_tc_packet.tc_bytes[j] = tc_handler->tc_descriptor.tc_bytes[termina__check__array_index(256U, j + tc_handler->app_data_index)];

        }

    }

    #line 480 "src/service_libraries/pus_services/pus_service19.fin"
    if (status._variant == Status__Success) {
        
        #line 482 "src/service_libraries/pus_services/pus_service19.fin"
        if (subtype == 1U) {
            
            #line 484 "src/service_libraries/pus_services/pus_service19.fin"
            status = CPUSService19__exec19_1TC(termina__ev, self);

        } else
        #line 486 "src/service_libraries/pus_services/pus_service19.fin"
        if (subtype == 2U) {
            
            #line 488 "src/service_libraries/pus_services/pus_service19.fin"
            status = CPUSService19__exec19_2TC(termina__ev, self);

        } else
        #line 490 "src/service_libraries/pus_services/pus_service19.fin"
        if (subtype == 4U) {
            
            #line 492 "src/service_libraries/pus_services/pus_service19.fin"
            status = CPUSService19__exec19_4TC(termina__ev, self);

        } else
        #line 494 "src/service_libraries/pus_services/pus_service19.fin"
        if (subtype == 5U) {
            
            #line 496 "src/service_libraries/pus_services/pus_service19.fin"
            status = CPUSService19__exec19_5TC(termina__ev, self);

        } else
        {
            
            #line 500 "src/service_libraries/pus_services/pus_service19.fin"
            status._variant = Status__Failure;
            #line 500 "src/service_libraries/pus_services/pus_service19.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 508 "src/service_libraries/pus_services/pus_service19.fin"
    if (status._variant == Status__Success) {
        
        #line 510 "src/service_libraries/pus_services/pus_service19.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 513 "src/service_libraries/pus_services/pus_service19.fin"
        const int32_t error_code = status.Failure._0;

        #line 515 "src/service_libraries/pus_services/pus_service19.fin"
        if (error_code == 4L) {
            
            #line 517 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, action_status);

        } else
        #line 522 "src/service_libraries/pus_services/pus_service19.fin"
        if (error_code == 3L) {
            
            #line 524 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, action_status);

        } else
        #line 529 "src/service_libraries/pus_services/pus_service19.fin"
        if (error_code == 5L) {
            
            #line 531 "src/service_libraries/pus_services/pus_service19.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, self->exec_tc_req_status_update.tc_data.packet_id, self->exec_tc_req_status_update.tc_data.packet_seq_ctrl, self->exec_tc_req_status_update.tc_data.tc_num_bytes, action_status);

        } else
        {
            
            #line 539 "src/service_libraries/pus_services/pus_service19.fin"
            (*action_status)._variant = Status__Failure;
            #line 539 "src/service_libraries/pus_services/pus_service19.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 546 "src/service_libraries/pus_services/pus_service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 546 "src/service_libraries/pus_services/pus_service19.fin"
    return;

}

void CPUSService19__extract_action(const termina__event_t * const termina__ev, void * const termina__this, const size_t action_index, TCHandler * const action_packet) {
    
    #line 641 "src/service_libraries/pus_services/pus_service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 641 "src/service_libraries/pus_services/pus_service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 643 "src/service_libraries/pus_services/pus_service19.fin"
    if (action_index == 0U) {
        
        #line 645 "src/service_libraries/pus_services/pus_service19.fin"
        *action_packet = self->pending_action_queue_1I[termina__check__array_index(8U, self->pending_action_head[0U])];

        #line 646 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_head[0U] = (size_t)(self->pending_action_head[0U] + 1U) % 8U;

        #line 647 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_number[0U] = self->pending_action_number[0U] - 1U;

    } else
    #line 649 "src/service_libraries/pus_services/pus_service19.fin"
    if (action_index == 1U) {
        
        #line 651 "src/service_libraries/pus_services/pus_service19.fin"
        *action_packet = self->pending_action_queue_2LS[termina__check__array_index(8U, self->pending_action_head[1U])];

        #line 652 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_head[1U] = (size_t)(self->pending_action_head[1U] + 1U) % 8U;

        #line 653 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_number[1U] = self->pending_action_number[1U] - 1U;

    } else
    #line 655 "src/service_libraries/pus_services/pus_service19.fin"
    if (action_index == 2U) {
        
        #line 657 "src/service_libraries/pus_services/pus_service19.fin"
        *action_packet = self->pending_action_queue_3MS[termina__check__array_index(8U, self->pending_action_head[2U])];

        #line 658 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_head[2U] = (size_t)(self->pending_action_head[2U] + 1U) % 8U;

        #line 659 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_number[2U] = self->pending_action_number[2U] - 1U;

    } else
    #line 661 "src/service_libraries/pus_services/pus_service19.fin"
    if (action_index == 3U) {
        
        #line 663 "src/service_libraries/pus_services/pus_service19.fin"
        *action_packet = self->pending_action_queue_4HS[termina__check__array_index(8U, self->pending_action_head[3U])];

        #line 664 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_head[3U] = (size_t)(self->pending_action_head[3U] + 1U) % 8U;

        #line 665 "src/service_libraries/pus_services/pus_service19.fin"
        self->pending_action_number[3U] = self->pending_action_number[3U] - 1U;

    } else
    {
        

    }

    #line 671 "src/service_libraries/pus_services/pus_service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 671 "src/service_libraries/pus_services/pus_service19.fin"
    return;

}

void CPUSService19__get_pending_action_number(const termina__event_t * const termina__ev, void * const termina__this, size_t paction_num[4U]) {
    
    #line 630 "src/service_libraries/pus_services/pus_service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 630 "src/service_libraries/pus_services/pus_service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 632 "src/service_libraries/pus_services/pus_service19.fin"
    for (size_t i = 0U; i < 3U; i = i + 1U) {
        
        #line 634 "src/service_libraries/pus_services/pus_service19.fin"
        paction_num[i] = self->pending_action_number[i];

    }

    #line 638 "src/service_libraries/pus_services/pus_service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 638 "src/service_libraries/pus_services/pus_service19.fin"
    return;

}

void CPUSService19__manage_event_action(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID) {
    
    #line 550 "src/service_libraries/pus_services/pus_service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 550 "src/service_libraries/pus_services/pus_service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 552 "src/service_libraries/pus_services/pus_service19.fin"
    FoundID found_and_id = CPUSService19__is_ev_action_defined(termina__ev, self, evID);

    #line 554 "src/service_libraries/pus_services/pus_service19.fin"
    if (found_and_id.found && found_and_id.enabled) {
        
        #line 557 "src/service_libraries/pus_services/pus_service19.fin"
        Ev_IDType RID_type = get_Ev_ID_type(evID);

        #line 561 "src/service_libraries/pus_services/pus_service19.fin"
        if (RID_type._variant == Ev_IDType__Informative) {
            
            #line 563 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->pending_action_number[0U] < 8U) {
                
                #line 565 "src/service_libraries/pus_services/pus_service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[0U] + self->pending_action_number[0U]) % 8U;

                #line 566 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_queue_1I[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 567 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_number[0U] = self->pending_action_number[0U] + 1U;

            } else
            {
                

            }

        } else
        #line 575 "src/service_libraries/pus_services/pus_service19.fin"
        if (RID_type._variant == Ev_IDType__LowSeverityAnomaly) {
            
            #line 577 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->pending_action_number[1U] < 8U) {
                
                #line 579 "src/service_libraries/pus_services/pus_service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[1U] + self->pending_action_number[1U]) % 8U;

                #line 580 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_queue_2LS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 581 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_number[1U] = self->pending_action_number[1U] + 1U;

            } else
            {
                

            }

        } else
        #line 589 "src/service_libraries/pus_services/pus_service19.fin"
        if (RID_type._variant == Ev_IDType__MediumSeverityAnomaly) {
            
            #line 591 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->pending_action_number[2U] < 8U) {
                
                #line 593 "src/service_libraries/pus_services/pus_service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[2U] + self->pending_action_number[2U]) % 8U;

                #line 594 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_queue_3MS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 595 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_number[2U] = self->pending_action_number[2U] + 1U;

            } else
            {
                

            }

        } else
        #line 603 "src/service_libraries/pus_services/pus_service19.fin"
        if (RID_type._variant == Ev_IDType__HighSeverityAnomaly) {
            
            #line 605 "src/service_libraries/pus_services/pus_service19.fin"
            if (self->pending_action_number[3U] < 8U) {
                
                #line 607 "src/service_libraries/pus_services/pus_service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[3U] + self->pending_action_number[3U]) % 8U;

                #line 608 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_queue_4HS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 609 "src/service_libraries/pus_services/pus_service19.fin"
                self->pending_action_number[3U] = self->pending_action_number[3U] + 1U;

            } else
            {
                

            }

        } else
        {
            

        }

    }

    #line 627 "src/service_libraries/pus_services/pus_service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 627 "src/service_libraries/pus_services/pus_service19.fin"
    return;

}
