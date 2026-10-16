
#include "tasks/tc_rx.h"

Status__i32 CTXRxBottomHalfTask__get_tc(const termina__event_t * const termina__ev, void * const termina__this, const size_t size) {
    
    #line 15 "src/tasks/tc_rx.fin"
    CTXRxBottomHalfTask * self = (CTXRxBottomHalfTask *)termina__this;

    #line 17 "src/tasks/tc_rx.fin"
    Status__i32 ret = { ._variant = Status__Success };

    #line 19 "src/tasks/tc_rx.fin"
    Option__box tc_handler = { ._variant = Option__None };

    #line 20 "src/tasks/tc_rx.fin"
    self->tc_handler_pool.alloc(termina__ev, self->tc_handler_pool._that, &tc_handler);

    #line 24 "src/tasks/tc_rx.fin"
    if (tc_handler._variant == Option__Some) {
        
        #line 24 "src/tasks/tc_rx.fin"
        const termina__box_t tc_handler_b = tc_handler.Some._0;

        #line 26 "src/tasks/tc_rx.fin"
        for (size_t i = 0U; i < 256U && (i < size && ret._variant == Status__Success); i = i + 1U) {
            
            #line 28 "src/tasks/tc_rx.fin"
            Option__u8 obyte = { ._variant = Option__None };

            #line 29 "src/tasks/tc_rx.fin"
            self->tc_channel.dequeue(termina__ev, self->tc_channel._that, &obyte);

            #line 33 "src/tasks/tc_rx.fin"
            if (obyte._variant == Option__Some) {
                
                #line 33 "src/tasks/tc_rx.fin"
                const uint8_t byte = obyte.Some._0;

                #line 34 "src/tasks/tc_rx.fin"
                (*(TCHandler *)tc_handler_b.data).tc_descriptor.tc_bytes[i] = byte;

            } else
            {
                
                #line 37 "src/tasks/tc_rx.fin"
                ret._variant = Status__Failure;
                #line 37 "src/tasks/tc_rx.fin"
                ret.Failure._0 = 13L;

            }

        }

        #line 44 "src/tasks/tc_rx.fin"
        if (ret._variant == Status__Success) {
            
            #line 46 "src/tasks/tc_rx.fin"
            (*(TCHandler *)tc_handler_b.data).tc_descriptor.tc_num_bytes = size;

            #line 48 "src/tasks/tc_rx.fin"
            tc_handler_build((TCHandler *)tc_handler_b.data);

            #line 50 "src/tasks/tc_rx.fin"
            termina__out_port__send(termina__ev, self->tc_message_queue_output, (const void *)&tc_handler_b);

        } else
        {
            
            #line 54 "src/tasks/tc_rx.fin"
            self->tc_handler_pool.free(termina__ev, self->tc_handler_pool._that, tc_handler_b);

        }

    } else
    {
        
        #line 61 "src/tasks/tc_rx.fin"
        ret._variant = Status__Failure;
        #line 61 "src/tasks/tc_rx.fin"
        ret.Failure._0 = 1L;

    }

    #line 66 "src/tasks/tc_rx.fin"
    return ret;

}

void termina__task_entry__CTXRxBottomHalfTask(void * const arg) {
    
    CTXRxBottomHalfTask * self = (CTXRxBottomHalfTask *)arg;

    termina__error_code_t status = termina__error__none;

    termina__event_t event;

    Status__i32 result;

    size_t get_tc__msg_data;

    for (;;) {
        
        termina__msg_queue__recv(self->_task_msg_queue_id, &event, &status);

        if (status != termina__error__none) {
            termina__except__msg_queue_recv_error(self->_task_msg_queue_id, status);
        }

        switch (event.port_id) {
            
            case CTXRxBottomHalfTask__frame_ready_input:

                termina__msg_queue__recv(self->frame_ready_input, (void *)&get_tc__msg_data, &status);

                if (status != termina__error__none) {
                    termina__except__msg_queue_recv_error(self->frame_ready_input, status);
                }

                result = CTXRxBottomHalfTask__get_tc(&event, self, get_tc__msg_data);

                if (result._variant != Status__Success) {
                    
                    ExceptSource source;
                    source._variant = ExceptSource__Task;
                    source.Task._0 = self->_task_id;

                    termina__except__action_failure(source, CTXRxBottomHalfTask__frame_ready_input, result.Failure._0);

                }

                break;

            default:

                termina__except__runtime_failure(termina__runtime_operation__task_dispatch, termina__error__invalid_id);

                break;

        }

    }

    return;

}
