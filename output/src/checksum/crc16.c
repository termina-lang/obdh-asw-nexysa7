
#include "checksum/crc16.h"

uint16_t crc16_update(const uint16_t crc_value, const uint8_t byte) {
    
    #line 18 "src/checksum/crc16.fin"
    uint16_t crc = crc_value ^ (uint16_t)((uint16_t)byte << 8U & 0xFFFFU);

    #line 20 "src/checksum/crc16.fin"
    for (uint16_t j = 0U; j < 8U; j = j + 1U) {
        
        #line 22 "src/checksum/crc16.fin"
        if ((uint16_t)(crc & 0x8000U) != 0U) {
            
            #line 23 "src/checksum/crc16.fin"
            crc = (uint16_t)(crc << 1U & 0xFFFFU) ^ 0x1021U;

        } else
        {
            
            #line 25 "src/checksum/crc16.fin"
            crc = crc << 1U;

        }

    }

    #line 29 "src/checksum/crc16.fin"
    return crc;

}

uint16_t cal_crc_16(const uint8_t data[256U], const size_t nbytes) {
    
    #line 49 "src/checksum/crc16.fin"
    uint16_t crc_value = 0xFFFFU;

    #line 51 "src/checksum/crc16.fin"
    for (size_t i = 0U; i < 256U && i < nbytes; i = i + 1U) {
        
        #line 53 "src/checksum/crc16.fin"
        crc_value = crc16_update(crc_value, data[i]);

    }

    #line 57 "src/checksum/crc16.fin"
    return crc_value;

}
