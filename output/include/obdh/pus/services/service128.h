#ifndef OBDH__PUS__SERVICES__SERVICE128_H__
#define OBDH__PUS__SERVICES__SERVICE128_H__

#include <termina.h>

#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service128/types.h"
#include "obdh/pus/tc_handler.h"

#include "option.h"

void exec128_1TC(PS128TCRequest * const tc_request);

typedef struct {
    termina__resource_lock_type_t _lock_type;
    struct {
        void * _that;
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
    } pus_service_1;
} CPUSService128;

void CPUSService128__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler, _Bool * const reboot_requested);

#endif
