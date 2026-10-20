
#include "drivers/gaisler/apbuart.h"

static void CAPBUARTDriver__disable_RF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__disable_TF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__disable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_RI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_RX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__enable_TX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self);

static void CAPBUARTDriver__disable_RF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 118 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_rf = 0xFFFFFBFFU;

    #line 119 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control & riscv_uart_rf;

    #line 120 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__disable_TF(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 108 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_tf = 0xFFFFFCFFU;

    #line 109 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control & riscv_uart_tf;

    #line 110 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__disable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 98 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_ti = 0xFFFFFFF7U;

    #line 99 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control & riscv_uart_ti;

    #line 100 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__disable_tx_irq(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 164 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 164 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 166 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__disable_TI(termina__ev, self);

    #line 168 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 168 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_RI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 78 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_ri = 0x4U;

    #line 79 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_ri;

    #line 80 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_RX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 68 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_rxe = 0x1U;

    #line 69 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_rxe;

    #line 70 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_TI(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 88 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_ti = 0x8U;

    #line 89 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_ti;

    #line 90 "src/drivers/gaisler/apbuart.fin"
    return;

}

static void CAPBUARTDriver__enable_TX(const termina__event_t * const termina__ev, CAPBUARTDriver * const self) {
    
    (void)termina__ev;

    #line 58 "src/drivers/gaisler/apbuart.fin"
    const uint32_t riscv_uart_txe = 0x2U;

    #line 59 "src/drivers/gaisler/apbuart.fin"
    self->registers->control = self->registers->control | riscv_uart_txe;

    #line 60 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__enable_tx_irq(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 155 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 155 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 157 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__enable_TI(termina__ev, self);

    #line 159 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 159 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__initialize(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 179 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 179 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 181 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__enable_RX(termina__ev, self);

    #line 182 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__enable_TX(termina__ev, self);

    #line 183 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__enable_RI(termina__ev, self);

    #line 184 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__disable_TF(termina__ev, self);

    #line 185 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver__disable_RF(termina__ev, self);

    #line 187 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 187 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__read_byte(const termina__event_t * const termina__ev, void * const termina__this, Option__u8 * const byte) {
    
    #line 124 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 124 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 126 "src/drivers/gaisler/apbuart.fin"
    if ((uint32_t)(self->registers->status & 0x1U) != 0U) {
        
        #line 127 "src/drivers/gaisler/apbuart.fin"
        (*byte)._variant = Option__Some;
        #line 127 "src/drivers/gaisler/apbuart.fin"
        (*byte).Some._0 = (uint8_t)self->registers->data;

    } else
    {
        
        #line 129 "src/drivers/gaisler/apbuart.fin"
        (*byte)._variant = Option__None;

    }

    #line 132 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 132 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__tx_ready(const termina__event_t * const termina__ev, void * const termina__this, _Bool * const ready) {
    
    #line 137 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 137 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 139 "src/drivers/gaisler/apbuart.fin"
    *ready = (uint32_t)(self->registers->status & 0x4U) != 0U;

    #line 141 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 141 "src/drivers/gaisler/apbuart.fin"
    return;

}

void CAPBUARTDriver__write_byte(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t byte) {
    
    #line 146 "src/drivers/gaisler/apbuart.fin"
    CAPBUARTDriver * self = (CAPBUARTDriver *)termina__this;

    #line 146 "src/drivers/gaisler/apbuart.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 148 "src/drivers/gaisler/apbuart.fin"
    self->registers->data = (uint32_t)byte;

    #line 150 "src/drivers/gaisler/apbuart.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 150 "src/drivers/gaisler/apbuart.fin"
    return;

}
