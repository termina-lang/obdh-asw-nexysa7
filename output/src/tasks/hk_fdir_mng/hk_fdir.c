
#include "tasks/hk_fdir_mng/hk_fdir.h"

const size_t num_actions_per_second = 2U;

Status__i32 CHousekeepingFDIRTask__check_pending_actions(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 96 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 98 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    Status__i32 result = { ._variant = Status__Success };

    #line 100 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    size_t pending_actions[4U] = { 0U, 0U, 0U, 0U };

    #line 101 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    self->pus_service_19.get_pending_action_number(termina__ev, self->pus_service_19._that, pending_actions);

    #line 103 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    size_t n = 4U;

    #line 105 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (pending_actions[3U] > 0U) {
        
        #line 107 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        n = 3U;

    } else
    #line 109 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (pending_actions[2U] > 0U) {
        
        #line 111 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        n = 2U;

    } else
    #line 113 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (pending_actions[1U] > 0U) {
        
        #line 115 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        n = 1U;

    } else
    #line 117 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (pending_actions[0U] > 0U) {
        
        #line 119 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        n = 0U;

    } else
    {
        

    }

    #line 125 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (n < 4U) {
        
        #line 127 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        Option__box tc_handler = { ._variant = Option__None };

        #line 128 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->tc_handler_pool.alloc(termina__ev, self->tc_handler_pool._that, &tc_handler);

        #line 132 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        if (tc_handler._variant == Option__Some) {
            
            #line 132 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            const termina__box_t b_tc_handler = tc_handler.Some._0;

            #line 134 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            self->pus_service_19.extract_action(termina__ev, self->pus_service_19._that, n, (TCHandler *)b_tc_handler.data);

            #line 135 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            termina__out_port__send(termina__ev, self->action_tc_message_queue_output, (const void *)&b_tc_handler);

        } else
        {
            
            #line 139 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            result._variant = Status__Failure;
            #line 139 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            result.Failure._0 = 1L;

        }

    }

    #line 145 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    return result;

}

Status__i32 CHousekeepingFDIRTask__do_fdir(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 53 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 55 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    Status__i32 result = { ._variant = Status__Success };

    #line 57 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    _Bool is_monitor_enabled = false;

    #line 59 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    for (size_t i = 0U; i < 16U; i = i + 1U) {
        
        #line 61 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_12.is_PMON_enabled(termina__ev, self->pus_service_12._that, i, &is_monitor_enabled);

        #line 63 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        if (is_monitor_enabled) {
            
            #line 65 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            uint16_t evID = 0U;

            #line 66 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            FaultInfo fault_info = { ._variant = FaultInfo__Empty };

            #line 67 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            _Bool event_triggered = false;

            #line 69 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            self->pus_service_12.do_monitoring(termina__ev, self->pus_service_12._that, (uint16_t)i, &evID, &fault_info, &event_triggered, &result);

            #line 71 "src/tasks/hk_fdir_mng/hk_fdir.fin"
            if (event_triggered) {
                
                #line 73 "src/tasks/hk_fdir_mng/hk_fdir.fin"
                _Bool is_Ev_ID_enabled = false;

                #line 74 "src/tasks/hk_fdir_mng/hk_fdir.fin"
                self->pus_service_5.is_Ev_ID_enabled_ext(termina__ev, self->pus_service_5._that, evID, &is_Ev_ID_enabled);

                #line 76 "src/tasks/hk_fdir_mng/hk_fdir.fin"
                if (is_Ev_ID_enabled) {
                    
                    #line 78 "src/tasks/hk_fdir_mng/hk_fdir.fin"
                    self->pus_service_5.send_tm_5_x(termina__ev, self->pus_service_5._that, evID, &fault_info, &result);

                    #line 79 "src/tasks/hk_fdir_mng/hk_fdir.fin"
                    self->pus_service_19.manage_event_action(termina__ev, self->pus_service_19._that, evID);

                }

            }

        }

    }

    #line 88 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (result._variant == Status__Success) {
        
        #line 89 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        return CHousekeepingFDIRTask__check_pending_actions(termina__ev, self);

    } else
    {
        
        #line 91 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        return result;

    }

}

Status__i32 CHousekeepingFDIRTask__do_hk_fdir(const termina__event_t * const termina__ev, void * const termina__this, const TimeVal termina__ignored__current_time) {
    
    (void)termina__ignored__current_time;

    #line 156 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 158 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    Status__i32 result = { ._variant = Status__Success };

    #line 160 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    self->pus_service_3.update_params(termina__ev, self->pus_service_3._that);

    #line 161 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    self->pus_service_4.update_all_stats(termina__ev, self->pus_service_4._that);

    #line 162 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    self->pus_service_3.do_hk(termina__ev, self->pus_service_3._that, &result);

    #line 164 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (result._variant == Status__Success) {
        
        #line 165 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        return CHousekeepingFDIRTask__do_fdir(termina__ev, self);

    } else
    {
        
        #line 167 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        return result;

    }

}

Status__i32 CHousekeepingFDIRTask__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 179 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)termina__this;

    #line 181 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 183 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    uint8_t tc_type = (*(TCHandler *)tc_handler.data).df_header.type;

    #line 185 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (tc_type == 3U) {
        
        #line 187 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_3.exec_tc(termina__ev, self->pus_service_3._that, (TCHandler *)tc_handler.data, &status);

    } else
    #line 189 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (tc_type == 5U) {
        
        #line 191 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_5.exec_tc(termina__ev, self->pus_service_5._that, (TCHandler *)tc_handler.data, &status);

    } else
    #line 193 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (tc_type == 12U) {
        
        #line 195 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_12.exec_tc(termina__ev, self->pus_service_12._that, (TCHandler *)tc_handler.data, &status);

    } else
    #line 197 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (tc_type == 19U) {
        
        #line 199 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_19.exec_tc(termina__ev, self->pus_service_19._that, (TCHandler *)tc_handler.data, &status);

    } else
    #line 202 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    if (tc_type == 4U) {
        
        #line 204 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_4.exec_tc(termina__ev, self->pus_service_4._that, (TCHandler *)tc_handler.data, &status);

    } else
    {
        
        #line 208 "src/tasks/hk_fdir_mng/hk_fdir.fin"
        self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, (*(TCHandler *)tc_handler.data).packet_header.packet_id, (*(TCHandler *)tc_handler.data).packet_header.packet_seq_ctrl, &status);

    }

    #line 215 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    #line 217 "src/tasks/hk_fdir_mng/hk_fdir.fin"
    return status;

}

void termina__task_entry__CHousekeepingFDIRTask(void * const arg) {
    
    CHousekeepingFDIRTask * self = (CHousekeepingFDIRTask *)arg;

    termina__error_code_t status = termina__error__none;

    termina__event_t event;

    Status__i32 result;

    TimeVal do_hk_fdir__msg_data;
    termina__box_t exec_tc__msg_data;

    for (;;) {
        
        termina__msg_queue__recv(self->_task_msg_queue_id, &event, &status);

        if (status != termina__error__none) {
            break;
        }

        switch (event.port_id) {
            
            case CHousekeepingFDIRTask__hk_fdir_timer_ev:

                termina__msg_queue__recv(self->hk_fdir_timer_ev, (void *)&do_hk_fdir__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->hk_fdir_timer_ev, status);
                }

                result = CHousekeepingFDIRTask__do_hk_fdir(&event, self, do_hk_fdir__msg_data);

                if (result._variant != Status__Success) {
                    
                    ExceptSource source;
                    source._variant = ExceptSource__Task;
                    source.Task._0 = self->_task_id;

                    termina__except__action_failure(source, CHousekeepingFDIRTask__hk_fdir_timer_ev, result.Failure._0);

                }

                break;

            case CHousekeepingFDIRTask__hkfdir_message_queue_input:

                termina__msg_queue__recv(self->hkfdir_message_queue_input, (void *)&exec_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->hkfdir_message_queue_input, status);
                }

                result = CHousekeepingFDIRTask__exec_tc(&event, self, exec_tc__msg_data);

                if (result._variant != Status__Success) {
                    
                    ExceptSource source;
                    source._variant = ExceptSource__Task;
                    source.Task._0 = self->_task_id;

                    termina__except__action_failure(source, CHousekeepingFDIRTask__hkfdir_message_queue_input, result.Failure._0);

                }

                break;

            default:

                termina__exec__reboot();

                break;

        }

    }

    return;

}
