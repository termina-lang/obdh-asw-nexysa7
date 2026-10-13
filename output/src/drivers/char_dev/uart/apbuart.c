
#include "drivers/char_dev/uart/apbuart.h"

const size_t hw_fifo_size = 1U;

static void CAPBUARTDriver__disable_RF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__disable_TF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_RI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_RX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_TX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__release_tx(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static _Bool CAPBUARTDriver__tf_is_empty(const termina__event_t * const termina__ev, const CAPBUARTDriver * const self);

static void CAPBUARTDriver__disable_RF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 131 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_rf = 0xFFFFFBFFU;

    #line 132 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control & riscv_uart_rf;

    #line 133 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__disable_TF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 121 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_tf = 0xFFFFFCFFU;

    #line 122 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control & riscv_uart_tf;

    #line 123 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_RI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 101 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_ri = 0x4U;

    #line 102 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_ri;

    #line 103 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_RX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 91 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_rxe = 0x1U;

    #line 92 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_rxe;

    #line 93 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 111 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_ti = 0x8U;

    #line 112 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_ti;

    #line 113 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_TX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 81 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_txe = 0x2U;

    #line 82 "src/drivers/char_dev/uart/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_txe;

    #line 83 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

void CAPBUARTDriver__initialize(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 255 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 255 "src/drivers/char_dev/uart/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 257 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__enable_RX(termina__ev, self);

    #line 258 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__enable_TX(termina__ev, self);

    #line 259 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__enable_RI(termina__ev, self);

    #line 260 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__enable_TI(termina__ev, self);

    #line 261 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__disable_TF(termina__ev, self);

    #line 262 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver__disable_RF(termina__ev, self);

    #line 264 "src/drivers/char_dev/uart/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 264 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static void CAPBUARTDriver__release_tx(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 167 "src/drivers/char_dev/uart/apbuart.fin"
    if (self->rem_bytes) {
        
        #line 169 "src/drivers/char_dev/uart/apbuart.fin"
        size_t num_elements = 0U;

        #line 171 "src/drivers/char_dev/uart/apbuart.fin"
        get_num_enqueued_elems(&self->uart_tx_queue, &num_elements);

        #line 173 "src/drivers/char_dev/uart/apbuart.fin"
        size_t sent_bytes = 0U;

        #line 174 "src/drivers/char_dev/uart/apbuart.fin"
        Option__u8 extracted_elem = { ._variant = Option__None };

        #line 176 "src/drivers/char_dev/uart/apbuart.fin"
        for (size_t i = 0U; i < 1U; i = i + 1U) {
            
            #line 178 "src/drivers/char_dev/uart/apbuart.fin"
            dequeue(&self->uart_tx_queue, &extracted_elem);

            #line 181 "src/drivers/char_dev/uart/apbuart.fin"
            if (extracted_elem._variant == Option__Some) {
                
                #line 181 "src/drivers/char_dev/uart/apbuart.fin"
                const uint8_t elem = extracted_elem.Some._0;

                #line 182 "src/drivers/char_dev/uart/apbuart.fin"
                self->registers->data = (uint32_t)elem;

                #line 183 "src/drivers/char_dev/uart/apbuart.fin"
                sent_bytes = sent_bytes + 1U;

            } else
            {
                

            }

        }

        #line 192 "src/drivers/char_dev/uart/apbuart.fin"
        if (sent_bytes < num_elements) {
            
            #line 194 "src/drivers/char_dev/uart/apbuart.fin"
            self->rem_bytes = true;

        } else
        {
            
            #line 198 "src/drivers/char_dev/uart/apbuart.fin"
            self->rem_bytes = false;

        }

    }

    #line 205 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

void CAPBUARTDriver__notify_irq(const termina__event_t * const termina__ev, void * const termina__this, CharDevIrqStatus * const status) {
    
    #line 137 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 137 "src/drivers/char_dev/uart/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 139 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t uart_status = self->registers->status;

    #line 140 "src/drivers/char_dev/uart/apbuart.fin"
    (*status)._variant = CharDevIrqStatus__IrqOk;

    #line 142 "src/drivers/char_dev/uart/apbuart.fin"
    if ((uint32_t)(uart_status & 0x4U) != 0U) {
        
        #line 144 "src/drivers/char_dev/uart/apbuart.fin"
        CAPBUARTDriver__release_tx(termina__ev, self);

    }

    #line 148 "src/drivers/char_dev/uart/apbuart.fin"
    if ((uint32_t)(uart_status & 0x1U) != 0U) {
        
        #line 150 "src/drivers/char_dev/uart/apbuart.fin"
        uint8_t byte = (uint8_t)self->registers->data;

        #line 151 "src/drivers/char_dev/uart/apbuart.fin"
        self->rx_queue.enqueue(termina__ev, self->rx_queue._that, byte, status);

    }

    #line 155 "src/drivers/char_dev/uart/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 155 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}

static _Bool CAPBUARTDriver__tf_is_empty(const termina__event_t * const termina__ev, const CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 72 "src/drivers/char_dev/uart/apbuart.fin"
    const uint32_t riscv_uart_te = 0x4U;

    #line 73 "src/drivers/char_dev/uart/apbuart.fin"
    return (uint32_t)(self->registers->status & riscv_uart_te) != 0U;

}

void CAPBUARTDriver__send(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t output_byte, Status__i32 * const status) {
    
    #line 219 "src/drivers/char_dev/uart/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 219 "src/drivers/char_dev/uart/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 222 "src/drivers/char_dev/uart/apbuart.fin"
    (*status)._variant = Status__Success;

    #line 224 "src/drivers/char_dev/uart/apbuart.fin"
    if (CAPBUARTDriver__tf_is_empty(termina__ev, self) == false || self->rem_bytes) {
        
        #line 226 "src/drivers/char_dev/uart/apbuart.fin"
        size_t num_elements = 0U;

        #line 227 "src/drivers/char_dev/uart/apbuart.fin"
        get_num_enqueued_elems(&self->uart_tx_queue, &num_elements);

        #line 229 "src/drivers/char_dev/uart/apbuart.fin"
        if ((size_t)(1024U - num_elements) >= 1U) {
            
            #line 231 "src/drivers/char_dev/uart/apbuart.fin"
            *status = enqueue(&self->uart_tx_queue, output_byte);

            #line 232 "src/drivers/char_dev/uart/apbuart.fin"
            self->rem_bytes = true;

        } else
        {
            
            #line 235 "src/drivers/char_dev/uart/apbuart.fin"
            (*status)._variant = Status__Failure;
            #line 235 "src/drivers/char_dev/uart/apbuart.fin"
            (*status).Failure._0 = 2L;

        }

    } else
    {
        
        #line 240 "src/drivers/char_dev/uart/apbuart.fin"
        self->registers->data = (uint32_t)output_byte;

    }

    #line 244 "src/drivers/char_dev/uart/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 244 "src/drivers/char_dev/uart/apbuart.fin"
    return;

}
