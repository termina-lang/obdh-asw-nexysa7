#ifndef OBDH__TM_COUNTER_H__
#define OBDH__TM_COUNTER_H__

#include <termina.h>

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    uint32_t lost_tm;
    uint16_t tm_count;
} CTMCounter;

void CTMCounter__count_lost_tm(const termina__event_t * const termina__ev, void * const termina__this);

void CTMCounter__get_next_tm_count(const termina__event_t * const termina__ev, void * const termina__this, uint16_t * const count);

#endif
