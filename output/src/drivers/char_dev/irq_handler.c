
#include "drivers/char_dev/irq_handler.h"

Status__i32 CCharDevIRQHandler__irq_handler(const termina__event_t * const termina__ev, void * const termina__this, const uint32_t termina__ignored__vector) {
    
    (void)termina__ignored__vector;

    #line 14 "src/drivers/char_dev/irq_handler.fin"
    CCharDevIRQHandler * self = (CCharDevIRQHandler *)termina__this;

    #line 16 "src/drivers/char_dev/irq_handler.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 17 "src/drivers/char_dev/irq_handler.fin"
    CharDevIrqStatus result = { ._variant = CharDevIrqStatus__IrqOk };

    #line 19 "src/drivers/char_dev/irq_handler.fin"
    self->uart_drv.notify_irq(termina__ev, self->uart_drv._that, &result);

    #line 22 "src/drivers/char_dev/irq_handler.fin"
    if (result._variant == CharDevIrqStatus__RxComplete) {
        
        #line 22 "src/drivers/char_dev/irq_handler.fin"
        const size_t size = result.RxComplete._0;

        #line 23 "src/drivers/char_dev/irq_handler.fin"
        termina__out_port__send(termina__ev, self->frame_ready_output, (const void *)&size);

    } else
    #line 25 "src/drivers/char_dev/irq_handler.fin"
    if (result._variant == CharDevIrqStatus__IrqOk) {
        

    } else
    {
        
        #line 28 "src/drivers/char_dev/irq_handler.fin"
        const int32_t error_code = result.IrqError._0;

        #line 29 "src/drivers/char_dev/irq_handler.fin"
        status._variant = Status__Failure;
        #line 29 "src/drivers/char_dev/irq_handler.fin"
        status.Failure._0 = error_code;

    }

    #line 33 "src/drivers/char_dev/irq_handler.fin"
    return status;

}
