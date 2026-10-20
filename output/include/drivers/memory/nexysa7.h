#ifndef DRIVERS__MEMORY__NEXYSA7_H__
#define DRIVERS__MEMORY__NEXYSA7_H__

#include <termina.h>

#include "checksum/crc16.h"
#include "drivers/memory.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    _Bool write_enabled[8U];
    volatile uint8_t (* ddr2)[16777216U];
} CNexysA7Memory;

void CNexysA7Memory__check_access(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const _Bool write, Status__MemAccessError * const result);

void CNexysA7Memory__checksum(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint16_t * const checksum);

void CNexysA7Memory__read(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint8_t dst[256U]);

void CNexysA7Memory__write(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const uint8_t src[256U]);

#endif
