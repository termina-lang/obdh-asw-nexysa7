#ifndef OBDH__PUS__SERVICES__SERVICE9__TYPES_H__
#define OBDH__PUS__SERVICES__SERVICE9__TYPES_H__

#include <termina.h>

#include "obdh/obt_manager.h"

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    CUCTime next_OBT;
} PS9TCRequest;

typedef enum {
    PUSService9Error__ErrorInAcceptance,
    PUSService9Error__AppDataOutOfRange
} termina__enum__PUSService9Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService9Error__AppDataOutOfRange_params_t;

typedef struct {
    termina__enum__PUSService9Error_t _variant;
    termina__enum__PUSService9Error__AppDataOutOfRange_params_t AppDataOutOfRange;
} PUSService9Error;

typedef struct {
    PUSService9Error _0;
} termina__enum__Status__PUSService9Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService9Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService9Error;

#endif
