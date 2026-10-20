#ifndef OBDH__OBT_MANAGER_H__
#define OBDH__OBT_MANAGER_H__

#include <termina.h>

#include "obdh/pus/time.h"
#include "time/timeval.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void (* clock_get_uptime)(const termina__event_t * const termina__ev, TimeVal * const current_time);
    } system_api;
    TimeVal ref_time_val_from_power_on;
    CUCTime ref_obt;
} COBTManager;

void COBTManager__get_current_obt(const termina__event_t * const termina__ev, void * const termina__this, CUCTime * const current_obt);

void COBTManager__set_obt(const termina__event_t * const termina__ev, void * const termina__this, const CUCTime next_obt);

#endif
