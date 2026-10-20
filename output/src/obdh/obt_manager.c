
#include "obdh/obt_manager.h"

void COBTManager__get_current_obt(const termina__event_t * const termina__ev, void * const termina__this, CUCTime * const current_obt) {
    
    #line 43 "src/obdh/obt_manager.fin"
    COBTManager * self = (COBTManager *)termina__this;

    #line 43 "src/obdh/obt_manager.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 45 "src/obdh/obt_manager.fin"
    TimeVal time_val_from_power_on = { .tv_sec = 0U, .tv_usec = 0U };

    #line 49 "src/obdh/obt_manager.fin"
    self->system_api.clock_get_uptime(termina__ev, &time_val_from_power_on);

    #line 50 "src/obdh/obt_manager.fin"
    TimeVal interval = substract_TimeVal(time_val_from_power_on, self->ref_time_val_from_power_on);

    #line 52 "src/obdh/obt_manager.fin"
    uint32_t fine_time_increment = (uint32_t)self->ref_obt.finetime;

    #line 53 "src/obdh/obt_manager.fin"
    fine_time_increment = fine_time_increment + (uint32_t)((uint32_t)(interval.tv_usec * 1000U) / 15259U);

    #line 55 "src/obdh/obt_manager.fin"
    current_obt->seconds = (uint32_t)(self->ref_obt.seconds + interval.tv_sec) + (uint32_t)(fine_time_increment >> 16U);

    #line 56 "src/obdh/obt_manager.fin"
    current_obt->finetime = (uint16_t)(uint32_t)(fine_time_increment & 0xFFFFU);

    #line 58 "src/obdh/obt_manager.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 58 "src/obdh/obt_manager.fin"
    return;

}

void COBTManager__set_obt(const termina__event_t * const termina__ev, void * const termina__this, const CUCTime next_obt) {
    
    #line 25 "src/obdh/obt_manager.fin"
    COBTManager * self = (COBTManager *)termina__this;

    #line 25 "src/obdh/obt_manager.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 27 "src/obdh/obt_manager.fin"
    self->ref_obt = next_obt;

    #line 28 "src/obdh/obt_manager.fin"
    self->system_api.clock_get_uptime(termina__ev, &self->ref_time_val_from_power_on);

    #line 30 "src/obdh/obt_manager.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 30 "src/obdh/obt_manager.fin"
    return;

}
