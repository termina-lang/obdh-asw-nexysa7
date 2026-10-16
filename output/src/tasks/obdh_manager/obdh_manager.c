
#include "tasks/obdh_manager/obdh_manager.h"

Status__i32 COBDHManagerTask__process_action_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 120 "src/tasks/obdh_manager/obdh_manager.fin"
    COBDHManagerTask * self = (COBDHManagerTask *)termina__this;

    #line 122 "src/tasks/obdh_manager/obdh_manager.fin"
    Status__i32 ret = { ._variant = Status__Success };

    #line 124 "src/tasks/obdh_manager/obdh_manager.fin"
    TCExecutionCtrl execution_status = handle_tc(&(*(TCHandler *)tc_handler.data).tc_descriptor);

    #line 128 "src/tasks/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlHK_FDIRTC) {
        
        #line 130 "src/tasks/obdh_manager/obdh_manager.fin"
        termina__out_port__send(termina__ev, self->hkfdir_message_queue_output, (const void *)&tc_handler);

    } else
    #line 132 "src/tasks/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlBKGTC) {
        
        #line 134 "src/tasks/obdh_manager/obdh_manager.fin"
        termina__out_port__send(termina__ev, self->bkg_message_queue_output, (const void *)&tc_handler);

    } else
    #line 137 "src/tasks/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlPrioTC) {
        
        #line 139 "src/tasks/obdh_manager/obdh_manager.fin"
        _Bool reebot_flag = false;

        #line 141 "src/tasks/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.PUS_prio_exec_tc(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &ret, &reebot_flag);

        #line 142 "src/tasks/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

        #line 144 "src/tasks/obdh_manager/obdh_manager.fin"
        if (reebot_flag) {
            
            termina__exec__reboot();

        }

    } else
    {
        
        #line 150 "src/tasks/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    }

    #line 156 "src/tasks/obdh_manager/obdh_manager.fin"
    return ret;

}

Status__i32 COBDHManagerTask__process_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 52 "src/tasks/obdh_manager/obdh_manager.fin"
    COBDHManagerTask * self = (COBDHManagerTask *)termina__this;

    #line 54 "src/tasks/obdh_manager/obdh_manager.fin"
    Status__i32 ret = { ._variant = Status__Success };

    #line 56 "src/tasks/obdh_manager/obdh_manager.fin"
    TCStatus current_tc_status = try_tc_acceptation(&(*(TCHandler *)tc_handler.data).tc_descriptor);

    #line 60 "src/tasks/obdh_manager/obdh_manager.fin"
    if (current_tc_status.acceptation_status._variant == TCAcceptationStatus__Accepted) {
        
        #line 62 "src/tasks/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.mng_tc_acceptation(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &ret);

        #line 66 "src/tasks/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlHK_FDIRTC) {
            
            #line 68 "src/tasks/obdh_manager/obdh_manager.fin"
            termina__out_port__send(termina__ev, self->hkfdir_message_queue_output, (const void *)&tc_handler);

        } else
        #line 70 "src/tasks/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlBKGTC) {
            
            #line 72 "src/tasks/obdh_manager/obdh_manager.fin"
            termina__out_port__send(termina__ev, self->bkg_message_queue_output, (const void *)&tc_handler);

        } else
        #line 75 "src/tasks/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlPrioTC) {
            
            #line 77 "src/tasks/obdh_manager/obdh_manager.fin"
            _Bool reebot_flag = false;

            #line 79 "src/tasks/obdh_manager/obdh_manager.fin"
            self->mng_tc_executor.PUS_prio_exec_tc(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &ret, &reebot_flag);

            #line 81 "src/tasks/obdh_manager/obdh_manager.fin"
            self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

            #line 83 "src/tasks/obdh_manager/obdh_manager.fin"
            if (reebot_flag) {
                
                termina__exec__reboot();

            }

        } else
        {
            
            #line 90 "src/tasks/obdh_manager/obdh_manager.fin"
            self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

        }

    } else
    {
        
        #line 97 "src/tasks/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.mng_tc_rejection(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &current_tc_status, &ret);

        #line 98 "src/tasks/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    }

    #line 103 "src/tasks/obdh_manager/obdh_manager.fin"
    return ret;

}

void termina__task_entry__COBDHManagerTask(void * const arg) {
    
    COBDHManagerTask * self = (COBDHManagerTask *)arg;

    termina__error_code_t status = termina__error__none;

    termina__event_t event;

    Status__i32 result;

    termina__box_t process_tc__msg_data;
    termina__box_t process_action_tc__msg_data;

    for (;;) {
        
        termina__msg_queue__recv(self->_task_msg_queue_id, &event, &status);

        if (status != termina__error__none) {
            termina__except__msg_queue_recv_error(self->_task_msg_queue_id, status);
        }

        switch (event.port_id) {
            
            case COBDHManagerTask__tc_message_queue_input:

                termina__msg_queue__recv(self->tc_message_queue_input, (void *)&process_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->tc_message_queue_input, status);
                }

                result = COBDHManagerTask__process_tc(&event, self, process_tc__msg_data);

                if (result._variant != Status__Success) {
                    
                    ExceptSource source;
                    source._variant = ExceptSource__Task;
                    source.Task._0 = self->_task_id;

                    termina__except__action_failure(source, COBDHManagerTask__tc_message_queue_input, result.Failure._0);

                }

                break;

            case COBDHManagerTask__action_tc_message_queue_input:

                termina__msg_queue__recv(self->action_tc_message_queue_input, (void *)&process_action_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->action_tc_message_queue_input, status);
                }

                result = COBDHManagerTask__process_action_tc(&event, self, process_action_tc__msg_data);

                if (result._variant != Status__Success) {
                    
                    ExceptSource source;
                    source._variant = ExceptSource__Task;
                    source.Task._0 = self->_task_id;

                    termina__except__action_failure(source, COBDHManagerTask__action_tc_message_queue_input, result.Failure._0);

                }

                break;

            default:

                termina__except__runtime_failure(termina__runtime_operation__task_dispatch, termina__error__invalid_id);

                break;

        }

    }

    return;

}
