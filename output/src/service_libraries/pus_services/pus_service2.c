
#include "service_libraries/pus_services/pus_service2.h"

static Status__i32 CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2ExecTCReqStatusUpdate * const exec_tc_req_status_update);

static Status__i32 CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2ExecTCReqStatusUpdate * const exec_tc_req_status_update);

static Status__i32 CPUSService2__dev_drv_on_off(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    #line 92 "src/service_libraries/pus_services/pus_service2.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 94 "src/service_libraries/pus_services/pus_service2.fin"
    uint8_t led = (uint8_t)(uint32_t)((uint32_t)(exec_tc_req_status_update->dev_address & 0xF0000000U) >> 28U);

    #line 95 "src/service_libraries/pus_services/pus_service2.fin"
    uint8_t on_off = (uint8_t)(uint32_t)(exec_tc_req_status_update->dev_address & 0xFU);

    #line 97 "src/service_libraries/pus_services/pus_service2.fin"
    self->gpio_driver.write_led(termina__ev, self->gpio_driver._that, led, on_off, &status);

    #line 99 "src/service_libraries/pus_services/pus_service2.fin"
    return status;

}

static Status__i32 CPUSService2__exec2_1TC(const termina__event_t * const termina__ev, CPUSService2 * const self, const PS2ExecTCReqStatusUpdate * const exec_tc_req_status_update) {
    
    #line 37 "src/service_libraries/pus_services/pus_service2.fin"
    Status__i32 status = { ._variant = Status__Success };

    #line 39 "src/service_libraries/pus_services/pus_service2.fin"
    if (exec_tc_req_status_update->N != 1U) {
        
        #line 41 "src/service_libraries/pus_services/pus_service2.fin"
        self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->N, &status);

    } else
    #line 46 "src/service_libraries/pus_services/pus_service2.fin"
    if (device_drv_is_on_off_address_valid(exec_tc_req_status_update) == false) {
        
        #line 48 "src/service_libraries/pus_services/pus_service2.fin"
        self->pus_service_1.send_tm_1_4_device_address_not_valid(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->dev_address, &status);

    } else
    {
        
        #line 55 "src/service_libraries/pus_services/pus_service2.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

        #line 61 "src/service_libraries/pus_services/pus_service2.fin"
        if (status._variant == Status__Success) {
            
            #line 63 "src/service_libraries/pus_services/pus_service2.fin"
            status = CPUSService2__dev_drv_on_off(termina__ev, self, exec_tc_req_status_update);

            #line 65 "src/service_libraries/pus_services/pus_service2.fin"
            if (status._variant == Status__Success) {
                
                #line 67 "src/service_libraries/pus_services/pus_service2.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->flags_ack, &status);

            } else
            {
                
                #line 75 "src/service_libraries/pus_services/pus_service2.fin"
                self->pus_service_1.send_tm_1_8_device_command_exec_error(termina__ev, self->pus_service_1._that, exec_tc_req_status_update->packet_id, exec_tc_req_status_update->packet_seq_ctrl, exec_tc_req_status_update->dev_address, &status);

            }

        }

    }

    #line 87 "src/service_libraries/pus_services/pus_service2.fin"
    return status;

}

void CPUSService2__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, Status__i32 * const action_status) {
    
    #line 102 "src/service_libraries/pus_services/pus_service2.fin"
    CPUSService2 * self = (CPUSService2 *)termina__this;

    #line 102 "src/service_libraries/pus_services/pus_service2.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 104 "src/service_libraries/pus_services/pus_service2.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 105 "src/service_libraries/pus_services/pus_service2.fin"
    PS2ExecTCReqStatusUpdate exec_tc_req_status_update = { .N = 0U, .dev_address = 0U, .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_num_bytes = 0U };

    #line 107 "src/service_libraries/pus_services/pus_service2.fin"
    exec_tc_req_status_update.packet_id = tc_handler->packet_header.packet_id;

    #line 108 "src/service_libraries/pus_services/pus_service2.fin"
    exec_tc_req_status_update.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 109 "src/service_libraries/pus_services/pus_service2.fin"
    exec_tc_req_status_update.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 110 "src/service_libraries/pus_services/pus_service2.fin"
    exec_tc_req_status_update.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 112 "src/service_libraries/pus_services/pus_service2.fin"
    Status__i32 status = tc_handler_get_u8_appdata_field(tc_handler, &exec_tc_req_status_update.N);

    #line 114 "src/service_libraries/pus_services/pus_service2.fin"
    if (status._variant == Status__Success) {
        
        #line 115 "src/service_libraries/pus_services/pus_service2.fin"
        status = tc_handler_get_u32_appdata_field(tc_handler, &exec_tc_req_status_update.dev_address);

    }

    #line 118 "src/service_libraries/pus_services/pus_service2.fin"
    if (status._variant == Status__Success) {
        
        #line 120 "src/service_libraries/pus_services/pus_service2.fin"
        if (subtype == 1U) {
            
            #line 122 "src/service_libraries/pus_services/pus_service2.fin"
            status = CPUSService2__exec2_1TC(termina__ev, self, &exec_tc_req_status_update);

        } else
        {
            
            #line 126 "src/service_libraries/pus_services/pus_service2.fin"
            status._variant = Status__Failure;
            #line 126 "src/service_libraries/pus_services/pus_service2.fin"
            status.Failure._0 = 4L;

        }

    }

    #line 133 "src/service_libraries/pus_services/pus_service2.fin"
    if (status._variant == Status__Success) {
        
        #line 135 "src/service_libraries/pus_services/pus_service2.fin"
        (*action_status)._variant = Status__Success;

    } else
    {
        
        #line 138 "src/service_libraries/pus_services/pus_service2.fin"
        const int32_t error_code = status.Failure._0;

        #line 140 "src/service_libraries/pus_services/pus_service2.fin"
        if (error_code == 4L) {
            
            #line 142 "src/service_libraries/pus_services/pus_service2.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 147 "src/service_libraries/pus_services/pus_service2.fin"
        if (error_code == 3L) {
            
            #line 149 "src/service_libraries/pus_services/pus_service2.fin"
            self->pus_service_1.send_tm_1_8_tm_exceed_limit_appdata(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, action_status);

        } else
        #line 154 "src/service_libraries/pus_services/pus_service2.fin"
        if (error_code == 5L) {
            
            #line 156 "src/service_libraries/pus_services/pus_service2.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, exec_tc_req_status_update.packet_id, exec_tc_req_status_update.packet_seq_ctrl, exec_tc_req_status_update.tc_num_bytes, action_status);

        } else
        {
            
            #line 164 "src/service_libraries/pus_services/pus_service2.fin"
            (*action_status)._variant = Status__Failure;
            #line 164 "src/service_libraries/pus_services/pus_service2.fin"
            (*action_status).Failure._0 = error_code;

        }

    }

    #line 171 "src/service_libraries/pus_services/pus_service2.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 171 "src/service_libraries/pus_services/pus_service2.fin"
    return;

}
