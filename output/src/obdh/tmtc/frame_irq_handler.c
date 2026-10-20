
#include "obdh/tmtc/frame_irq_handler.h"

void CTMTCFrameIRQHandler__irq_handler(const termina__event_t * const termina__ev, void * const termina__this, const uint32_t termina__ignored__vector) {
    
    (void)termina__ignored__vector;

    #line 23 "src/obdh/tmtc/frame_irq_handler.fin"
    CTMTCFrameIRQHandler * self = (CTMTCFrameIRQHandler *)termina__this;

    #line 26 "src/obdh/tmtc/frame_irq_handler.fin"
    self->tm_frame_transmitter.transmit(termina__ev, self->tm_frame_transmitter._that);

    #line 29 "src/obdh/tmtc/frame_irq_handler.fin"
    Option__u8 byte = { ._variant = Option__None };

    #line 30 "src/obdh/tmtc/frame_irq_handler.fin"
    self->char_dev.read_byte(termina__ev, self->char_dev._that, &byte);

    #line 33 "src/obdh/tmtc/frame_irq_handler.fin"
    if (byte._variant == Option__Some) {
        
        #line 33 "src/obdh/tmtc/frame_irq_handler.fin"
        const uint8_t rx_byte = byte.Some._0;

        #line 35 "src/obdh/tmtc/frame_irq_handler.fin"
        Option__box tc_handler = { ._variant = Option__None };

        #line 36 "src/obdh/tmtc/frame_irq_handler.fin"
        self->tc_frame_receiver.receive(termina__ev, self->tc_frame_receiver._that, rx_byte, &tc_handler);

        #line 39 "src/obdh/tmtc/frame_irq_handler.fin"
        if (tc_handler._variant == Option__Some) {
            
            #line 39 "src/obdh/tmtc/frame_irq_handler.fin"
            const termina__box_t tc_handler_b = tc_handler.Some._0;

            #line 40 "src/obdh/tmtc/frame_irq_handler.fin"
            termina__out_port__send(termina__ev, self->tc_message_queue_output, (const void *)&tc_handler_b);

        } else
        {
            

        }

    } else
    {
        

    }

    #line 52 "src/obdh/tmtc/frame_irq_handler.fin"
    return;

}
