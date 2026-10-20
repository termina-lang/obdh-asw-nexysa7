#ifndef OBDH__PUS__SERVICES__SERVICE3__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE3__INTERNAL_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service5.h"
#include "obdh/system_data_pool.h"
#include "random/lcg.h"

#include "option.h"

typedef struct {
    _Bool found;
    size_t index;
} IndexFound;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint16_t SID;
    uint8_t collection_interval;
} PS3TCRequest;

typedef enum {
    PUSService3Error__ErrorInAcceptance,
    PUSService3Error__AppDataOutOfRange,
    PUSService3Error__NumOfInstrNotValid,
    PUSService3Error__SIDNotValid
} termina__enum__PUSService3Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService3Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService3Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService3Error__SIDNotValid_params_t;

typedef struct {
    termina__enum__PUSService3Error_t _variant;
    union {
        termina__enum__PUSService3Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService3Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService3Error__SIDNotValid_params_t SIDNotValid;
    };
} PUSService3Error;

typedef struct {
    PUSService3Error _0;
} termina__enum__Status__PUSService3Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService3Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService3Error;

typedef struct {
    _Bool enabled;
    uint16_t SID;
    uint8_t interval;
    uint8_t interval_control;
    uint8_t num_params;
    uint16_t params_def[16U];
} HKConfiguration;

#endif
