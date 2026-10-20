
#include "obdh/pus/services/service19.h"

static void CPUSService19__delete_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index);

static void CPUSService19__disable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index);

static void CPUSService19__enable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index);

static FoundID CPUSService19__get_free_event_action_index(const termina__event_t * const termina__ev, const CPUSService19 * const self);

static FoundID CPUSService19__is_ev_action_defined(const termina__event_t * const termina__ev, const CPUSService19 * const self, const uint16_t evID);

static Status__PUSService19Error CPUSService19__exec19_1TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request);

static Status__PUSService19Error CPUSService19__exec19_2TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request);

static Status__PUSService19Error CPUSService19__exec19_4TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request);

static Status__PUSService19Error CPUSService19__exec19_5TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request);

static void CPUSService19__delete_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index) {
    
    (void)termina__ev;

    #line 47 "src/obdh/pus/services/service19.fin"
    self->event_action_config[termina__check__array_index(16U, ev_action_index)].event_ID = 0U;

    #line 48 "src/obdh/pus/services/service19.fin"
    self->event_action_config[termina__check__array_index(16U, ev_action_index)].enabled = false;

    #line 50 "src/obdh/pus/services/service19.fin"
    return;

}

static void CPUSService19__disable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index) {
    
    (void)termina__ev;

    #line 33 "src/obdh/pus/services/service19.fin"
    self->event_action_config[termina__check__array_index(16U, ev_action_index)].enabled = false;

    #line 35 "src/obdh/pus/services/service19.fin"
    return;

}

static void CPUSService19__enable_event_action(const termina__event_t * const termina__ev, CPUSService19 * const self, const size_t ev_action_index) {
    
    (void)termina__ev;

    #line 40 "src/obdh/pus/services/service19.fin"
    self->event_action_config[termina__check__array_index(16U, ev_action_index)].enabled = true;

    #line 42 "src/obdh/pus/services/service19.fin"
    return;

}

static FoundID CPUSService19__get_free_event_action_index(const termina__event_t * const termina__ev, const CPUSService19 * const self) {
    
    (void)termina__ev;

    #line 55 "src/obdh/pus/services/service19.fin"
    FoundID found_and_id = { .enabled = false, .ev_action_index = 0U, .found = false };

    #line 57 "src/obdh/pus/services/service19.fin"
    for (size_t i = 0U; i < 16U && found_and_id.found == false; i = i + 1U) {
        
        #line 59 "src/obdh/pus/services/service19.fin"
        if (self->event_action_config[i].event_ID == 0U) {
            
            #line 61 "src/obdh/pus/services/service19.fin"
            found_and_id.ev_action_index = i;

            #line 62 "src/obdh/pus/services/service19.fin"
            found_and_id.found = true;

        }

    }

    #line 65 "src/obdh/pus/services/service19.fin"
    return found_and_id;

}

static FoundID CPUSService19__is_ev_action_defined(const termina__event_t * const termina__ev, const CPUSService19 * const self, const uint16_t evID) {
    
    (void)termina__ev;

    #line 70 "src/obdh/pus/services/service19.fin"
    FoundID found_and_id = { .enabled = false, .ev_action_index = 0U, .found = false };

    #line 72 "src/obdh/pus/services/service19.fin"
    for (size_t i = 0U; i < 16U && found_and_id.found == false; i = i + 1U) {
        
        #line 74 "src/obdh/pus/services/service19.fin"
        if (self->event_action_config[i].event_ID == evID) {
            
            #line 76 "src/obdh/pus/services/service19.fin"
            found_and_id.ev_action_index = i;

            #line 77 "src/obdh/pus/services/service19.fin"
            found_and_id.enabled = self->event_action_config[i].enabled;

            #line 78 "src/obdh/pus/services/service19.fin"
            found_and_id.found = true;

        }

    }

    #line 81 "src/obdh/pus/services/service19.fin"
    return found_and_id;

}

static Status__PUSService19Error CPUSService19__exec19_1TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request) {
    
    #line 89 "src/obdh/pus/services/service19.fin"
    Status__PUSService19Error status = { ._variant = Status__Success };

    #line 91 "src/obdh/pus/services/service19.fin"
    if (tc_request->tc_data.N != 1U) {
        
        #line 93 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 93 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__NumOfInstrNotValid;
        #line 93 "src/obdh/pus/services/service19.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data.N;

    } else
    #line 95 "src/obdh/pus/services/service19.fin"
    if (is_Ev_ID_valid(tc_request->tc_data.EvID) == false) {
        
        #line 97 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 97 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__EvIDNotValid;
        #line 97 "src/obdh/pus/services/service19.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->tc_data.EvID;

    } else
    {
        
        #line 101 "src/obdh/pus/services/service19.fin"
        TC19_1_Error error;

        #line 103 "src/obdh/pus/services/service19.fin"
        tc_request->ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, tc_request->tc_data.EvID);

        #line 105 "src/obdh/pus/services/service19.fin"
        if (tc_request->ev_action_ID.found) {
            
            #line 107 "src/obdh/pus/services/service19.fin"
            if (tc_request->ev_action_ID.enabled) {
                
                #line 109 "src/obdh/pus/services/service19.fin"
                error._variant = TC19_1_Error__EvIDEnabled;

            } else
            {
                
                #line 113 "src/obdh/pus/services/service19.fin"
                error._variant = TC19_1_Error__NoError;

            }

        } else
        {
            
            #line 118 "src/obdh/pus/services/service19.fin"
            tc_request->ev_action_ID = CPUSService19__get_free_event_action_index(termina__ev, self);

            #line 120 "src/obdh/pus/services/service19.fin"
            if (tc_request->ev_action_ID.found) {
                
                #line 121 "src/obdh/pus/services/service19.fin"
                error._variant = TC19_1_Error__NoError;

            } else
            {
                
                #line 124 "src/obdh/pus/services/service19.fin"
                error._variant = TC19_1_Error__MaxEventActionDefinitions;

            }

        }

        #line 130 "src/obdh/pus/services/service19.fin"
        if (error._variant == TC19_1_Error__NoError) {
            
            #line 132 "src/obdh/pus/services/service19.fin"
            TCHandler action_tc_handler = { .app_data_index = 0U, .df_header = { .flag_ver_ack = 0U, .sourceID = 0U, .subtype = 0U, .type = 0U }, .packet_error_ctrl = 0U, .packet_header = { .packet_id = 0U, .packet_length = 0U, .packet_seq_ctrl = 0U }, .tc_descriptor = tc_request->action_tc_packet };

            #line 149 "src/obdh/pus/services/service19.fin"
            tc_handler_build(&action_tc_handler);

            #line 151 "src/obdh/pus/services/service19.fin"
            TCStatus tc_status = try_tc_acceptation(&tc_request->action_tc_packet);

            #line 153 "src/obdh/pus/services/service19.fin"
            if (tc_status.acceptation_status._variant == TCAcceptationStatus__Accepted) {
                
                #line 155 "src/obdh/pus/services/service19.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

                #line 160 "src/obdh/pus/services/service19.fin"
                self->event_action_config[termina__check__array_index(16U, tc_request->ev_action_ID.ev_action_index)].event_ID = tc_request->tc_data.EvID;

                #line 161 "src/obdh/pus/services/service19.fin"
                self->event_action_config[termina__check__array_index(16U, tc_request->ev_action_ID.ev_action_index)].enabled = false;

                #line 162 "src/obdh/pus/services/service19.fin"
                self->event_action_packets[termina__check__array_index(16U, tc_request->ev_action_ID.ev_action_index)] = action_tc_handler;

                #line 164 "src/obdh/pus/services/service19.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

            } else
            {
                
                #line 171 "src/obdh/pus/services/service19.fin"
                status._variant = Status__Failure;
                #line 171 "src/obdh/pus/services/service19.fin"
                status.Failure._0._variant = PUSService19Error__EvActionRejected;
                #line 171 "src/obdh/pus/services/service19.fin"
                status.Failure._0.EvActionRejected._0 = tc_request->tc_data.EvID;

            }

        } else
        #line 176 "src/obdh/pus/services/service19.fin"
        if (error._variant == TC19_1_Error__EvIDEnabled) {
            
            #line 178 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 178 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__EvActionEnabled;
            #line 178 "src/obdh/pus/services/service19.fin"
            status.Failure._0.EvActionEnabled._0 = tc_request->tc_data.EvID;

        } else
        {
            
            #line 183 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 183 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__MaxEvActionsDefined;
            #line 183 "src/obdh/pus/services/service19.fin"
            status.Failure._0.MaxEvActionsDefined._0 = tc_request->tc_data.EvID;

        }

    }

    #line 190 "src/obdh/pus/services/service19.fin"
    return status;

}

static Status__PUSService19Error CPUSService19__exec19_2TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request) {
    
    #line 196 "src/obdh/pus/services/service19.fin"
    Status__PUSService19Error status;

    #line 198 "src/obdh/pus/services/service19.fin"
    if (tc_request->tc_data.N != 1U) {
        
        #line 200 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 200 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__NumOfInstrNotValid;
        #line 200 "src/obdh/pus/services/service19.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data.N;

    } else
    #line 202 "src/obdh/pus/services/service19.fin"
    if (is_Ev_ID_valid(tc_request->tc_data.EvID) == false) {
        
        #line 204 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 204 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__EvIDNotValid;
        #line 204 "src/obdh/pus/services/service19.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->tc_data.EvID;

    } else
    {
        
        #line 208 "src/obdh/pus/services/service19.fin"
        tc_request->ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, tc_request->tc_data.EvID);

        #line 211 "src/obdh/pus/services/service19.fin"
        if (tc_request->ev_action_ID.found) {
            
            #line 213 "src/obdh/pus/services/service19.fin"
            if (tc_request->ev_action_ID.enabled) {
                
                #line 215 "src/obdh/pus/services/service19.fin"
                status._variant = Status__Failure;
                #line 215 "src/obdh/pus/services/service19.fin"
                status.Failure._0._variant = PUSService19Error__EvActionEnabled;
                #line 215 "src/obdh/pus/services/service19.fin"
                status.Failure._0.EvActionEnabled._0 = tc_request->tc_data.EvID;

            } else
            {
                
                #line 219 "src/obdh/pus/services/service19.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

                #line 224 "src/obdh/pus/services/service19.fin"
                CPUSService19__delete_event_action(termina__ev, self, tc_request->ev_action_ID.ev_action_index);

                #line 226 "src/obdh/pus/services/service19.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

                #line 231 "src/obdh/pus/services/service19.fin"
                status._variant = Status__Success;

            }

        } else
        {
            
            #line 237 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 237 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__EvActionUndefined;
            #line 237 "src/obdh/pus/services/service19.fin"
            status.Failure._0.EvActionUndefined._0 = tc_request->tc_data.EvID;

        }

    }

    #line 243 "src/obdh/pus/services/service19.fin"
    return status;

}

static Status__PUSService19Error CPUSService19__exec19_4TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request) {
    
    #line 249 "src/obdh/pus/services/service19.fin"
    Status__PUSService19Error status;

    #line 251 "src/obdh/pus/services/service19.fin"
    if (tc_request->tc_data.N != 1U) {
        
        #line 253 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 253 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__NumOfInstrNotValid;
        #line 253 "src/obdh/pus/services/service19.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data.N;

    } else
    #line 255 "src/obdh/pus/services/service19.fin"
    if (is_Ev_ID_valid(tc_request->tc_data.EvID) == false) {
        
        #line 257 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 257 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__EvIDNotValid;
        #line 257 "src/obdh/pus/services/service19.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->tc_data.EvID;

    } else
    {
        
        #line 261 "src/obdh/pus/services/service19.fin"
        tc_request->ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, tc_request->tc_data.EvID);

        #line 263 "src/obdh/pus/services/service19.fin"
        if (tc_request->ev_action_ID.found) {
            
            #line 265 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

            #line 270 "src/obdh/pus/services/service19.fin"
            CPUSService19__enable_event_action(termina__ev, self, tc_request->ev_action_ID.ev_action_index);

            #line 272 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

            #line 277 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Success;

        } else
        {
            
            #line 281 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 281 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__EvActionUndefined;
            #line 281 "src/obdh/pus/services/service19.fin"
            status.Failure._0.EvActionUndefined._0 = tc_request->tc_data.EvID;

        }

    }

    #line 286 "src/obdh/pus/services/service19.fin"
    return status;

}

static Status__PUSService19Error CPUSService19__exec19_5TC(const termina__event_t * const termina__ev, CPUSService19 * const self, PS19TCRequest * const tc_request) {
    
    #line 292 "src/obdh/pus/services/service19.fin"
    Status__PUSService19Error status;

    #line 295 "src/obdh/pus/services/service19.fin"
    if (tc_request->tc_data.N != 1U) {
        
        #line 297 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 297 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__NumOfInstrNotValid;
        #line 297 "src/obdh/pus/services/service19.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data.N;

    } else
    #line 300 "src/obdh/pus/services/service19.fin"
    if (is_Ev_ID_valid(tc_request->tc_data.EvID) == false) {
        
        #line 302 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 302 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__EvIDNotValid;
        #line 302 "src/obdh/pus/services/service19.fin"
        status.Failure._0.EvIDNotValid._0 = tc_request->tc_data.EvID;

    } else
    {
        
        #line 306 "src/obdh/pus/services/service19.fin"
        tc_request->ev_action_ID = CPUSService19__is_ev_action_defined(termina__ev, self, tc_request->tc_data.EvID);

        #line 309 "src/obdh/pus/services/service19.fin"
        if (tc_request->ev_action_ID.found) {
            
            #line 311 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

            #line 316 "src/obdh/pus/services/service19.fin"
            CPUSService19__disable_event_action(termina__ev, self, tc_request->ev_action_ID.ev_action_index);

            #line 318 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->tc_data.packet_id, tc_request->tc_data.packet_seq_ctrl, tc_request->tc_data.flags_ack);

            #line 323 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Success;

        } else
        {
            
            #line 327 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 327 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__EvActionUndefined;
            #line 327 "src/obdh/pus/services/service19.fin"
            status.Failure._0.EvActionUndefined._0 = tc_request->tc_data.EvID;

        }

    }

    #line 333 "src/obdh/pus/services/service19.fin"
    return status;

}

void CPUSService19__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 336 "src/obdh/pus/services/service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 336 "src/obdh/pus/services/service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 338 "src/obdh/pus/services/service19.fin"
    Status__PUSService19Error status = { ._variant = Status__Success };

    #line 339 "src/obdh/pus/services/service19.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 340 "src/obdh/pus/services/service19.fin"
    PS19TCRequest tc_request = { .action_tc_packet = { .tc_bytes = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, .tc_num_bytes = 0U }, .ev_action_ID = { .enabled = false, .ev_action_index = 0U, .found = false }, .tc_data = { .EvID = 0U, .N = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U } };

    #line 342 "src/obdh/pus/services/service19.fin"
    tc_request.tc_data.packet_id = tc_handler->packet_header.packet_id;

    #line 343 "src/obdh/pus/services/service19.fin"
    tc_request.tc_data.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 344 "src/obdh/pus/services/service19.fin"
    tc_request.tc_data.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 345 "src/obdh/pus/services/service19.fin"
    tc_request.tc_data.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 347 "src/obdh/pus/services/service19.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_data.N);

    #line 349 "src/obdh/pus/services/service19.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 350 "src/obdh/pus/services/service19.fin"
        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.tc_data.EvID);

    }

    #line 353 "src/obdh/pus/services/service19.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 354 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 354 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__AppDataOutOfRange;
        #line 354 "src/obdh/pus/services/service19.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_data.tc_num_bytes;

    }

    #line 357 "src/obdh/pus/services/service19.fin"
    if (status._variant == Status__Success && subtype == 1U && tc_request.tc_data.tc_num_bytes < (size_t)((size_t)(tc_handler->app_data_index + 2U) + 13U)) {
        
        #line 359 "src/obdh/pus/services/service19.fin"
        status._variant = Status__Failure;
        #line 359 "src/obdh/pus/services/service19.fin"
        status.Failure._0._variant = PUSService19Error__AppDataOutOfRange;
        #line 359 "src/obdh/pus/services/service19.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_data.tc_num_bytes;

    }

    #line 362 "src/obdh/pus/services/service19.fin"
    if (status._variant == Status__Success && subtype == 1U) {
        
        #line 364 "src/obdh/pus/services/service19.fin"
        tc_request.action_tc_packet.tc_num_bytes = (size_t)(tc_handler->tc_descriptor.tc_num_bytes - 2U) - tc_handler->app_data_index;

        #line 366 "src/obdh/pus/services/service19.fin"
        for (size_t j = 0U; j < 242U && j < tc_request.action_tc_packet.tc_num_bytes; j = j + 1U) {
            
            #line 368 "src/obdh/pus/services/service19.fin"
            tc_request.action_tc_packet.tc_bytes[j] = tc_handler->tc_descriptor.tc_bytes[termina__check__array_index(256U, j + tc_handler->app_data_index)];

        }

    }

    #line 374 "src/obdh/pus/services/service19.fin"
    if (status._variant == Status__Success) {
        
        #line 376 "src/obdh/pus/services/service19.fin"
        if (subtype == 1U) {
            
            #line 378 "src/obdh/pus/services/service19.fin"
            status = CPUSService19__exec19_1TC(termina__ev, self, &tc_request);

        } else
        #line 380 "src/obdh/pus/services/service19.fin"
        if (subtype == 2U) {
            
            #line 382 "src/obdh/pus/services/service19.fin"
            status = CPUSService19__exec19_2TC(termina__ev, self, &tc_request);

        } else
        #line 384 "src/obdh/pus/services/service19.fin"
        if (subtype == 4U) {
            
            #line 386 "src/obdh/pus/services/service19.fin"
            status = CPUSService19__exec19_4TC(termina__ev, self, &tc_request);

        } else
        #line 388 "src/obdh/pus/services/service19.fin"
        if (subtype == 5U) {
            
            #line 390 "src/obdh/pus/services/service19.fin"
            status = CPUSService19__exec19_5TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 394 "src/obdh/pus/services/service19.fin"
            status._variant = Status__Failure;
            #line 394 "src/obdh/pus/services/service19.fin"
            status.Failure._0._variant = PUSService19Error__ErrorInAcceptance;

        }

    }

    #line 402 "src/obdh/pus/services/service19.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 405 "src/obdh/pus/services/service19.fin"
        const PUSService19Error error = status.Failure._0;

        #line 409 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__ErrorInAcceptance) {
            
            #line 411 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl);

        } else
        #line 416 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__AppDataOutOfRange) {
            
            #line 416 "src/obdh/pus/services/service19.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 418 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 424 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__NumOfInstrNotValid) {
            
            #line 424 "src/obdh/pus/services/service19.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 426 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, N);

        } else
        #line 432 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__EvIDNotValid) {
            
            #line 432 "src/obdh/pus/services/service19.fin"
            const uint16_t EvID = error.EvIDNotValid._0;

            #line 434 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_EvID_not_valid(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, EvID);

        } else
        #line 440 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__EvActionEnabled) {
            
            #line 440 "src/obdh/pus/services/service19.fin"
            const uint16_t EvID = error.EvActionEnabled._0;

            #line 442 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_enabled(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, EvID);

        } else
        #line 448 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__EvActionRejected) {
            
            #line 448 "src/obdh/pus/services/service19.fin"
            const uint16_t EvID = error.EvActionRejected._0;

            #line 450 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_rejected(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, EvID);

        } else
        #line 456 "src/obdh/pus/services/service19.fin"
        if (error._variant == PUSService19Error__EvActionUndefined) {
            
            #line 456 "src/obdh/pus/services/service19.fin"
            const uint16_t EvID = error.EvActionUndefined._0;

            #line 458 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_4_ev_action_undefined(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, EvID);

        } else
        {
            
            #line 464 "src/obdh/pus/services/service19.fin"
            const uint16_t EvID = error.MaxEvActionsDefined._0;

            #line 466 "src/obdh/pus/services/service19.fin"
            self->pus_service_1.send_tm_1_8_max_ev_actions_defined(termina__ev, self->pus_service_1._that, tc_request.tc_data.packet_id, tc_request.tc_data.packet_seq_ctrl, EvID);

        }

    }

    #line 477 "src/obdh/pus/services/service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 477 "src/obdh/pus/services/service19.fin"
    return;

}

void CPUSService19__extract_action(const termina__event_t * const termina__ev, void * const termina__this, const size_t action_index, TCHandler * const action_packet) {
    
    #line 572 "src/obdh/pus/services/service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 572 "src/obdh/pus/services/service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 574 "src/obdh/pus/services/service19.fin"
    if (action_index == 0U) {
        
        #line 576 "src/obdh/pus/services/service19.fin"
        *action_packet = self->pending_action_queue_1I[termina__check__array_index(8U, self->pending_action_head[0U])];

        #line 577 "src/obdh/pus/services/service19.fin"
        self->pending_action_head[0U] = (size_t)(self->pending_action_head[0U] + 1U) % 8U;

        #line 578 "src/obdh/pus/services/service19.fin"
        self->pending_action_number[0U] = self->pending_action_number[0U] - 1U;

    } else
    #line 580 "src/obdh/pus/services/service19.fin"
    if (action_index == 1U) {
        
        #line 582 "src/obdh/pus/services/service19.fin"
        *action_packet = self->pending_action_queue_2LS[termina__check__array_index(8U, self->pending_action_head[1U])];

        #line 583 "src/obdh/pus/services/service19.fin"
        self->pending_action_head[1U] = (size_t)(self->pending_action_head[1U] + 1U) % 8U;

        #line 584 "src/obdh/pus/services/service19.fin"
        self->pending_action_number[1U] = self->pending_action_number[1U] - 1U;

    } else
    #line 586 "src/obdh/pus/services/service19.fin"
    if (action_index == 2U) {
        
        #line 588 "src/obdh/pus/services/service19.fin"
        *action_packet = self->pending_action_queue_3MS[termina__check__array_index(8U, self->pending_action_head[2U])];

        #line 589 "src/obdh/pus/services/service19.fin"
        self->pending_action_head[2U] = (size_t)(self->pending_action_head[2U] + 1U) % 8U;

        #line 590 "src/obdh/pus/services/service19.fin"
        self->pending_action_number[2U] = self->pending_action_number[2U] - 1U;

    } else
    #line 592 "src/obdh/pus/services/service19.fin"
    if (action_index == 3U) {
        
        #line 594 "src/obdh/pus/services/service19.fin"
        *action_packet = self->pending_action_queue_4HS[termina__check__array_index(8U, self->pending_action_head[3U])];

        #line 595 "src/obdh/pus/services/service19.fin"
        self->pending_action_head[3U] = (size_t)(self->pending_action_head[3U] + 1U) % 8U;

        #line 596 "src/obdh/pus/services/service19.fin"
        self->pending_action_number[3U] = self->pending_action_number[3U] - 1U;

    } else
    {
        

    }

    #line 602 "src/obdh/pus/services/service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 602 "src/obdh/pus/services/service19.fin"
    return;

}

void CPUSService19__get_pending_action_number(const termina__event_t * const termina__ev, void * const termina__this, size_t paction_num[4U]) {
    
    #line 561 "src/obdh/pus/services/service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 561 "src/obdh/pus/services/service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 563 "src/obdh/pus/services/service19.fin"
    for (size_t i = 0U; i < 3U; i = i + 1U) {
        
        #line 565 "src/obdh/pus/services/service19.fin"
        paction_num[i] = self->pending_action_number[i];

    }

    #line 569 "src/obdh/pus/services/service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 569 "src/obdh/pus/services/service19.fin"
    return;

}

void CPUSService19__manage_event_action(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t evID) {
    
    #line 481 "src/obdh/pus/services/service19.fin"
    CPUSService19 * self = (CPUSService19 *)termina__this;

    #line 481 "src/obdh/pus/services/service19.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 483 "src/obdh/pus/services/service19.fin"
    FoundID found_and_id = CPUSService19__is_ev_action_defined(termina__ev, self, evID);

    #line 485 "src/obdh/pus/services/service19.fin"
    if (found_and_id.found && found_and_id.enabled) {
        
        #line 488 "src/obdh/pus/services/service19.fin"
        Ev_IDType RID_type = get_Ev_ID_type(evID);

        #line 492 "src/obdh/pus/services/service19.fin"
        if (RID_type._variant == Ev_IDType__Informative) {
            
            #line 494 "src/obdh/pus/services/service19.fin"
            if (self->pending_action_number[0U] < 8U) {
                
                #line 496 "src/obdh/pus/services/service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[0U] + self->pending_action_number[0U]) % 8U;

                #line 497 "src/obdh/pus/services/service19.fin"
                self->pending_action_queue_1I[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 498 "src/obdh/pus/services/service19.fin"
                self->pending_action_number[0U] = self->pending_action_number[0U] + 1U;

            } else
            {
                

            }

        } else
        #line 506 "src/obdh/pus/services/service19.fin"
        if (RID_type._variant == Ev_IDType__LowSeverityAnomaly) {
            
            #line 508 "src/obdh/pus/services/service19.fin"
            if (self->pending_action_number[1U] < 8U) {
                
                #line 510 "src/obdh/pus/services/service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[1U] + self->pending_action_number[1U]) % 8U;

                #line 511 "src/obdh/pus/services/service19.fin"
                self->pending_action_queue_2LS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 512 "src/obdh/pus/services/service19.fin"
                self->pending_action_number[1U] = self->pending_action_number[1U] + 1U;

            } else
            {
                

            }

        } else
        #line 520 "src/obdh/pus/services/service19.fin"
        if (RID_type._variant == Ev_IDType__MediumSeverityAnomaly) {
            
            #line 522 "src/obdh/pus/services/service19.fin"
            if (self->pending_action_number[2U] < 8U) {
                
                #line 524 "src/obdh/pus/services/service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[2U] + self->pending_action_number[2U]) % 8U;

                #line 525 "src/obdh/pus/services/service19.fin"
                self->pending_action_queue_3MS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 526 "src/obdh/pus/services/service19.fin"
                self->pending_action_number[2U] = self->pending_action_number[2U] + 1U;

            } else
            {
                

            }

        } else
        #line 534 "src/obdh/pus/services/service19.fin"
        if (RID_type._variant == Ev_IDType__HighSeverityAnomaly) {
            
            #line 536 "src/obdh/pus/services/service19.fin"
            if (self->pending_action_number[3U] < 8U) {
                
                #line 538 "src/obdh/pus/services/service19.fin"
                size_t tail_index = (size_t)(self->pending_action_head[3U] + self->pending_action_number[3U]) % 8U;

                #line 539 "src/obdh/pus/services/service19.fin"
                self->pending_action_queue_4HS[tail_index] = self->event_action_packets[termina__check__array_index(16U, found_and_id.ev_action_index)];

                #line 540 "src/obdh/pus/services/service19.fin"
                self->pending_action_number[3U] = self->pending_action_number[3U] + 1U;

            } else
            {
                

            }

        } else
        {
            

        }

    }

    #line 558 "src/obdh/pus/services/service19.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 558 "src/obdh/pus/services/service19.fin"
    return;

}
