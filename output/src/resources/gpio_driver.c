
#include "resources/gpio_driver.h"

void CGPIODriver__init_gpio(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 46 "src/resources/gpio_driver.fin"
    CGPIODriver * self = (CGPIODriver *)termina__this;

    #line 46 "src/resources/gpio_driver.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 48 "src/resources/gpio_driver.fin"
    self->registers->Direction = self->registers->Direction | 983040U;

    #line 50 "src/resources/gpio_driver.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 50 "src/resources/gpio_driver.fin"
    return;

}

void CGPIODriver__write_led(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t led, const uint8_t value, Status__i32 * const status) {
    
    #line 63 "src/resources/gpio_driver.fin"
    CGPIODriver * self = (CGPIODriver *)termina__this;

    #line 63 "src/resources/gpio_driver.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 65 "src/resources/gpio_driver.fin"
    if (led > 5U && led < 10U) {
        
        #line 67 "src/resources/gpio_driver.fin"
        (*status)._variant = Status__Success;

        #line 69 "src/resources/gpio_driver.fin"
        const uint8_t bit = led + 17U;

        #line 70 "src/resources/gpio_driver.fin"
        if (value == 0U) {
            
            #line 71 "src/resources/gpio_driver.fin"
            const uint32_t mask = 0xFFFFFFFFU ^ (uint32_t)((uint32_t)1U << bit);

            #line 72 "src/resources/gpio_driver.fin"
            self->registers->Output = self->registers->Output & mask;

        } else
        {
            
            #line 74 "src/resources/gpio_driver.fin"
            self->registers->Output = self->registers->Output | (uint32_t)((uint32_t)1U << bit);

        }

    } else
    {
        
        #line 79 "src/resources/gpio_driver.fin"
        (*status)._variant = Status__Failure;
        #line 79 "src/resources/gpio_driver.fin"
        (*status).Failure._0 = 7L;

    }

    #line 83 "src/resources/gpio_driver.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 83 "src/resources/gpio_driver.fin"
    return;

}
