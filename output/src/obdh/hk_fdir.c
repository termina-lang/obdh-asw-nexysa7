
#include "obdh/hk_fdir.h"

const size_t num_actions_per_second = 2U;

void CHousekeepingFDIRTask__check_pending_actions(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 88 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 90 "src/obdh/hk_fdir.fin"
    size_t pending_actions[4U] = { 0U, 0U, 0U, 0U };

    #line 91 "src/obdh/hk_fdir.fin"
    self->pus_service_19.get_pending_action_number(termina__ev, self->pus_service_19._that, pending_actions);

    #line 93 "src/obdh/hk_fdir.fin"
    size_t n = 4U;

    #line 95 "src/obdh/hk_fdir.fin"
    if (pending_actions[3U] > 0U) {
        
        #line 97 "src/obdh/hk_fdir.fin"
        n = 3U;

    } else
    #line 99 "src/obdh/hk_fdir.fin"
    if (pending_actions[2U] > 0U) {
        
        #line 101 "src/obdh/hk_fdir.fin"
        n = 2U;

    } else
    #line 103 "src/obdh/hk_fdir.fin"
    if (pending_actions[1U] > 0U) {
        
        #line 105 "src/obdh/hk_fdir.fin"
        n = 1U;

    } else
    #line 107 "src/obdh/hk_fdir.fin"
    if (pending_actions[0U] > 0U) {
        
        #line 109 "src/obdh/hk_fdir.fin"
        n = 0U;

    } else
    {
        

    }

    #line 115 "src/obdh/hk_fdir.fin"
    if (n < 4U) {
        
        #line 117 "src/obdh/hk_fdir.fin"
        Option__box tc_handler = { ._variant = Option__None };

        #line 118 "src/obdh/hk_fdir.fin"
        self->tc_handler_pool.alloc(termina__ev, self->tc_handler_pool._that, &tc_handler);

        #line 122 "src/obdh/hk_fdir.fin"
        if (tc_handler._variant == Option__Some) {
            
            #line 122 "src/obdh/hk_fdir.fin"
            const termina__box_t b_tc_handler = tc_handler.Some._0;

            #line 124 "src/obdh/hk_fdir.fin"
            self->pus_service_19.extract_action(termina__ev, self->pus_service_19._that, n, (TCHandler *)b_tc_handler.data);

            #line 125 "src/obdh/hk_fdir.fin"
            termina__out_port__send(termina__ev, self->action_tc_message_queue_output, (const void *)&b_tc_handler);

        } else
        {
            

        }

    }

    #line 134 "src/obdh/hk_fdir.fin"
    return;

}

void CHousekeepingFDIRTask__do_fdir(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 51 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 53 "src/obdh/hk_fdir.fin"
    _Bool is_monitor_enabled = false;

    #line 55 "src/obdh/hk_fdir.fin"
    for (size_t i = 0U; i < 16U; i = i + 1U) {
        
        #line 57 "src/obdh/hk_fdir.fin"
        self->pus_service_12.is_PMON_enabled(termina__ev, self->pus_service_12._that, i, &is_monitor_enabled);

        #line 59 "src/obdh/hk_fdir.fin"
        if (is_monitor_enabled) {
            
            #line 61 "src/obdh/hk_fdir.fin"
            uint16_t evID = 0U;

            #line 62 "src/obdh/hk_fdir.fin"
            FaultInfo fault_info = { ._variant = FaultInfo__Empty };

            #line 63 "src/obdh/hk_fdir.fin"
            _Bool event_triggered = false;

            #line 65 "src/obdh/hk_fdir.fin"
            self->pus_service_12.do_monitoring(termina__ev, self->pus_service_12._that, (uint16_t)i, &evID, &fault_info, &event_triggered);

            #line 67 "src/obdh/hk_fdir.fin"
            if (event_triggered) {
                
                #line 69 "src/obdh/hk_fdir.fin"
                _Bool is_Ev_ID_enabled = false;

                #line 70 "src/obdh/hk_fdir.fin"
                self->pus_service_5.is_Ev_ID_enabled_ext(termina__ev, self->pus_service_5._that, evID, &is_Ev_ID_enabled);

                #line 72 "src/obdh/hk_fdir.fin"
                if (is_Ev_ID_enabled) {
                    
                    #line 74 "src/obdh/hk_fdir.fin"
                    self->pus_service_5.send_tm_5_x(termina__ev, self->pus_service_5._that, evID, &fault_info);

                    #line 75 "src/obdh/hk_fdir.fin"
                    self->pus_service_19.manage_event_action(termina__ev, self->pus_service_19._that, evID);

                }

            }

        }

    }

    #line 84 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask__check_pending_actions(termina__ev, self);
    #line 84 "src/obdh/hk_fdir.fin"
    return;

}

void CHousekeepingFDIRTask__do_hk_fdir(const termina__event_t * const termina__ev, void * const termina__this, const TimeVal termina__ignored__current_time) {
    
    (void)termina__ignored__current_time;

    #line 144 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 146 "src/obdh/hk_fdir.fin"
    self->pus_service_3.update_params(termina__ev, self->pus_service_3._that);

    #line 147 "src/obdh/hk_fdir.fin"
    self->pus_service_4.update_all_stats(termina__ev, self->pus_service_4._that);

    #line 148 "src/obdh/hk_fdir.fin"
    self->pus_service_3.do_hk(termina__ev, self->pus_service_3._that);

    #line 150 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask__do_fdir(termina__ev, self);
    #line 150 "src/obdh/hk_fdir.fin"
    return;

}

void CHousekeepingFDIRTask__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 160 "src/obdh/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 162 "src/obdh/hk_fdir.fin"
    uint8_t tc_type = (*(TCHandler *)tc_handler.data).df_header.type;

    #line 164 "src/obdh/hk_fdir.fin"
    if (tc_type == 3U) {
        
        #line 166 "src/obdh/hk_fdir.fin"
        self->pus_service_3.exec_tc(termina__ev, self->pus_service_3._that, (TCHandler *)tc_handler.data);

    } else
    #line 168 "src/obdh/hk_fdir.fin"
    if (tc_type == 5U) {
        
        #line 170 "src/obdh/hk_fdir.fin"
        self->pus_service_5.exec_tc(termina__ev, self->pus_service_5._that, (TCHandler *)tc_handler.data);

    } else
    #line 172 "src/obdh/hk_fdir.fin"
    if (tc_type == 12U) {
        
        #line 174 "src/obdh/hk_fdir.fin"
        self->pus_service_12.exec_tc(termina__ev, self->pus_service_12._that, (TCHandler *)tc_handler.data);

    } else
    #line 176 "src/obdh/hk_fdir.fin"
    if (tc_type == 19U) {
        
        #line 178 "src/obdh/hk_fdir.fin"
        self->pus_service_19.exec_tc(termina__ev, self->pus_service_19._that, (TCHandler *)tc_handler.data);

    } else
    #line 181 "src/obdh/hk_fdir.fin"
    if (tc_type == 4U) {
        
        #line 183 "src/obdh/hk_fdir.fin"
        self->pus_service_4.exec_tc(termina__ev, self->pus_service_4._that, (TCHandler *)tc_handler.data);

    } else
    {
        
        #line 187 "src/obdh/hk_fdir.fin"
        self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, (*(TCHandler *)tc_handler.data).packet_header.packet_id, (*(TCHandler *)tc_handler.data).packet_header.packet_seq_ctrl);

    }

    #line 193 "src/obdh/hk_fdir.fin"
    self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    #line 195 "src/obdh/hk_fdir.fin"
    return;

}

void termina__task_entry__CHousekeepingFDIRTask(void * const arg) {
    
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)arg;

    termina__error_code_t status = termina__error__none;

    termina__event_t event;

    TimeVal do_hk_fdir__msg_data;
    termina__box_t exec_tc__msg_data;

    for (;;) {
        
        termina__msg_queue__recv(self->_task_msg_queue_id, &event, &status);

        if (status != termina__error__none) {
            termina__except__msg_queue_recv_error(self->_task_msg_queue_id, status);
        }

        switch (event.port_id) {
            
            case CHousekeepingFDIRTask__hk_fdir_timer_ev:

                termina__msg_queue__recv(self->hk_fdir_timer_ev, (void *)&do_hk_fdir__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->hk_fdir_timer_ev, status);
                }

                CHousekeepingFDIRTask__do_hk_fdir(&event, self, do_hk_fdir__msg_data);

                break;

            case CHousekeepingFDIRTask__hkfdir_message_queue_input:

                termina__msg_queue__recv(self->hkfdir_message_queue_input, (void *)&exec_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->hkfdir_message_queue_input, status);
                }

                CHousekeepingFDIRTask__exec_tc(&event, self, exec_tc__msg_data);

                break;

            default:

                termina__except__runtime_failure(termina__runtime_operation__task_dispatch, termina__error__invalid_id);

                break;

        }

    }

    return;

}
