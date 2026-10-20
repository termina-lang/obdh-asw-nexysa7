
#include "obdh/pus/tm_handler.h"

const uint16_t APID = 0x32CU;

const uint16_t DESTINATION_ID = 0x78U;

const size_t tm_app_data_offset = 19U;

Status__TMHandlerError append_u8_appdata_field(TMHandler * const tm_handler, const uint8_t data) {
    
    #line 66 "src/obdh/pus/tm_handler.fin"
    Status__TMHandlerError status = { ._variant = Status__Success };

    #line 68 "src/obdh/pus/tm_handler.fin"
    if (tm_handler->app_data_index < 256U) {
        
        #line 70 "src/obdh/pus/tm_handler.fin"
        tm_handler->tm_descriptor.tm_bytes[termina__check__array_index(256U, tm_handler->app_data_index)] = data;

        #line 71 "src/obdh/pus/tm_handler.fin"
        tm_handler->app_data_index = tm_handler->app_data_index + 1U;

    } else
    {
        
        #line 75 "src/obdh/pus/tm_handler.fin"
        status._variant = Status__Failure;
        #line 75 "src/obdh/pus/tm_handler.fin"
        status.Failure._0._variant = TMHandlerError__AppDataOverflow;

    }

    #line 79 "src/obdh/pus/tm_handler.fin"
    return status;

}

Status__TMHandlerError append_u16_appdata_field(TMHandler * const tm_handler, const uint16_t data) {
    
    #line 93 "src/obdh/pus/tm_handler.fin"
    Status__TMHandlerError status = { ._variant = Status__Success };

    #line 95 "src/obdh/pus/tm_handler.fin"
    if ((size_t)(tm_handler->app_data_index + 1U) < 256U) {
        
        #line 97 "src/obdh/pus/tm_handler.fin"
        serialize_uint16(data, &tm_handler->tm_descriptor.tm_bytes[termina__check__array_slice(256U, 2U, tm_handler->app_data_index, tm_handler->app_data_index + 2U)]);

        #line 98 "src/obdh/pus/tm_handler.fin"
        tm_handler->app_data_index = tm_handler->app_data_index + 2U;

    } else
    {
        
        #line 102 "src/obdh/pus/tm_handler.fin"
        status._variant = Status__Failure;
        #line 102 "src/obdh/pus/tm_handler.fin"
        status.Failure._0._variant = TMHandlerError__AppDataOverflow;

    }

    #line 105 "src/obdh/pus/tm_handler.fin"
    return status;

}

Status__TMHandlerError append_u32_appdata_field(TMHandler * const tm_handler, const uint32_t data) {
    
    #line 119 "src/obdh/pus/tm_handler.fin"
    Status__TMHandlerError status = { ._variant = Status__Success };

    #line 121 "src/obdh/pus/tm_handler.fin"
    if ((size_t)(tm_handler->app_data_index + 3U) < 256U) {
        
        #line 123 "src/obdh/pus/tm_handler.fin"
        serialize_uint32(data, &tm_handler->tm_descriptor.tm_bytes[termina__check__array_slice(256U, 4U, tm_handler->app_data_index, tm_handler->app_data_index + 4U)]);

        #line 124 "src/obdh/pus/tm_handler.fin"
        tm_handler->app_data_index = tm_handler->app_data_index + 4U;

    } else
    {
        
        #line 128 "src/obdh/pus/tm_handler.fin"
        status._variant = Status__Failure;
        #line 128 "src/obdh/pus/tm_handler.fin"
        status.Failure._0._variant = TMHandlerError__AppDataOverflow;

    }

    #line 132 "src/obdh/pus/tm_handler.fin"
    return status;

}

void tm_handler_build_packet_header(TMHandler * const tm_handler, const uint16_t tm_seq_counter) {
    
    #line 147 "src/obdh/pus/tm_handler.fin"
    tm_handler->packet_header.packet_id = ccsds_pus_tm_build_packet_id(0x32CU);

    #line 149 "src/obdh/pus/tm_handler.fin"
    tm_handler->packet_header.packet_seq_ctrl = tm_seq_counter & 0x3FFFU;

    #line 151 "src/obdh/pus/tm_handler.fin"
    tm_handler->packet_header.packet_length = (uint16_t)(size_t)(tm_handler->app_data_index - 7U);

    #line 153 "src/obdh/pus/tm_handler.fin"
    return;

}

void tm_handler_build_df_header(TMHandler * const tm_handler, const uint8_t tm_type, const uint8_t tm_subtype, const CUCTime current_obt) {
    
    #line 169 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.version = 0x20U;

    #line 170 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.type = tm_type;

    #line 171 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.subtype = tm_subtype;

    #line 172 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.msg_type_counter = 0U;

    #line 173 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.destinationID = 0x78U;

    #line 174 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.obt_secs = current_obt.seconds;

    #line 175 "src/obdh/pus/tm_handler.fin"
    tm_handler->df_header.obt_finetime = current_obt.finetime;

    #line 177 "src/obdh/pus/tm_handler.fin"
    return;

}

void close_tm(TMHandler * const tm_handler, const uint8_t type, const uint8_t subtype, const uint16_t tm_count, const CUCTime current_obt) {
    
    #line 195 "src/obdh/pus/tm_handler.fin"
    tm_handler_build_packet_header(tm_handler, tm_count);

    #line 196 "src/obdh/pus/tm_handler.fin"
    tm_handler_build_df_header(tm_handler, type, subtype, current_obt);

    #line 198 "src/obdh/pus/tm_handler.fin"
    ccsds_pus_tm_set_fields(&tm_handler->tm_descriptor.tm_bytes[0U], &tm_handler->packet_header, &tm_handler->df_header);

    #line 200 "src/obdh/pus/tm_handler.fin"
    tm_handler->tm_descriptor.tm_num_bytes = (size_t)tm_handler->packet_header.packet_length + 7U;

    #line 202 "src/obdh/pus/tm_handler.fin"
    return;

}

void startup_tm(TMHandler * const tm_handler) {
    
    #line 216 "src/obdh/pus/tm_handler.fin"
    tm_handler->tm_descriptor.tm_num_bytes = 256U;

    #line 217 "src/obdh/pus/tm_handler.fin"
    tm_handler->app_data_index = 19U;

    #line 219 "src/obdh/pus/tm_handler.fin"
    return;

}
