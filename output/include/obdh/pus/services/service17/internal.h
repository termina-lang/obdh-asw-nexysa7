#ifndef OBDH__PUS__SERVICES__SERVICE17__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE17__INTERNAL_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
} PS17TCRequest;

typedef enum {
    PUSService17Error__ErrorInAcceptance
} termina__enum__PUSService17Error_t;

typedef struct {
    termina__enum__PUSService17Error_t _variant;
} PUSService17Error;

typedef struct {
    PUSService17Error _0;
} termina__enum__Status__PUSService17Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService17Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService17Error;

void build_tm_17_2(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt);

#endif
