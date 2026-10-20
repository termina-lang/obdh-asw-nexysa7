
#include "obdh/tmtc/tm_frame_transmitter.h"

static void CTMFrameTransmitter__next_byte(const termina__event_t * const termina__ev, CTMFrameTransmitter * const self, Option__u8 * const byte);

static void CTMFrameTransmitter__pump(const termina__event_t * const termina__ev, CTMFrameTransmitter * const self);

static void CTMFrameTransmitter__next_byte(const termina__event_t * const termina__ev, CTMFrameTransmitter * const self, Option__u8 * const byte) {
    
    #line 63 "src/obdh/tmtc/tm_frame_transmitter.fin"
    Option__box current = { ._variant = Option__None };

    #line 64 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__deque__take(self->tm_frames, &current);

    #line 68 "src/obdh/tmtc/tm_frame_transmitter.fin"
    if (current._variant == Option__Some) {
        
        #line 68 "src/obdh/tmtc/tm_frame_transmitter.fin"
        const termina__box_t tm_handler = current.Some._0;

        #line 70 "src/obdh/tmtc/tm_frame_transmitter.fin"
        const size_t num_bytes = (*(TMHandler *)tm_handler.data).tm_descriptor.tm_num_bytes;

        #line 72 "src/obdh/tmtc/tm_frame_transmitter.fin"
        if (self->tx_index < 4U) {
            
            #line 74 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte)._variant = Option__Some;
            #line 74 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte).Some._0 = self->sync_word[termina__check__array_index(4U, self->tx_index)];

        } else
        #line 76 "src/obdh/tmtc/tm_frame_transmitter.fin"
        if (self->tx_index < 6U) {
            
            #line 78 "src/obdh/tmtc/tm_frame_transmitter.fin"
            uint8_t length[2U] = { 0U, 0U };

            #line 79 "src/obdh/tmtc/tm_frame_transmitter.fin"
            serialize_uint16((uint16_t)num_bytes, length);

            #line 80 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte)._variant = Option__Some;
            #line 80 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte).Some._0 = length[termina__check__array_index(2U, self->tx_index - 4U)];

        } else
        {
            
            #line 84 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte)._variant = Option__Some;
            #line 84 "src/obdh/tmtc/tm_frame_transmitter.fin"
            (*byte).Some._0 = (*(TMHandler *)tm_handler.data).tm_descriptor.tm_bytes[termina__check__array_index(256U, self->tx_index - 6U)];

        }

        #line 88 "src/obdh/tmtc/tm_frame_transmitter.fin"
        self->tx_index = self->tx_index + 1U;

        #line 90 "src/obdh/tmtc/tm_frame_transmitter.fin"
        if (self->tx_index == (size_t)(6U + num_bytes)) {
            
            #line 91 "src/obdh/tmtc/tm_frame_transmitter.fin"
            self->tx_index = 0U;

            #line 92 "src/obdh/tmtc/tm_frame_transmitter.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, tm_handler);

        } else
        {
            
            #line 94 "src/obdh/tmtc/tm_frame_transmitter.fin"
            termina__deque__put_front(self->tm_frames, tm_handler);

        }

    } else
    {
        
        #line 99 "src/obdh/tmtc/tm_frame_transmitter.fin"
        (*byte)._variant = Option__None;

    }

    #line 103 "src/obdh/tmtc/tm_frame_transmitter.fin"
    return;

}

static void CTMFrameTransmitter__pump(const termina__event_t * const termina__ev, CTMFrameTransmitter * const self) {
    
    #line 113 "src/obdh/tmtc/tm_frame_transmitter.fin"
    _Bool ready = false;

    #line 114 "src/obdh/tmtc/tm_frame_transmitter.fin"
    self->char_dev.tx_ready(termina__ev, self->char_dev._that, &ready);

    #line 116 "src/obdh/tmtc/tm_frame_transmitter.fin"
    if (ready) {
        
        #line 118 "src/obdh/tmtc/tm_frame_transmitter.fin"
        Option__u8 byte = { ._variant = Option__None };

        #line 119 "src/obdh/tmtc/tm_frame_transmitter.fin"
        CTMFrameTransmitter__next_byte(termina__ev, self, &byte);

        #line 122 "src/obdh/tmtc/tm_frame_transmitter.fin"
        if (byte._variant == Option__Some) {
            
            #line 122 "src/obdh/tmtc/tm_frame_transmitter.fin"
            const uint8_t tx_byte = byte.Some._0;

            #line 123 "src/obdh/tmtc/tm_frame_transmitter.fin"
            self->char_dev.write_byte(termina__ev, self->char_dev._that, tx_byte);

            #line 124 "src/obdh/tmtc/tm_frame_transmitter.fin"
            self->char_dev.enable_tx_irq(termina__ev, self->char_dev._that);

        } else
        {
            
            #line 127 "src/obdh/tmtc/tm_frame_transmitter.fin"
            self->char_dev.disable_tx_irq(termina__ev, self->char_dev._that);

        }

    }

    #line 132 "src/obdh/tmtc/tm_frame_transmitter.fin"
    return;

}

void CTMFrameTransmitter__send_tm(const termina__event_t * const termina__ev, void * const termina__this, const termina__box_t tm_handler) {
    
    #line 143 "src/obdh/tmtc/tm_frame_transmitter.fin"
    CTMFrameTransmitter * self = (CTMFrameTransmitter *)termina__this;

    #line 143 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 145 "src/obdh/tmtc/tm_frame_transmitter.fin"
    Option__box rejected = { ._variant = Option__None };

    #line 146 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__deque__try_put(self->tm_frames, tm_handler, &rejected);

    #line 149 "src/obdh/tmtc/tm_frame_transmitter.fin"
    if (rejected._variant == Option__Some) {
        
        #line 149 "src/obdh/tmtc/tm_frame_transmitter.fin"
        const termina__box_t rejected_tm = rejected.Some._0;

        #line 150 "src/obdh/tmtc/tm_frame_transmitter.fin"
        self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, rejected_tm);

        #line 151 "src/obdh/tmtc/tm_frame_transmitter.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    } else
    {
        

    }

    #line 157 "src/obdh/tmtc/tm_frame_transmitter.fin"
    CTMFrameTransmitter__pump(termina__ev, self);

    #line 159 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 159 "src/obdh/tmtc/tm_frame_transmitter.fin"
    return;

}

void CTMFrameTransmitter__transmit(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 166 "src/obdh/tmtc/tm_frame_transmitter.fin"
    CTMFrameTransmitter * self = (CTMFrameTransmitter *)termina__this;

    #line 166 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 168 "src/obdh/tmtc/tm_frame_transmitter.fin"
    CTMFrameTransmitter__pump(termina__ev, self);

    #line 170 "src/obdh/tmtc/tm_frame_transmitter.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 170 "src/obdh/tmtc/tm_frame_transmitter.fin"
    return;

}
