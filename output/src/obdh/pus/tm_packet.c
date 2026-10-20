
#include "obdh/pus/tm_packet.h"

uint16_t ccsds_pus_tm_build_packet_id(const uint16_t apid) {
    
    #line 46 "src/obdh/pus/tm_packet.fin"
    return 18432U | (uint16_t)(apid & 0x7FFU);

}

uint16_t ccsds_pus_tm_build_packet_seq_ctrl(const uint16_t sequence_flags, const uint16_t tm_count) {
    
    #line 60 "src/obdh/pus/tm_packet.fin"
    return (uint16_t)((uint16_t)(sequence_flags & 0x3U) << 14U & 0xFFFFU) | (uint16_t)(tm_count & 0x3FFFU);

}

uint32_t ccsds_pus_tm_build_df_header(const uint8_t service_type, const uint8_t service_subtype, const uint8_t destination_id) {
    
    #line 74 "src/obdh/pus/tm_packet.fin"
    return (uint32_t)((uint32_t)(0x10000000U | (uint32_t)((uint32_t)service_type << 16U)) | (uint32_t)((uint32_t)service_subtype << 8U)) | (uint32_t)destination_id;

}

uint8_t ccsds_pus_tm_build_df_header_version(const uint8_t version) {
    
    #line 87 "src/obdh/pus/tm_packet.fin"
    return (uint8_t)(version & 0xFU) << 4U;

}

void ccsds_pus_tm_set_fields(uint8_t tm_bytes[19U], const CCSDSPUSTMPacketHeader * const p_tm_packet_header, const CCSDSPUSTMDFHeader * const p_tm_df_header) {
    
    #line 103 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_packet_header->packet_id, &tm_bytes[0U]);

    #line 106 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_packet_header->packet_seq_ctrl, &tm_bytes[2U]);

    #line 109 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_packet_header->packet_length, &tm_bytes[4U]);

    #line 112 "src/obdh/pus/tm_packet.fin"
    tm_bytes[6U] = p_tm_df_header->version;

    #line 115 "src/obdh/pus/tm_packet.fin"
    tm_bytes[7U] = p_tm_df_header->type;

    #line 118 "src/obdh/pus/tm_packet.fin"
    tm_bytes[8U] = p_tm_df_header->subtype;

    #line 121 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_df_header->msg_type_counter, &tm_bytes[9U]);

    #line 124 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_df_header->destinationID, &tm_bytes[11U]);

    #line 127 "src/obdh/pus/tm_packet.fin"
    serialize_uint32(p_tm_df_header->obt_secs, &tm_bytes[13U]);

    #line 130 "src/obdh/pus/tm_packet.fin"
    serialize_uint16(p_tm_df_header->obt_finetime, &tm_bytes[17U]);

    #line 132 "src/obdh/pus/tm_packet.fin"
    return;

}
