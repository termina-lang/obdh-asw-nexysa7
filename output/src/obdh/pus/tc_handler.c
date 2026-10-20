
#include "obdh/pus/tc_handler.h"

void tc_handler_build(TCHandler * const tc_handler) {
    
    #line 63 "src/obdh/pus/tc_handler.fin"
    tc_get_fields(tc_handler->tc_descriptor.tc_bytes, &tc_handler->packet_header, &tc_handler->df_header, &tc_handler->packet_error_ctrl);

    #line 68 "src/obdh/pus/tc_handler.fin"
    tc_handler->app_data_index = 11U;

    #line 70 "src/obdh/pus/tc_handler.fin"
    return;

}

_Bool tc_handler_is_valid_next_appdata_field(const TCHandler * const tc_handler, const size_t field_size) {
    
    #line 84 "src/obdh/pus/tc_handler.fin"
    _Bool res = false;

    #line 86 "src/obdh/pus/tc_handler.fin"
    size_t required_size = tc_handler->app_data_index + field_size;

    #line 88 "src/obdh/pus/tc_handler.fin"
    if (required_size <= tc_handler->tc_descriptor.tc_num_bytes) {
        
        #line 89 "src/obdh/pus/tc_handler.fin"
        res = true;

    }

    #line 92 "src/obdh/pus/tc_handler.fin"
    return res;

}

Status__TCHandlerError tc_handler_get_u8_appdata_field(TCHandler * const tc_handler, uint8_t * const data) {
    
    #line 109 "src/obdh/pus/tc_handler.fin"
    Status__TCHandlerError status = { ._variant = Status__Success };

    #line 111 "src/obdh/pus/tc_handler.fin"
    if (tc_handler_is_valid_next_appdata_field(tc_handler, 1U)) {
        
        #line 113 "src/obdh/pus/tc_handler.fin"
        *data = tc_handler->tc_descriptor.tc_bytes[termina__check__array_index(256U, tc_handler->app_data_index)];

        #line 114 "src/obdh/pus/tc_handler.fin"
        tc_handler->app_data_index = tc_handler->app_data_index + 1U;

    } else
    {
        
        #line 118 "src/obdh/pus/tc_handler.fin"
        status._variant = Status__Failure;
        #line 118 "src/obdh/pus/tc_handler.fin"
        status.Failure._0._variant = TCHandlerError__AppDataOutOfRange;

    }

    #line 122 "src/obdh/pus/tc_handler.fin"
    return status;

}

Status__TCHandlerError tc_handler_get_u16_appdata_field(TCHandler * const tc_handler, uint16_t * const data) {
    
    #line 138 "src/obdh/pus/tc_handler.fin"
    Status__TCHandlerError status = { ._variant = Status__Success };

    #line 140 "src/obdh/pus/tc_handler.fin"
    if (tc_handler_is_valid_next_appdata_field(tc_handler, 2U)) {
        
        #line 142 "src/obdh/pus/tc_handler.fin"
        *data = deserialize_uint16(&tc_handler->tc_descriptor.tc_bytes[termina__check__array_slice(256U, 2U, tc_handler->app_data_index, tc_handler->app_data_index + 2U)]);

        #line 143 "src/obdh/pus/tc_handler.fin"
        tc_handler->app_data_index = tc_handler->app_data_index + 2U;

    } else
    {
        
        #line 147 "src/obdh/pus/tc_handler.fin"
        status._variant = Status__Failure;
        #line 147 "src/obdh/pus/tc_handler.fin"
        status.Failure._0._variant = TCHandlerError__AppDataOutOfRange;

    }

    #line 151 "src/obdh/pus/tc_handler.fin"
    return status;

}

Status__TCHandlerError tc_handler_get_u32_appdata_field(TCHandler * const tc_handler, uint32_t * const data) {
    
    #line 167 "src/obdh/pus/tc_handler.fin"
    Status__TCHandlerError status = { ._variant = Status__Success };

    #line 169 "src/obdh/pus/tc_handler.fin"
    if (tc_handler_is_valid_next_appdata_field(tc_handler, 4U)) {
        
        #line 171 "src/obdh/pus/tc_handler.fin"
        *data = deserialize_uint32(&tc_handler->tc_descriptor.tc_bytes[termina__check__array_slice(256U, 4U, tc_handler->app_data_index, tc_handler->app_data_index + 4U)]);

        #line 172 "src/obdh/pus/tc_handler.fin"
        tc_handler->app_data_index = tc_handler->app_data_index + 4U;

    } else
    {
        
        #line 176 "src/obdh/pus/tc_handler.fin"
        status._variant = Status__Failure;
        #line 176 "src/obdh/pus/tc_handler.fin"
        status.Failure._0._variant = TCHandlerError__AppDataOutOfRange;

    }

    #line 180 "src/obdh/pus/tc_handler.fin"
    return status;

}
