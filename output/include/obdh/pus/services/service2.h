#ifndef OBDH__PUS__SERVICES__SERVICE2_H__
#define OBDH__PUS__SERVICES__SERVICE2_H__

#include <termina.h>

#include "drivers/gpio.h"
#include "encoding/binary.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service12.h"
#include "obdh/pus/services/service2/types.h"
#include "obdh/pus/tc_packet.h"
#include "obdh/pus/tm_packet.h"

#include "option.h"

typedef struct {
    termina__resource_lock_type_t _lock_type;
    Option__GPIOPinId device_pins[16U];
    struct {
        void * _that;
        void (* write_pin)(const termina__event_t * const termina__ev, void * const termina__this, const GPIOPinId pin, const GPIOPinState state);
    } gpio;
    struct {
        void * _that;
        void (* notify_tm_1_3)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* notify_tm_1_7)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack);
        void (* send_tm_1_4_device_address_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t device_address);
        void (* send_tm_1_4_error_in_acceptance)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl);
        void (* send_tm_1_4_num_of_instr_not_valid)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N);
        void (* send_tm_1_4_short_pack_length)(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes);
    } pus_service_1;
} CPUSService2;

void CPUSService2__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler);

#endif
