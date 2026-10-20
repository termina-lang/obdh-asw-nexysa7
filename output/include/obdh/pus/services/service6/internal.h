#ifndef OBDH__PUS__SERVICES__SERVICE6__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE6__INTERNAL_H__

#include <termina.h>

#include "drivers/memory.h"
#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/tm_handler.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t mem_id;
    uint8_t N;
    uint32_t address;
    uint16_t length;
    uint8_t data[256U];
} PS6TCRequest;

typedef enum {
    PUSService6Error__ErrorInAcceptance,
    PUSService6Error__AppDataOutOfRange,
    PUSService6Error__AppDataOverflow,
    PUSService6Error__NumOfInstrNotValid,
    PUSService6Error__MemAddressNotValid,
    PUSService6Error__MemIDReadOnly
} termina__enum__PUSService6Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService6Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService6Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint8_t _0;
    uint32_t _1;
} termina__enum__PUSService6Error__MemAddressNotValid_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService6Error__MemIDReadOnly_params_t;

typedef struct {
    termina__enum__PUSService6Error_t _variant;
    union {
        termina__enum__PUSService6Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService6Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService6Error__MemAddressNotValid_params_t MemAddressNotValid;
        termina__enum__PUSService6Error__MemIDReadOnly_params_t MemIDReadOnly;
    };
} PUSService6Error;

typedef struct {
    PUSService6Error _0;
} termina__enum__Status__PUSService6Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService6Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService6Error;

Status__TMHandlerError build_tm_6_6(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const PS6TCRequest * const mem_data);

Status__TMHandlerError build_tm_6_10(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const PS6TCRequest * const mem_data, const uint16_t checksum);

#endif
