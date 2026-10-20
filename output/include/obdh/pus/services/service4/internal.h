#ifndef OBDH__PUS__SERVICES__SERVICE4__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE4__INTERNAL_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    uint32_t min;
    CUCTime min_obt;
    uint32_t max;
    CUCTime max_obt;
    uint32_t mean_value;
    uint32_t samples;
} StatsDef;

typedef struct {
    _Bool defined[4U];
    uint16_t PID[4U];
    CUCTime start_time[4U];
} StatsConfig;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint16_t PID;
    size_t valid_index;
} PS4TCRequest;

typedef enum {
    PUSService4Error__ErrorInAcceptance,
    PUSService4Error__AppDataOutOfRange,
    PUSService4Error__NumOfInstrNotValid,
    PUSService4Error__PIDNotValid,
    PUSService4Error__PIDStatsUndefined,
    PUSService4Error__NotFreeStatsConfig
} termina__enum__PUSService4Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService4Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService4Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService4Error__PIDNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService4Error__PIDStatsUndefined_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService4Error__NotFreeStatsConfig_params_t;

typedef struct {
    termina__enum__PUSService4Error_t _variant;
    union {
        termina__enum__PUSService4Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService4Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService4Error__PIDNotValid_params_t PIDNotValid;
        termina__enum__PUSService4Error__PIDStatsUndefined_params_t PIDStatsUndefined;
        termina__enum__PUSService4Error__NotFreeStatsConfig_params_t NotFreeStatsConfig;
    };
} PUSService4Error;

typedef struct {
    PUSService4Error _0;
} termina__enum__Status__PUSService4Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService4Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService4Error;

typedef struct {
    size_t index;
    Status__PUSService4Error status;
} IndexStatus;

Status__TMHandlerError build_tm_4_2(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const size_t stats_index, const uint8_t N, const StatsConfig * const stats_config_table, const StatsDef param_stats[4U], const CUCTime current_obt);

#endif
