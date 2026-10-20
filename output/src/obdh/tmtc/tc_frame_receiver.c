
#include "obdh/tmtc/tc_frame_receiver.h"

static size_t CTCFrameReceiver__sync(const termina__event_t * const termina__ev, CTCFrameReceiver * const self, const uint8_t byte);

static size_t CTCFrameReceiver__sync(const termina__event_t * const termina__ev, CTCFrameReceiver * const self, const uint8_t byte) {
    
    (void)termina__ev;

    #line 61 "src/obdh/tmtc/tc_frame_receiver.fin"
    size_t length = 0U;

    #line 65 "src/obdh/tmtc/tc_frame_receiver.fin"
    if (self->rx_status._variant == TCFrameRxStatus__SyncBytesRx) {
        
        #line 67 "src/obdh/tmtc/tc_frame_receiver.fin"
        if (byte == self->sync_word[termina__check__array_index(4U, self->sync_index)]) {
            
            #line 69 "src/obdh/tmtc/tc_frame_receiver.fin"
            if (3U == self->sync_index) {
                
                #line 70 "src/obdh/tmtc/tc_frame_receiver.fin"
                self->sync_index = 0U;

                #line 71 "src/obdh/tmtc/tc_frame_receiver.fin"
                self->rx_status._variant = TCFrameRxStatus__SyncLengthRx;

            } else
            {
                
                #line 73 "src/obdh/tmtc/tc_frame_receiver.fin"
                self->sync_index = self->sync_index + 1U;

            }

        } else
        {
            
            #line 77 "src/obdh/tmtc/tc_frame_receiver.fin"
            self->sync_index = 0U;

        }

    } else
    {
        
        #line 83 "src/obdh/tmtc/tc_frame_receiver.fin"
        self->raw_rx_tc_length[termina__check__array_index(2U, self->sync_index)] = byte;

        #line 84 "src/obdh/tmtc/tc_frame_receiver.fin"
        self->sync_index = self->sync_index + 1U;

        #line 86 "src/obdh/tmtc/tc_frame_receiver.fin"
        if (2U == self->sync_index) {
            
            #line 88 "src/obdh/tmtc/tc_frame_receiver.fin"
            const size_t num_bytes = (size_t)deserialize_uint16(self->raw_rx_tc_length);

            #line 90 "src/obdh/tmtc/tc_frame_receiver.fin"
            if (num_bytes > 0U && num_bytes < 256U) {
                
                #line 91 "src/obdh/tmtc/tc_frame_receiver.fin"
                length = num_bytes;

            }

            #line 94 "src/obdh/tmtc/tc_frame_receiver.fin"
            self->rx_status._variant = TCFrameRxStatus__SyncBytesRx;

            #line 95 "src/obdh/tmtc/tc_frame_receiver.fin"
            self->sync_index = 0U;

        }

    }

    #line 100 "src/obdh/tmtc/tc_frame_receiver.fin"
    return length;

}

void CTCFrameReceiver__receive(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte, Option__box * const tc_handler) {
    
    #line 109 "src/obdh/tmtc/tc_frame_receiver.fin"
    CTCFrameReceiver * self = (CTCFrameReceiver *)termina__this;

    #line 109 "src/obdh/tmtc/tc_frame_receiver.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 111 "src/obdh/tmtc/tc_frame_receiver.fin"
    Option__box current = { ._variant = Option__None };

    #line 112 "src/obdh/tmtc/tc_frame_receiver.fin"
    termina__deque__take(self->tc_frame, &current);

    #line 116 "src/obdh/tmtc/tc_frame_receiver.fin"
    if (current._variant == Option__Some) {
        
        #line 116 "src/obdh/tmtc/tc_frame_receiver.fin"
        const termina__box_t tc_handler_b = current.Some._0;

        #line 118 "src/obdh/tmtc/tc_frame_receiver.fin"
        (*(TCHandler *)tc_handler_b.data).tc_descriptor.tc_bytes[termina__check__array_index(256U, self->rx_index)] = byte;

        #line 119 "src/obdh/tmtc/tc_frame_receiver.fin"
        self->rx_index = self->rx_index + 1U;

        #line 121 "src/obdh/tmtc/tc_frame_receiver.fin"
        if (self->rx_index == (*(TCHandler *)tc_handler_b.data).tc_descriptor.tc_num_bytes) {
            
            #line 122 "src/obdh/tmtc/tc_frame_receiver.fin"
            self->rx_index = 0U;

            #line 123 "src/obdh/tmtc/tc_frame_receiver.fin"
            (*tc_handler)._variant = Option__Some;
            #line 123 "src/obdh/tmtc/tc_frame_receiver.fin"
            (*tc_handler).Some._0 = tc_handler_b;

        } else
        {
            
            #line 125 "src/obdh/tmtc/tc_frame_receiver.fin"
            termina__deque__put(self->tc_frame, tc_handler_b);

            #line 126 "src/obdh/tmtc/tc_frame_receiver.fin"
            (*tc_handler)._variant = Option__None;

        }

    } else
    {
        
        #line 132 "src/obdh/tmtc/tc_frame_receiver.fin"
        const size_t length = CTCFrameReceiver__sync(termina__ev, self, byte);

        #line 134 "src/obdh/tmtc/tc_frame_receiver.fin"
        if (length > 0U) {
            
            #line 136 "src/obdh/tmtc/tc_frame_receiver.fin"
            Option__box new_tc_handler = { ._variant = Option__None };

            #line 137 "src/obdh/tmtc/tc_frame_receiver.fin"
            self->tc_handler_pool.alloc(termina__ev, self->tc_handler_pool._that, &new_tc_handler);

            #line 140 "src/obdh/tmtc/tc_frame_receiver.fin"
            if (new_tc_handler._variant == Option__Some) {
                
                #line 140 "src/obdh/tmtc/tc_frame_receiver.fin"
                const termina__box_t tc_handler_b = new_tc_handler.Some._0;

                #line 141 "src/obdh/tmtc/tc_frame_receiver.fin"
                (*(TCHandler *)tc_handler_b.data).tc_descriptor.tc_num_bytes = length;

                #line 142 "src/obdh/tmtc/tc_frame_receiver.fin"
                termina__deque__put(self->tc_frame, tc_handler_b);

            } else
            {
                

            }

        }

        #line 151 "src/obdh/tmtc/tc_frame_receiver.fin"
        (*tc_handler)._variant = Option__None;

    }

    #line 155 "src/obdh/tmtc/tc_frame_receiver.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 155 "src/obdh/tmtc/tc_frame_receiver.fin"
    return;

}
