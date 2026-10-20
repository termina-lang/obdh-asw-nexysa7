
#include "obdh/obdh_manager/obdh_manager.h"

void COBDHManagerTask__process_action_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 118 "src/obdh/obdh_manager/obdh_manager.fin"
    COBDHManagerTask * self = (COBDHManagerTask *)termina__this;

    #line 120 "src/obdh/obdh_manager/obdh_manager.fin"
    TCExecutionCtrl execution_status = handle_tc(&(*(TCHandler *)tc_handler.data).tc_descriptor);

    #line 124 "src/obdh/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlHK_FDIRTC) {
        
        #line 126 "src/obdh/obdh_manager/obdh_manager.fin"
        termina__out_port__send(termina__ev, self->hkfdir_message_queue_output, (const void *)&tc_handler);

    } else
    #line 128 "src/obdh/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlBKGTC) {
        
        #line 130 "src/obdh/obdh_manager/obdh_manager.fin"
        termina__out_port__send(termina__ev, self->bkg_message_queue_output, (const void *)&tc_handler);

    } else
    #line 133 "src/obdh/obdh_manager/obdh_manager.fin"
    if (execution_status._variant == TCExecutionCtrl__ExecCtrlPrioTC) {
        
        #line 135 "src/obdh/obdh_manager/obdh_manager.fin"
        _Bool reboot_requested = false;

        #line 137 "src/obdh/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.PUS_prio_exec_tc(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &reboot_requested);

        #line 138 "src/obdh/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

        #line 140 "src/obdh/obdh_manager/obdh_manager.fin"
        if (reboot_requested) {
            
            termina__exec__reboot();

        }

    } else
    {
        
        #line 146 "src/obdh/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    }

    #line 152 "src/obdh/obdh_manager/obdh_manager.fin"
    return;

}

void COBDHManagerTask__process_tc(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tc_handler) {
    
    #line 51 "src/obdh/obdh_manager/obdh_manager.fin"
    COBDHManagerTask * self = (COBDHManagerTask *)termina__this;

    #line 53 "src/obdh/obdh_manager/obdh_manager.fin"
    tc_handler_build((TCHandler *)tc_handler.data);

    #line 55 "src/obdh/obdh_manager/obdh_manager.fin"
    TCStatus current_tc_status = try_tc_acceptation(&(*(TCHandler *)tc_handler.data).tc_descriptor);

    #line 59 "src/obdh/obdh_manager/obdh_manager.fin"
    if (current_tc_status.acceptation_status._variant == TCAcceptationStatus__Accepted) {
        
        #line 61 "src/obdh/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.mng_tc_acceptation(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data);

        #line 65 "src/obdh/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlHK_FDIRTC) {
            
            #line 67 "src/obdh/obdh_manager/obdh_manager.fin"
            termina__out_port__send(termina__ev, self->hkfdir_message_queue_output, (const void *)&tc_handler);

        } else
        #line 69 "src/obdh/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlBKGTC) {
            
            #line 71 "src/obdh/obdh_manager/obdh_manager.fin"
            termina__out_port__send(termina__ev, self->bkg_message_queue_output, (const void *)&tc_handler);

        } else
        #line 74 "src/obdh/obdh_manager/obdh_manager.fin"
        if (current_tc_status.execution_status._variant == TCExecutionCtrl__ExecCtrlPrioTC) {
            
            #line 76 "src/obdh/obdh_manager/obdh_manager.fin"
            _Bool reboot_requested = false;

            #line 78 "src/obdh/obdh_manager/obdh_manager.fin"
            self->mng_tc_executor.PUS_prio_exec_tc(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &reboot_requested);

            #line 80 "src/obdh/obdh_manager/obdh_manager.fin"
            self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

            #line 82 "src/obdh/obdh_manager/obdh_manager.fin"
            if (reboot_requested) {
                
                termina__exec__reboot();

            }

        } else
        {
            
            #line 89 "src/obdh/obdh_manager/obdh_manager.fin"
            self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

        }

    } else
    {
        
        #line 96 "src/obdh/obdh_manager/obdh_manager.fin"
        self->mng_tc_executor.mng_tc_rejection(termina__ev, self->mng_tc_executor._that, (TCHandler *)tc_handler.data, &current_tc_status);

        #line 97 "src/obdh/obdh_manager/obdh_manager.fin"
        self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler);

    }

    #line 102 "src/obdh/obdh_manager/obdh_manager.fin"
    return;

}

void termina__task_entry__COBDHManagerTask(void * const arg) {
    
    COBDHManagerTask * self = (COBDHManagerTask *)arg;

    termina__error_code_t status = termina__error__none;

    termina__event_t event;

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

                COBDHManagerTask__process_tc(&event, self, process_tc__msg_data);

                break;

            case COBDHManagerTask__action_tc_message_queue_input:

                termina__msg_queue__recv(self->action_tc_message_queue_input, (void *)&process_action_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->action_tc_message_queue_input, status);
                }

                COBDHManagerTask__process_action_tc(&event, self, process_action_tc__msg_data);

                break;

            default:

                termina__except__runtime_failure(termina__runtime_operation__task_dispatch, termina__error__invalid_id);

                break;

        }

    }

    return;

}
