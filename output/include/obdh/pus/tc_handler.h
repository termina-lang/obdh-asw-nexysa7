#ifndef OBDH__PUS__TC_HANDLER_H__
#define OBDH__PUS__TC_HANDLER_H__

#include <termina.h>

#include "obdh/pus/tc_packet.h"

#include "option.h"

typedef enum {
    TCHandlerError__AppDataOutOfRange
} termina__enum__TCHandlerError_t;

typedef struct {
    termina__enum__TCHandlerError_t _variant;
} TCHandlerError;

typedef struct {
    TCHandlerError _0;
} termina__enum__Status__TCHandlerError__Failure_params_t;

typedef struct {
    termina__enum__Status__TCHandlerError__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__TCHandlerError;

typedef struct {
    TCDescriptor tc_descriptor;
    CCSDSPUSTCPacketHeader packet_header;
    CCSDSPUSTCDFHeader df_header;
    uint16_t packet_error_ctrl;
    size_t app_data_index;
} TCHandler;

void tc_handler_build(TCHandler * const tc_handler);

_Bool tc_handler_is_valid_next_appdata_field(const TCHandler * const tc_handler, const size_t field_size);

Status__TCHandlerError tc_handler_get_u8_appdata_field(TCHandler * const tc_handler, uint8_t * const data);

Status__TCHandlerError tc_handler_get_u16_appdata_field(TCHandler * const tc_handler, uint16_t * const data);

Status__TCHandlerError tc_handler_get_u32_appdata_field(TCHandler * const tc_handler, uint32_t * const data);

#endif
