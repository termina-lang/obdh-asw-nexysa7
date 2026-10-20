
#include "obdh/pus/services/service2.h"

static Status__GPIODriverError CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request);

static Status__PUSService2Error CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request);

static Status__GPIODriverError CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request) {
    
    #line 76 "src/obdh/pus/services/service2.fin"
    Status__GPIODriverError status = { ._variant = Status__Success };

    #line 78 "src/obdh/pus/services/service2.fin"
    uint8_t led = (uint8_t)(uint32_t)((uint32_t)(tc_request->dev_address & 0xF0000000U) >> 28U);

    #line 79 "src/obdh/pus/services/service2.fin"
    uint8_t on_off = (uint8_t)(uint32_t)(tc_request->dev_address & 0xFU);

    #line 81 "src/obdh/pus/services/service2.fin"
    self->gpio_driver.write_led(termina__ev, self->gpio_driver._that, led, on_off, &status);

    #line 83 "src/obdh/pus/services/service2.fin"
    return status;

}

static Status__PUSService2Error CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request) {
    
    #line 37 "src/obdh/pus/services/service2.fin"
    Status__PUSService2Error status = { ._variant = Status__Success };

    #line 39 "src/obdh/pus/services/service2.fin"
    if (tc_request->N != 1U) {
        
        #line 41 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 41 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__NumOfInstrNotValid;
        #line 41 "src/obdh/pus/services/service2.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 43 "src/obdh/pus/services/service2.fin"
    if (device_drv_is_on_off_address_valid(tc_request) == false) {
        
        #line 45 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 45 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__DeviceAddressNotValid;
        #line 45 "src/obdh/pus/services/service2.fin"
        status.Failure._0.DeviceAddressNotValid._0 = tc_request->dev_address;

    } else
    {
        
        #line 49 "src/obdh/pus/services/service2.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 54 "src/obdh/pus/services/service2.fin"
        const Status__GPIODriverError led_status = CPUSService2__dev_drv_on_off(termina__ev, self, tc_request);

        #line 56 "src/obdh/pus/services/service2.fin"
        if (led_status._variant == Status__Success) {
            
            #line 58 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 65 "src/obdh/pus/services/service2.fin"
            status._variant = Status__Failure;
            #line 65 "src/obdh/pus/services/service2.fin"
            status.Failure._0._variant = PUSService2Error__DeviceCommandExecError;
            #line 65 "src/obdh/pus/services/service2.fin"
            status.Failure._0.DeviceCommandExecError._0 = tc_request->dev_address;

        }

    }

    #line 71 "src/obdh/pus/services/service2.fin"
    return status;

}

void CPUSService2__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 86 "src/obdh/pus/services/service2.fin"
    CPUSService2 * self = (CPUSService2 *)termina__this;

    #line 86 "src/obdh/pus/services/service2.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 88 "src/obdh/pus/services/service2.fin"
    Status__PUSService2Error status = { ._variant = Status__Success };

    #line 89 "src/obdh/pus/services/service2.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 90 "src/obdh/pus/services/service2.fin"
    PS2TCRequest tc_request = { .N = 0U, .dev_address = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 92 "src/obdh/pus/services/service2.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 93 "src/obdh/pus/services/service2.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 94 "src/obdh/pus/services/service2.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 95 "src/obdh/pus/services/service2.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 97 "src/obdh/pus/services/service2.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    #line 99 "src/obdh/pus/services/service2.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 100 "src/obdh/pus/services/service2.fin"
        tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &tc_request.dev_address);

    }

    #line 103 "src/obdh/pus/services/service2.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 104 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 104 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__AppDataOutOfRange;
        #line 104 "src/obdh/pus/services/service2.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 107 "src/obdh/pus/services/service2.fin"
    if (status._variant == Status__Success) {
        
        #line 109 "src/obdh/pus/services/service2.fin"
        if (subtype == 1U) {
            
            #line 111 "src/obdh/pus/services/service2.fin"
            status = CPUSService2__exec2_1TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 115 "src/obdh/pus/services/service2.fin"
            status._variant = Status__Failure;
            #line 115 "src/obdh/pus/services/service2.fin"
            status.Failure._0._variant = PUSService2Error__ErrorInAcceptance;

        }

    }

    #line 122 "src/obdh/pus/services/service2.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 125 "src/obdh/pus/services/service2.fin"
        const PUSService2Error error = status.Failure._0;

        #line 129 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__ErrorInAcceptance) {
            
            #line 131 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 136 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__AppDataOutOfRange) {
            
            #line 136 "src/obdh/pus/services/service2.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 138 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 144 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__NumOfInstrNotValid) {
            
            #line 144 "src/obdh/pus/services/service2.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 146 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        #line 152 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__DeviceAddressNotValid) {
            
            #line 152 "src/obdh/pus/services/service2.fin"
            const uint32_t dev_address = error.DeviceAddressNotValid._0;

            #line 154 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_device_address_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, dev_address);

        } else
        {
            
            #line 160 "src/obdh/pus/services/service2.fin"
            const uint32_t dev_address = error.DeviceCommandExecError._0;

            #line 162 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_8_device_command_exec_error(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, dev_address);

        }

    }

    #line 173 "src/obdh/pus/services/service2.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 173 "src/obdh/pus/services/service2.fin"
    return;

}
