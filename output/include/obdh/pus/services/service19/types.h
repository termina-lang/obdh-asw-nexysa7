#ifndef OBDH__PUS__SERVICES__SERVICE19__TYPES_H__
#define OBDH__PUS__SERVICES__SERVICE19__TYPES_H__

#include <termina.h>

#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service5.h"

#include "option.h"

extern const size_t event_action_max_bytes;

extern const size_t min_tc_size;

typedef struct {
    _Bool enabled;
    uint16_t event_ID;
} EventActionConfig;

typedef struct {
    uint16_t packet_id;
    uint16_t packet_seq_ctrl;
    uint8_t flags_ack;
    size_t tc_num_bytes;
    uint8_t N;
    uint16_t EvID;
} PS19TCData;

typedef struct {
    _Bool found;
    size_t ev_action_index;
    _Bool enabled;
} FoundID;

typedef struct {
    PS19TCData tc_data;
    FoundID ev_action_ID;
    TCDescriptor action_tc_packet;
} PS19TCRequest;

typedef enum {
    TC19_1_Error__NoError,
    TC19_1_Error__EvIDEnabled,
    TC19_1_Error__MaxEventActionDefinitions
} termina__enum__TC19_1_Error_t;

typedef struct {
    termina__enum__TC19_1_Error_t _variant;
} TC19_1_Error;

typedef enum {
    PUSService19Error__ErrorInAcceptance,
    PUSService19Error__AppDataOutOfRange,
    PUSService19Error__NumOfInstrNotValid,
    PUSService19Error__EvIDNotValid,
    PUSService19Error__EvActionEnabled,
    PUSService19Error__EvActionRejected,
    PUSService19Error__EvActionUndefined,
    PUSService19Error__MaxEvActionsDefined
} termina__enum__PUSService19Error_t;

typedef struct {
    size_t _0;
} termina__enum__PUSService19Error__AppDataOutOfRange_params_t;

typedef struct {
    uint8_t _0;
} termina__enum__PUSService19Error__NumOfInstrNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService19Error__EvIDNotValid_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService19Error__EvActionEnabled_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService19Error__EvActionRejected_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService19Error__EvActionUndefined_params_t;

typedef struct {
    uint16_t _0;
} termina__enum__PUSService19Error__MaxEvActionsDefined_params_t;

typedef struct {
    termina__enum__PUSService19Error_t _variant;
    union {
        termina__enum__PUSService19Error__AppDataOutOfRange_params_t AppDataOutOfRange;
        termina__enum__PUSService19Error__NumOfInstrNotValid_params_t NumOfInstrNotValid;
        termina__enum__PUSService19Error__EvIDNotValid_params_t EvIDNotValid;
        termina__enum__PUSService19Error__EvActionEnabled_params_t EvActionEnabled;
        termina__enum__PUSService19Error__EvActionRejected_params_t EvActionRejected;
        termina__enum__PUSService19Error__EvActionUndefined_params_t EvActionUndefined;
        termina__enum__PUSService19Error__MaxEvActionsDefined_params_t MaxEvActionsDefined;
    };
} PUSService19Error;

typedef struct {
    PUSService19Error _0;
} termina__enum__Status__PUSService19Error__Failure_params_t;

typedef struct {
    termina__enum__Status__PUSService19Error__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__PUSService19Error;

#endif
