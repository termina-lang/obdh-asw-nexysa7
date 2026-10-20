#ifndef OBDH__PUS__SERVICES__SERVICE20__TYPES_H__
#define OBDH__PUS__SERVICES__SERVICE20__TYPES_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/system_data_pool.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    uint8_t PID_value_u8;
    uint32_t PID_value_u32;
} TC20_3Data;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint16_t PID;
    TC20_3Data tc_20_3_data;
} PS20TCRequest;

typedef enum {
    PUSService20Error__ErrorInAcceptance,
    PUSService20Error__AppDataOutOfRange,
    PUSService20Error__NumOfInstrNotValid,
    PUSService20Error__PIDNotValid,
    PUSService20Error__PIDReadOnlyViaTC
} termina__enum__PUSService20Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService20Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService20Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService20Error__PIDNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService20Error__PIDReadOnlyViaTC_params_t;

typedef struct {
    termina__enum__PUSService20Error_t _variant;
    union {
        termina__enum__PUSService20Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService20Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService20Error__PIDNotValid_params_t PIDNotValid;
        termina__enum__PUSService20Error__PIDReadOnlyViaTC_params_t PIDReadOnlyViaTC;
    };
} PUSService20Error;

typedef struct {
    PUSService20Error _0;
} termina__enum__Status__PUSService20Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService20Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService20Error;

#endif
