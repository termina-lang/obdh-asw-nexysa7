#ifndef OBDH__PUS__TM_PACKET_H__
#define OBDH__PUS__TM_PACKET_H__

#include <termina.h>

#include "encoding/binary.h"

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint16_t packet_length;
} CCSDSPUSTMPacketHeader;

typedef struct {
    uint8_t version;
    uint8_t type;
    uint8_t subtype;
    uint16_t msg_type_counter;
    uint16_t destinationID;
    uint32_t obt_secs;
    uint16_t obt_finetime;
} CCSDSPUSTMDFHeader;

typedef struct {
    uint8_t tm_bytes[256U];
    size_t tm_num_bytes;
} TMDescriptor;

uint16_t ccsds_pus_tm_build_packet_id(const uint16_t apid);

uint16_t ccsds_pus_tm_build_packet_seq_ctrl(const uint16_t sequence_flags, const uint16_t tm_count);

uint32_t ccsds_pus_tm_build_df_header(const uint8_t service_type, const uint8_t service_subtype, const uint8_t destination_id);

uint8_t ccsds_pus_tm_build_df_header_version(const uint8_t version);

void ccsds_pus_tm_set_fields(uint8_t tm_bytes[19U], const CCSDSPUSTMPacketHeader * const p_tm_packet_header, const CCSDSPUSTMDFHeader * const p_tm_df_header);

#endif
