#ifndef OBDH__PUS__SERVICES__SERVICE12__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE12__INTERNAL_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service5.h"

#include "option.h"

typedef enum {
    MonitorCheckType__ExpectedValue,
    MonitorCheckType__Limits,
    MonitorCheckType__Delta,
    MonitorCheckType__Free
} termina__enum__MonitorCheckType_t;

typedef struct {
    termina__enum__MonitorCheckType_t _variant;
} MonitorCheckType;

typedef struct {
    uint32_t mask_value;
    uint32_t expected_value;
    uint16_t EvID;
} ParamValueCheckDefinition;

typedef struct {
    uint32_t low_limit;
    uint16_t low_limit_evID;
    uint32_t high_limit;
    uint16_t high_limit_evID;
} ParamLimitCheckDefinition;

typedef struct {
    uint16_t low_delta_threshold;
    uint16_t low_delta_EvID;
    uint16_t high_delta_threshold;
    uint16_t high_delta_EvID;
    uint8_t consecutive_delta_values;
} ParamDeltaCheckDefinition;

typedef enum {
    MonitorDefinition__ParamValueCheck,
    MonitorDefinition__ParamLimitCheck,
    MonitorDefinition__ParamDeltaCheck,
    MonitorDefinition__Unselected
} termina__enum__MonitorDefinition_t;

typedef struct {
    ParamValueCheckDefinition _0;
} termina__enum__MonitorDefinition__ParamValueCheck_params_t;

typedef struct {
    ParamLimitCheckDefinition _0;
} termina__enum__MonitorDefinition__ParamLimitCheck_params_t;

typedef struct {
    ParamDeltaCheckDefinition _0;
} termina__enum__MonitorDefinition__ParamDeltaCheck_params_t;

typedef struct {
    termina__enum__MonitorDefinition_t _variant;
    union {
        termina__enum__MonitorDefinition__ParamValueCheck_params_t ParamValueCheck;
        termina__enum__MonitorDefinition__ParamLimitCheck_params_t ParamLimitCheck;
        termina__enum__MonitorDefinition__ParamDeltaCheck_params_t ParamDeltaCheck;
    };
} MonitorDefinition;

typedef enum {
    CheckValueResult__MonitorValueUnexpected,
    CheckValueResult__MonitorValueExpected
} termina__enum__CheckValueResult_t;

typedef struct {
    termina__enum__CheckValueResult_t _variant;
} CheckValueResult;

typedef struct {
    CheckValueResult _0;
} termina__enum__Option__CheckValueResult__Some_params_t;

typedef struct {
    termina__enum__Option__CheckValueResult__Some_params_t Some;
    termina__enum__Option_t _variant;
} Option__CheckValueResult;

typedef enum {
    CheckLimitsResult__MonitorAboveHighLimit,
    CheckLimitsResult__MonitorBelowLowLimit,
    CheckLimitsResult__MonitorWithinLimits
} termina__enum__CheckLimitsResult_t;

typedef struct {
    termina__enum__CheckLimitsResult_t _variant;
} CheckLimitsResult;

typedef struct {
    CheckLimitsResult _0;
} termina__enum__Option__CheckLimitsResult__Some_params_t;

typedef struct {
    termina__enum__Option__CheckLimitsResult__Some_params_t Some;
    termina__enum__Option_t _variant;
} Option__CheckLimitsResult;

typedef enum {
    CheckDeltaResult__MonitorDeltaLow,
    CheckDeltaResult__MonitorDeltaHigh,
    CheckDeltaResult__MonitorDeltaWithin
} termina__enum__CheckDeltaResult_t;

typedef struct {
    termina__enum__CheckDeltaResult_t _variant;
} CheckDeltaResult;

typedef struct {
    CheckDeltaResult _0;
} termina__enum__Option__CheckDeltaResult__Some_params_t;

typedef struct {
    termina__enum__Option__CheckDeltaResult__Some_params_t Some;
    termina__enum__Option_t _variant;
} Option__CheckDeltaResult;

typedef enum {
    CheckState__ParamValueStatus,
    CheckState__ParamLimitStatus,
    CheckState__ParamDeltaStatus,
    CheckState__Unselected
} termina__enum__CheckState_t;

typedef struct {
    Option__CheckValueResult _0;
} termina__enum__CheckState__ParamValueStatus_params_t;

typedef struct {
    Option__CheckLimitsResult _0;
} termina__enum__CheckState__ParamLimitStatus_params_t;

typedef struct {
    Option__CheckDeltaResult _0;
} termina__enum__CheckState__ParamDeltaStatus_params_t;

typedef struct {
    termina__enum__CheckState_t _variant;
    union {
        termina__enum__CheckState__ParamValueStatus_params_t ParamValueStatus;
        termina__enum__CheckState__ParamLimitStatus_params_t ParamLimitStatus;
        termina__enum__CheckState__ParamDeltaStatus_params_t ParamDeltaStatus;
    };
} CheckState;

typedef struct {
    CheckState _0;
} termina__enum__Option__CheckState__Some_params_t;

typedef struct {
    termina__enum__Option__CheckState__Some_params_t Some;
    termina__enum__Option_t _variant;
} Option__CheckState;

typedef struct {
    uint16_t PID;
    MonitorCheckType type;
    _Bool enabled;
    MonitorDefinition definition;
    uint8_t repetition;
    uint8_t repetition_control;
    uint8_t interval;
    uint8_t interval_control;
    CUCTime transition_obt;
    CheckState temp_state;
    CheckState current_state;
} ParamMonitoringConfiguration;

typedef struct {
    uint16_t PMONID;
    uint16_t PID;
    MonitorCheckType type;
    uint32_t mask_value;
    uint32_t limit_value;
    uint32_t new_value;
    CheckState prev_status;
    CheckState new_status;
    CUCTime trans_obt;
} ParamMonitoringTransition;

typedef enum {
    MonitoringOutcome__EventTriggered,
    MonitoringOutcome__NoEvent,
    MonitoringOutcome__NoReport
} termina__enum__MonitoringOutcome_t;

typedef struct {
    uint16_t _0;
    FaultInfo _1;
} termina__enum__MonitoringOutcome__EventTriggered_params_t;

typedef struct {
    termina__enum__MonitoringOutcome_t _variant;
    termina__enum__MonitoringOutcome__EventTriggered_params_t EventTriggered;
} MonitoringOutcome;

typedef struct {
    uint8_t N;
    uint16_t PMONID;
} PS12TC_1_2_6_Data;

typedef struct {
    uint8_t N;
    uint16_t PMONID;
    ParamMonitoringConfiguration mon_config;
} PS12TC_5_Data;

typedef enum {
    PUSService12Error__ErrorInAcceptance,
    PUSService12Error__AppDataOutOfRange,
    PUSService12Error__NumOfInstrNotValid,
    PUSService12Error__PIDNotValid,
    PUSService12Error__PMONUndefined,
    PUSService12Error__PMONIDInvalid,
    PUSService12Error__PMONDefinitionInvalid,
    PUSService12Error__PMONEnabled
} termina__enum__PUSService12Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService12Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService12Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService12Error__PIDNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService12Error__PMONUndefined_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService12Error__PMONIDInvalid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService12Error__PMONDefinitionInvalid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService12Error__PMONEnabled_params_t;

typedef struct {
    termina__enum__PUSService12Error_t _variant;
    union {
        termina__enum__PUSService12Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService12Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService12Error__PIDNotValid_params_t PIDNotValid;
        termina__enum__PUSService12Error__PMONUndefined_params_t PMONUndefined;
        termina__enum__PUSService12Error__PMONIDInvalid_params_t PMONIDInvalid;
        termina__enum__PUSService12Error__PMONDefinitionInvalid_params_t PMONDefinitionInvalid;
        termina__enum__PUSService12Error__PMONEnabled_params_t PMONEnabled;
    };
} PUSService12Error;

typedef struct {
    PUSService12Error _0;
} termina__enum__Status__PUSService12Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService12Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService12Error;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    PS12TC_1_2_6_Data tc_data_1_2_6;
    PS12TC_5_Data tc_data_5;
} PS12TCRequest;

uint8_t get_check_status_index(const CheckState status);

uint8_t get_type_index(const MonitorCheckType type);

_Bool are_status_equal(const CheckState status1, const CheckState status2);

_Bool is_PMONID_valid(const uint16_t PMONID);

MonitorCheckType get_check_type(const uint8_t aux);

_Bool is_valid_check_limit_def(const MonitorDefinition * const param_limit_check_definition);

Status__TMHandlerError build_tm_12_12(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const uint8_t counter, const ParamMonitoringTransition param_mon_transitions_table[1U]);

#endif
