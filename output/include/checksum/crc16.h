#ifndef CHECKSUM__CRC16_H__
#define CHECKSUM__CRC16_H__

#include <termina.h>

#include "obdh/pus/tc_packet.h"

#include "option.h"

uint16_t crc16_update(const uint16_t crc_value, const uint8_t byte);

uint16_t cal_crc_16(const uint8_t data[256U], const size_t nbytes);

#endif
