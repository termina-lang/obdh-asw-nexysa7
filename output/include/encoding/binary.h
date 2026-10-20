#ifndef ENCODING__BINARY_H__
#define ENCODING__BINARY_H__

#include <termina.h>

#include "option.h"

uint16_t deserialize_uint16(const uint8_t data_bytes[2U]);

uint32_t deserialize_uint32(const uint8_t data_bytes[4U]);

void serialize_uint16(const uint16_t aux, uint8_t data_bytes[2U]);

void serialize_uint32(const uint32_t aux, uint8_t data_bytes[4U]);

#endif
