
#include "obdh/pus/tc_packet.h"

uint16_t get_packet_id(const uint8_t tc_bytes[256U]) {
    
    #line 51 "src/obdh/pus/tc_packet.fin"
    uint16_t packet_id = deserialize_uint16(&tc_bytes[0U]);

    #line 52 "src/obdh/pus/tc_packet.fin"
    return packet_id;

}

uint16_t get_APID(const uint8_t tc_bytes[256U]) {
    
    #line 65 "src/obdh/pus/tc_packet.fin"
    uint16_t packet_id = get_packet_id(tc_bytes);

    #line 67 "src/obdh/pus/tc_packet.fin"
    return packet_id & 0x7FFU;

}

uint16_t get_seq_flags(const uint16_t packet_seq_ctrl) {
    
    #line 79 "src/obdh/pus/tc_packet.fin"
    return packet_seq_ctrl >> 14U;

}

uint16_t get_seq_count(const uint16_t packet_seq_ctrl) {
    
    #line 91 "src/obdh/pus/tc_packet.fin"
    return packet_seq_ctrl & 0x3FFFU;

}

uint16_t get_packet_length(const uint8_t tc_bytes[256U]) {
    
    #line 102 "src/obdh/pus/tc_packet.fin"
    return deserialize_uint16(&tc_bytes[4U]);

}

uint16_t get_packet_seq_ctrl(const uint8_t tc_bytes[256U]) {
    
    #line 114 "src/obdh/pus/tc_packet.fin"
    const uint16_t crc_offset = get_packet_length(tc_bytes) + 5U;

    #line 115 "src/obdh/pus/tc_packet.fin"
    uint16_t packet_error_ctrl = deserialize_uint16(&tc_bytes[termina__check__array_slice(256U, 2U, (size_t)crc_offset, (size_t)(uint16_t)((crc_offset + 2U) & 0xFFFFU))]);

    #line 117 "src/obdh/pus/tc_packet.fin"
    return packet_error_ctrl;

}

uint8_t get_ack(const uint8_t flag_ver_ack) {
    
    #line 128 "src/obdh/pus/tc_packet.fin"
    return flag_ver_ack & 0xFU;

}

uint8_t get_type(const uint8_t tc_bytes[256U]) {
    
    #line 139 "src/obdh/pus/tc_packet.fin"
    uint8_t type = tc_bytes[7U];

    #line 140 "src/obdh/pus/tc_packet.fin"
    return type;

}

uint8_t get_subtype(const uint8_t tc_bytes[256U]) {
    
    #line 151 "src/obdh/pus/tc_packet.fin"
    uint8_t subtype = tc_bytes[8U];

    #line 152 "src/obdh/pus/tc_packet.fin"
    return subtype;

}

uint16_t get_source_id(const uint8_t tc_bytes[256U]) {
    
    #line 164 "src/obdh/pus/tc_packet.fin"
    uint16_t sourceID = deserialize_uint16(&tc_bytes[9U]);

    #line 165 "src/obdh/pus/tc_packet.fin"
    return sourceID;

}

void tc_get_fields(const uint8_t tc_bytes[256U], CCSDSPUSTCPacketHeader * const p_tc_packet_header, CCSDSPUSTCDFHeader * const p_tc_df_header, uint16_t * const p_tc_packet_err_ctrl) {
    
    #line 183 "src/obdh/pus/tc_packet.fin"
    p_tc_packet_header->packet_id = deserialize_uint16(&tc_bytes[0U]);

    #line 186 "src/obdh/pus/tc_packet.fin"
    p_tc_packet_header->packet_seq_ctrl = deserialize_uint16(&tc_bytes[2U]);

    #line 189 "src/obdh/pus/tc_packet.fin"
    p_tc_packet_header->packet_length = deserialize_uint16(&tc_bytes[4U]);

    #line 192 "src/obdh/pus/tc_packet.fin"
    p_tc_df_header->flag_ver_ack = tc_bytes[6U];

    #line 195 "src/obdh/pus/tc_packet.fin"
    p_tc_df_header->type = tc_bytes[7U];

    #line 196 "src/obdh/pus/tc_packet.fin"
    p_tc_df_header->subtype = tc_bytes[8U];

    #line 197 "src/obdh/pus/tc_packet.fin"
    p_tc_df_header->sourceID = deserialize_uint16(&tc_bytes[9U]);

    #line 200 "src/obdh/pus/tc_packet.fin"
    uint8_t packet_error_ctrl[2U] = { 0U, 0U };

    #line 201 "src/obdh/pus/tc_packet.fin"
    packet_error_ctrl[0U] = tc_bytes[termina__check__array_index(256U, (size_t)(uint16_t)(((*p_tc_packet_header).packet_length + 5U) & 0xFFFFU))];

    #line 202 "src/obdh/pus/tc_packet.fin"
    packet_error_ctrl[1U] = tc_bytes[termina__check__array_index(256U, (size_t)(uint16_t)(((*p_tc_packet_header).packet_length + 6U) & 0xFFFFU))];

    #line 204 "src/obdh/pus/tc_packet.fin"
    *p_tc_packet_err_ctrl = deserialize_uint16(packet_error_ctrl);

    #line 206 "src/obdh/pus/tc_packet.fin"
    return;

}
