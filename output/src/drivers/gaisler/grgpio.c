
#include "drivers/gaisler/grgpio.h"

void CGRGPIODriver__init_gpio(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 41 "src/drivers/gaisler/grgpio.fin"
    CGRGPIODriver * self = (CGRGPIODriver *)termina__this;

    #line 41 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 43 "src/drivers/gaisler/grgpio.fin"
    self->registers->Direction = self->registers->Direction | self->output_mask;

    #line 45 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 45 "src/drivers/gaisler/grgpio.fin"
    return;

}

void CGRGPIODriver__read_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin, GPIOPinState * const state) {
    
    #line 71 "src/drivers/gaisler/grgpio.fin"
    CGRGPIODriver * self = (CGRGPIODriver *)termina__this;

    #line 71 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 73 "src/drivers/gaisler/grgpio.fin"
    if ((uint32_t)(self->registers->Data & (uint32_t)((uint32_t)1U << termina__check__shift_amount(32U, (uint32_t)pin.pin))) != 0U) {
        
        #line 74 "src/drivers/gaisler/grgpio.fin"
        (*state)._variant = GPIOPinState__High;

    } else
    {
        
        #line 76 "src/drivers/gaisler/grgpio.fin"
        (*state)._variant = GPIOPinState__Low;

    }

    #line 79 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 79 "src/drivers/gaisler/grgpio.fin"
    return;

}

void CGRGPIODriver__toggle_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin) {
    
    #line 64 "src/drivers/gaisler/grgpio.fin"
    CGRGPIODriver * self = (CGRGPIODriver *)termina__this;

    #line 64 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 66 "src/drivers/gaisler/grgpio.fin"
    self->registers->Output = self->registers->Output ^ (uint32_t)((uint32_t)1U << termina__check__shift_amount(32U, (uint32_t)pin.pin));

    #line 68 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 68 "src/drivers/gaisler/grgpio.fin"
    return;

}

void CGRGPIODriver__write_pin(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin, const GPIOPinState state) {
    
    #line 48 "src/drivers/gaisler/grgpio.fin"
    CGRGPIODriver * self = (CGRGPIODriver *)termina__this;

    #line 48 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 50 "src/drivers/gaisler/grgpio.fin"
    const uint32_t bit = (uint32_t)1U << termina__check__shift_amount(32U, (uint32_t)pin.pin);

    #line 53 "src/drivers/gaisler/grgpio.fin"
    if (state._variant == GPIOPinState__Low) {
        
        #line 54 "src/drivers/gaisler/grgpio.fin"
        self->registers->Output = self->registers->Output & (uint32_t)(0xFFFFFFFFU ^ bit);

    } else
    {
        
        #line 57 "src/drivers/gaisler/grgpio.fin"
        self->registers->Output = self->registers->Output | bit;

    }

    #line 61 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 61 "src/drivers/gaisler/grgpio.fin"
    return;

}
