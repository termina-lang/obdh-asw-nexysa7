#ifndef OBDH__PUS__SERVICES__SERVICE2__TYPES_H__
#define OBDH__PUS__SERVICES__SERVICE2__TYPES_H__

#include <termina.h>

#include "option.h"

extern const size_t num_params2;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint32_t dev_address;
} PS2TCRequest;

typedef enum {
    PUSService2Error__ErrorInAcceptance,
    PUSService2Error__AppDataOutOfRange,
    PUSService2Error__NumOfInstrNotValid,
    PUSService2Error__DeviceAddressNotValid,
    PUSService2Error__DeviceCommandExecError
} termina__enum__PUSService2Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService2Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService2Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint32_t _0;
} termina__enum__PUSService2Error__DeviceAddressNotValid_params_t;

typedef struct {
    uint32_t _0;
} termina__enum__PUSService2Error__DeviceCommandExecError_params_t;

typedef struct {
    termina__enum__PUSService2Error_t _variant;
    union {
        termina__enum__PUSService2Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService2Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService2Error__DeviceAddressNotValid_params_t DeviceAddressNotValid;
        termina__enum__PUSService2Error__DeviceCommandExecError_params_t DeviceCommandExecError;
    };
} PUSService2Error;

typedef struct {
    PUSService2Error _0;
} termina__enum__Status__PUSService2Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService2Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService2Error;

#endif
