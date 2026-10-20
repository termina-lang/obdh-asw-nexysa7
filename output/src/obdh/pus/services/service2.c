
#include "obdh/pus/services/service2.h"

static void CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request);

static _Bool CPUSService2__is_device_address_valid(const termina__event_t * const termina__ev, const CPUSService2 * const self, const uint32_t dev_address);

static Status__PUSService2Error CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request);

static void CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request) {
    
    #line 86 "src/obdh/pus/services/service2.fin"
    const size_t device = (size_t)(uint32_t)((uint32_t)(tc_request->dev_address & 0xF0000000U) >> 28U);

    #line 89 "src/obdh/pus/services/service2.fin"
    if (self->device_pins[device]._variant == Option__Some) {
        
        #line 89 "src/obdh/pus/services/service2.fin"
        const GPIOPinId pin = self->device_pins[device].Some._0;

        #line 90 "src/obdh/pus/services/service2.fin"
        if ((uint32_t)(tc_request->dev_address & 0x1U) == 0U) {
            
            #line 91 "src/obdh/pus/services/service2.fin"
            self->gpio.write_pin(termina__ev, self->gpio._that, pin, (GPIOPinState){ ._variant = GPIOPinState__Low });

        } else
        {
            
            #line 93 "src/obdh/pus/services/service2.fin"
            self->gpio.write_pin(termina__ev, self->gpio._that, pin, (GPIOPinState){ ._variant = GPIOPinState__High });

        }

    } else
    {
        

    }

    #line 100 "src/obdh/pus/services/service2.fin"
    return;

}

static _Bool CPUSService2__is_device_address_valid(const termina__event_t * const termina__ev, const CPUSService2 * const self, const uint32_t dev_address) {
    
    (void)termina__ev;

    #line 35 "src/obdh/pus/services/service2.fin"
    _Bool is_valid = false;

    #line 37 "src/obdh/pus/services/service2.fin"
    if ((uint32_t)(dev_address & 0xFFFFFFEU) == 0U) {
        
        #line 39 "src/obdh/pus/services/service2.fin"
        const size_t device = (size_t)(uint32_t)((uint32_t)(dev_address & 0xF0000000U) >> 28U);

        #line 42 "src/obdh/pus/services/service2.fin"
        if (self->device_pins[device]._variant == Option__Some) {
            
            #line 43 "src/obdh/pus/services/service2.fin"
            is_valid = true;

        } else
        {
            

        }

    }

    #line 50 "src/obdh/pus/services/service2.fin"
    return is_valid;

}

static Status__PUSService2Error CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2TCRequest * const tc_request) {
    
    #line 55 "src/obdh/pus/services/service2.fin"
    Status__PUSService2Error status = { ._variant = Status__Success };

    #line 57 "src/obdh/pus/services/service2.fin"
    if (tc_request->N != 1U) {
        
        #line 59 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 59 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__NumOfInstrNotValid;
        #line 59 "src/obdh/pus/services/service2.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->N;

    } else
    #line 61 "src/obdh/pus/services/service2.fin"
    if (CPUSService2__is_device_address_valid(termina__ev, self, tc_request->dev_address) == false) {
        
        #line 63 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 63 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__DeviceAddressNotValid;
        #line 63 "src/obdh/pus/services/service2.fin"
        status.Failure._0.DeviceAddressNotValid._0 = tc_request->dev_address;

    } else
    {
        
        #line 67 "src/obdh/pus/services/service2.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 72 "src/obdh/pus/services/service2.fin"
        CPUSService2__dev_drv_on_off(termina__ev, self, tc_request);

        #line 74 "src/obdh/pus/services/service2.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    }

    #line 81 "src/obdh/pus/services/service2.fin"
    return status;

}

void CPUSService2__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 103 "src/obdh/pus/services/service2.fin"
    CPUSService2 * self = (CPUSService2 *)termina__this;

    #line 103 "src/obdh/pus/services/service2.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 105 "src/obdh/pus/services/service2.fin"
    Status__PUSService2Error status = { ._variant = Status__Success };

    #line 106 "src/obdh/pus/services/service2.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 107 "src/obdh/pus/services/service2.fin"
    PS2TCRequest tc_request = { .N = 0U, .dev_address = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 109 "src/obdh/pus/services/service2.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 110 "src/obdh/pus/services/service2.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 111 "src/obdh/pus/services/service2.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 112 "src/obdh/pus/services/service2.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 114 "src/obdh/pus/services/service2.fin"
    Status__TCHandlerError tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.N);

    #line 116 "src/obdh/pus/services/service2.fin"
    if (tc_data_status._variant == Status__Success) {
        
        #line 117 "src/obdh/pus/services/service2.fin"
        tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &tc_request.dev_address);

    }

    #line 120 "src/obdh/pus/services/service2.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 121 "src/obdh/pus/services/service2.fin"
        status._variant = Status__Failure;
        #line 121 "src/obdh/pus/services/service2.fin"
        status.Failure._0._variant = PUSService2Error__AppDataOutOfRange;
        #line 121 "src/obdh/pus/services/service2.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 124 "src/obdh/pus/services/service2.fin"
    if (status._variant == Status__Success) {
        
        #line 126 "src/obdh/pus/services/service2.fin"
        if (subtype == 1U) {
            
            #line 128 "src/obdh/pus/services/service2.fin"
            status = CPUSService2__exec2_1TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 132 "src/obdh/pus/services/service2.fin"
            status._variant = Status__Failure;
            #line 132 "src/obdh/pus/services/service2.fin"
            status.Failure._0._variant = PUSService2Error__ErrorInAcceptance;

        }

    }

    #line 139 "src/obdh/pus/services/service2.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 142 "src/obdh/pus/services/service2.fin"
        const PUSService2Error error = status.Failure._0;

        #line 146 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__ErrorInAcceptance) {
            
            #line 148 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 153 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__AppDataOutOfRange) {
            
            #line 153 "src/obdh/pus/services/service2.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 155 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 161 "src/obdh/pus/services/service2.fin"
        if (error._variant == PUSService2Error__NumOfInstrNotValid) {
            
            #line 161 "src/obdh/pus/services/service2.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 163 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        {
            
            #line 169 "src/obdh/pus/services/service2.fin"
            const uint32_t dev_address = error.DeviceAddressNotValid._0;

            #line 171 "src/obdh/pus/services/service2.fin"
            self->pus_service_1.send_tm_1_4_device_address_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, dev_address);

        }

    }

    #line 182 "src/obdh/pus/services/service2.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 182 "src/obdh/pus/services/service2.fin"
    return;

}
