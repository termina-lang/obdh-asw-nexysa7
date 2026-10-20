#ifndef OBDH__PUS__SERVICES__SERVICE5__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE5__INTERNAL_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/tmtc/tm_channel.h"

#include "option.h"

typedef enum {
    Ev_IDType__Informative,
    Ev_IDType__LowSeverityAnomaly,
    Ev_IDType__MediumSeverityAnomaly,
    Ev_IDType__HighSeverityAnomaly,
    Ev_IDType__Ev_IDNotValid
} termina__enum__Ev_IDType_t;

typedef struct {
    termina__enum__Ev_IDType_t _variant;
} Ev_IDType;

typedef enum {
    PUSService5Error__ErrorInAcceptance,
    PUSService5Error__AppDataOutOfRange,
    PUSService5Error__NumOfInstrNotValid,
    PUSService5Error__EvIDNotValid
} termina__enum__PUSService5Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService5Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService5Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService5Error__EvIDNotValid_params_t;

typedef struct {
    termina__enum__PUSService5Error_t _variant;
    union {
        termina__enum__PUSService5Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService5Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService5Error__EvIDNotValid_params_t EvIDNotValid;
    };
} PUSService5Error;

typedef struct {
    PUSService5Error _0;
} termina__enum__Status__PUSService5Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService5Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService5Error;

extern const uint16_t informative_Ev_IDs;

extern const uint16_t low_severity_anomaly_Ev_IDs;

extern const uint16_t medium_severity_anomaly_Ev_IDs;

extern const uint16_t high_severity_anomaly_Ev_IDs;

extern const uint16_t Ev_IDs_per_type[5U];

extern const uint16_t offset_mask;

extern const uint16_t EvID_build_tm_error;

typedef struct {
    uint16_t PID;
    uint32_t PID_value;
    uint32_t PID_limit;
} ParamOutOfLimitInfo;

typedef struct {
    uint16_t PID;
    uint32_t PID_value;
    uint32_t PID_mask;
    uint32_t PID_expected_value;
} ParamFaultValueInfo;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint16_t EvID;
} PS5TCRequest;

Ev_IDType get_Ev_ID_type(const uint16_t Ev_ID);

_Bool is_Ev_ID_valid(const uint16_t evID);

size_t get_Ev_ID_enable_config_index(const uint16_t Ev_ID);

uint8_t get_Ev_ID_enable_config_offset(const uint16_t Ev_ID);

Status__TMHandlerError build_tm_5_x_param_out_of_limit(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const ParamOutOfLimitInfo fault_info, const uint16_t ev_ID, const CUCTime current_obt);

Status__TMHandlerError build_tm_5_x_param_check_value_fail(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const ParamFaultValueInfo fault_info, const uint16_t ev_ID, const CUCTime current_obt);

#endif
