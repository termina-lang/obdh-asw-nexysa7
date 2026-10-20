#ifndef OBDH__PUS__TC_PACKET_H__
#define OBDH__PUS__TC_PACKET_H__

#include <termina.h>

#include "encoding/binary.h"

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint16_t packet_length;
} CCSDSPUSTCPacketHeader;

typedef struct {
    uint8_t flag_ver_ack;
    uint8_t type;
    uint8_t subtype;
    uint16_t sourceID;
} CCSDSPUSTCDFHeader;

typedef struct {
    uint8_t tc_bytes[256U];
    size_t tc_num_bytes;
} TCDescriptor;

uint16_t get_packet_id(const uint8_t tc_bytes[256U]);

uint16_t get_APID(const uint8_t tc_bytes[256U]);

uint16_t get_seq_flags(const uint16_t packet_seq_ctrl);

uint16_t get_seq_count(const uint16_t packet_seq_ctrl);

uint16_t get_packet_length(const uint8_t tc_bytes[256U]);

uint16_t get_packet_seq_ctrl(const uint8_t tc_bytes[256U]);

uint8_t get_ack(const uint8_t flag_ver_ack);

uint8_t get_type(const uint8_t tc_bytes[256U]);

uint8_t get_subtype(const uint8_t tc_bytes[256U]);

uint16_t get_source_id(const uint8_t tc_bytes[256U]);

void tc_get_fields(const uint8_t tc_bytes[256U], CCSDSPUSTCPacketHeader * const p_tc_packet_header, CCSDSPUSTCDFHeader * const p_tc_df_header, uint16_t * const p_tc_packet_err_ctrl);

#endif
