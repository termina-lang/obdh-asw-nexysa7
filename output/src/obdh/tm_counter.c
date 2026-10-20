
#include "obdh/tm_counter.h"

void CTMCounter__count_lost_tm(const termina__event_t * const termina__ev, void * const termina__this) {
    
    #line 56 "src/obdh/tm_counter.fin"
    CTMCounter * self = (CTMCounter *)termina__this;

    #line 56 "src/obdh/tm_counter.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 58 "src/obdh/tm_counter.fin"
    self->lost_tm = self->lost_tm + 1U;

    #line 60 "src/obdh/tm_counter.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 60 "src/obdh/tm_counter.fin"
    return;

}

void CTMCounter__get_next_tm_count(const termina__event_t * const termina__ev, void * const termina__this, uint16_t * const count) {
    
    #line 45 "src/obdh/tm_counter.fin"
    CTMCounter * self = (CTMCounter *)termina__this;

    #line 45 "src/obdh/tm_counter.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 47 "src/obdh/tm_counter.fin"
    *count = self->tm_count;

    #line 48 "src/obdh/tm_counter.fin"
    self->tm_count = (uint16_t)((self->tm_count + 1U) & 0xFFFFU) & 0x3FFFU;

    #line 50 "src/obdh/tm_counter.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 50 "src/obdh/tm_counter.fin"
    return;

}
