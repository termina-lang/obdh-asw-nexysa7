
#include "drivers/gaisler/grgpio.h"

void CGPIODriver__init_gpio(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 52 "src/drivers/gaisler/grgpio.fin"
    CGPIODriver * self = (CGPIODriver *)termina__this;

    #line 52 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 54 "src/drivers/gaisler/grgpio.fin"
    self->registers->Direction = self->registers->Direction | 983040U;

    #line 56 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 56 "src/drivers/gaisler/grgpio.fin"
    return;

}

void CGPIODriver__write_led(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t led, const uint8_t value, Status__GPIODriverError * const status) {
    
    #line 69 "src/drivers/gaisler/grgpio.fin"
    CGPIODriver * self = (CGPIODriver *)termina__this;

    #line 69 "src/drivers/gaisler/grgpio.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 71 "src/drivers/gaisler/grgpio.fin"
    if (led > 5U && led < 10U) {
        
        #line 73 "src/drivers/gaisler/grgpio.fin"
        (*status)._variant = Status__Success;

        #line 75 "src/drivers/gaisler/grgpio.fin"
        const uint8_t bit = led + 17U;

        #line 76 "src/drivers/gaisler/grgpio.fin"
        if (value == 0U) {
            
            #line 77 "src/drivers/gaisler/grgpio.fin"
            const uint32_t mask = 0xFFFFFFFFU ^ (uint32_t)((uint32_t)1U << bit);

            #line 78 "src/drivers/gaisler/grgpio.fin"
            self->registers->Output = self->registers->Output & mask;

        } else
        {
            
            #line 80 "src/drivers/gaisler/grgpio.fin"
            self->registers->Output = self->registers->Output | (uint32_t)((uint32_t)1U << bit);

        }

    } else
    {
        
        #line 85 "src/drivers/gaisler/grgpio.fin"
        (*status)._variant = Status__Failure;
        #line 85 "src/drivers/gaisler/grgpio.fin"
        (*status).Failure._0._variant = GPIODriverError__InvalidLEDIndex;

    }

    #line 89 "src/drivers/gaisler/grgpio.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 89 "src/drivers/gaisler/grgpio.fin"
    return;

}
