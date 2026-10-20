
#include "encoding/binary.h"

uint16_t deserialize_uint16(const uint8_t data_bytes[2U]) {
    
    #line 14 "src/encoding/binary.fin"
    uint16_t aux = (uint16_t)data_bytes[0U];

    #line 15 "src/encoding/binary.fin"
    aux = aux << 8U;

    #line 16 "src/encoding/binary.fin"
    aux = aux | (uint16_t)data_bytes[1U];

    #line 18 "src/encoding/binary.fin"
    return aux;

}

uint32_t deserialize_uint32(const uint8_t data_bytes[4U]) {
    
    #line 34 "src/encoding/binary.fin"
    uint32_t aux = (uint32_t)data_bytes[0U];

    #line 35 "src/encoding/binary.fin"
    aux = aux << 8U;

    #line 36 "src/encoding/binary.fin"
    aux = aux | (uint32_t)data_bytes[1U];

    #line 37 "src/encoding/binary.fin"
    aux = aux << 8U;

    #line 38 "src/encoding/binary.fin"
    aux = aux | (uint32_t)data_bytes[2U];

    #line 39 "src/encoding/binary.fin"
    aux = aux << 8U;

    #line 40 "src/encoding/binary.fin"
    aux = aux | (uint32_t)data_bytes[3U];

    #line 42 "src/encoding/binary.fin"
    return aux;

}

void serialize_uint16(const uint16_t aux, uint8_t data_bytes[2U]) {
    
    #line 56 "src/encoding/binary.fin"
    data_bytes[0U] = (uint8_t)(uint16_t)((uint16_t)(aux & 0xFF00U) >> 8U);

    #line 57 "src/encoding/binary.fin"
    data_bytes[1U] = (uint8_t)(uint16_t)(aux & 0xFFU);

    #line 59 "src/encoding/binary.fin"
    return;

}

void serialize_uint32(const uint32_t aux, uint8_t data_bytes[4U]) {
    
    #line 73 "src/encoding/binary.fin"
    data_bytes[0U] = (uint8_t)(uint32_t)((uint32_t)(aux & 0xFF000000U) >> 24U);

    #line 74 "src/encoding/binary.fin"
    data_bytes[1U] = (uint8_t)(uint32_t)((uint32_t)(aux & 0xFF0000U) >> 16U);

    #line 75 "src/encoding/binary.fin"
    data_bytes[2U] = (uint8_t)(uint32_t)((uint32_t)(aux & 0xFF00U) >> 8U);

    #line 76 "src/encoding/binary.fin"
    data_bytes[3U] = (uint8_t)(uint32_t)(aux & 0xFFU);

    #line 78 "src/encoding/binary.fin"
    return;

}
