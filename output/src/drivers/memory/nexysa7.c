
#include "drivers/memory/nexysa7.h"

void CNexysA7Memory__check_access(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const _Bool write, Status__MemAccessError * const result) {
    
    #line 19 "src/drivers/memory/nexysa7.fin"
    const CNexysA7Memory * self = (const CNexysA7Memory *)termina__this;

    #line 19 "src/drivers/memory/nexysa7.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 22 "src/drivers/memory/nexysa7.fin"
    if ((size_t)mem_id >= 8U || address >= 16777216U || length > (size_t)(16777216U - address) || length > 256U) {
        
        #line 27 "src/drivers/memory/nexysa7.fin"
        (*result)._variant = Status__Failure;
        #line 27 "src/drivers/memory/nexysa7.fin"
        (*result).Failure._0._variant = MemAccessError__InvalidAccess;

    } else
    #line 29 "src/drivers/memory/nexysa7.fin"
    if (write) {
        
        #line 31 "src/drivers/memory/nexysa7.fin"
        if (self->write_enabled[termina__check__array_index(8U, (size_t)mem_id)]) {
            
            #line 32 "src/drivers/memory/nexysa7.fin"
            (*result)._variant = Status__Success;

        } else
        {
            
            #line 34 "src/drivers/memory/nexysa7.fin"
            (*result)._variant = Status__Failure;
            #line 34 "src/drivers/memory/nexysa7.fin"
            (*result).Failure._0._variant = MemAccessError__ReadOnly;

        }

    } else
    {
        
        #line 39 "src/drivers/memory/nexysa7.fin"
        (*result)._variant = Status__Success;

    }

    #line 43 "src/drivers/memory/nexysa7.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 43 "src/drivers/memory/nexysa7.fin"
    return;

}

void CNexysA7Memory__checksum(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint16_t * const checksum) {
    
    #line 66 "src/drivers/memory/nexysa7.fin"
    const CNexysA7Memory * self = (const CNexysA7Memory *)termina__this;

    #line 66 "src/drivers/memory/nexysa7.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 69 "src/drivers/memory/nexysa7.fin"
    uint16_t crc = 0xFFFFU;

    #line 71 "src/drivers/memory/nexysa7.fin"
    for (size_t i = 0U; i < 256U && i < length; i = i + 1U) {
        
        #line 72 "src/drivers/memory/nexysa7.fin"
        crc = crc16_update(crc, self->ddr2[termina__check__array_index(8U, (size_t)mem_id)][termina__check__array_index(16777216U, address + i)]);

    }

    #line 75 "src/drivers/memory/nexysa7.fin"
    *checksum = crc;

    #line 77 "src/drivers/memory/nexysa7.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 77 "src/drivers/memory/nexysa7.fin"
    return;

}

void CNexysA7Memory__read(const termina__event_t * const termina__ev, const void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, uint8_t dst[256U]) {
    
    #line 46 "src/drivers/memory/nexysa7.fin"
    const CNexysA7Memory * self = (const CNexysA7Memory *)termina__this;

    #line 46 "src/drivers/memory/nexysa7.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 49 "src/drivers/memory/nexysa7.fin"
    for (size_t i = 0U; i < 256U && i < length; i = i + 1U) {
        
        #line 50 "src/drivers/memory/nexysa7.fin"
        dst[i] = self->ddr2[termina__check__array_index(8U, (size_t)mem_id)][termina__check__array_index(16777216U, address + i)];

    }

    #line 53 "src/drivers/memory/nexysa7.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 53 "src/drivers/memory/nexysa7.fin"
    return;

}

void CNexysA7Memory__write(const termina__event_t * const termina__ev, void * const termina__this, const uint8_t mem_id, const size_t address, const size_t length, const uint8_t src[256U]) {
    
    #line 56 "src/drivers/memory/nexysa7.fin"
    CNexysA7Memory * self = (CNexysA7Memory *)termina__this;

    #line 56 "src/drivers/memory/nexysa7.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 59 "src/drivers/memory/nexysa7.fin"
    for (size_t i = 0U; i < 256U && i < length; i = i + 1U) {
        
        #line 60 "src/drivers/memory/nexysa7.fin"
        self->ddr2[termina__check__array_index(8U, (size_t)mem_id)][termina__check__array_index(16777216U, address + i)] = src[i];

    }

    #line 63 "src/drivers/memory/nexysa7.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 63 "src/drivers/memory/nexysa7.fin"
    return;

}
