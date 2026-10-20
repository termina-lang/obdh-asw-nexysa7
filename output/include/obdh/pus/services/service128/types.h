#ifndef OBDH__PUS__SERVICES__SERVICE128__TYPES_H__
#define OBDH__PUS__SERVICES__SERVICE128__TYPES_H__

#include <termina.h>

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    _Bool reboot_requested;
} PS128TCRequest;

typedef enum {
    PUSService128Error__ErrorInAcceptance
} termina__enum__PUSService128Error_t;

typedef struct {
    termina__enum__PUSService128Error_t _variant;
} PUSService128Error;

typedef struct {
    PUSService128Error _0;
} termina__enum__Status__PUSService128Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService128Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService128Error;

#endif
