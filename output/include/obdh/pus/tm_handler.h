#ifndef OBDH__PUS__TM_HANDLER_H__
#define OBDH__PUS__TM_HANDLER_H__

#include <termina.h>

#include "encoding/binary.h"
#include "obdh/pus/time.h"
#include "obdh/pus/tm_packet.h"

#include "option.h"

typedef enum {
    TMHandlerError__AppDataOverflow
} termina__enum__TMHandlerError_t;

typedef struct {
    termina__enum__TMHandlerError_t _variant;
} TMHandlerError;

typedef struct {
    TMHandlerError _0;
} termina__enum__Status__TMHandlerError__Failure_params_t;

typedef struct {
    termina__enum__Status__TMHandlerError__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__TMHandlerError;

typedef struct {
    TMDescriptor tm_descriptor;
    CCSDSPUSTMPacketHeader packet_header;
    CCSDSPUSTMDFHeader df_header;
    size_t app_data_index;
} TMHandler;

extern const uint16_t APID;

extern const uint16_t DESTINATION_ID;

extern const size_t tm_app_data_offset;

Status__TMHandlerError append_u8_appdata_field(TMHandler * const tm_handler, const uint8_t data);

Status__TMHandlerError append_u16_appdata_field(TMHandler * const tm_handler, const uint16_t data);

Status__TMHandlerError append_u32_appdata_field(TMHandler * const tm_handler, const uint32_t data);

void tm_handler_build_packet_header(TMHandler * const tm_handler, const uint16_t tm_seq_counter);

void tm_handler_build_df_header(TMHandler * const tm_handler, const uint8_t tm_type, const uint8_t tm_subtype, const CUCTime current_obt);

void close_tm(TMHandler * const tm_handler, const uint8_t type, const uint8_t subtype, const uint16_t tm_count, const CUCTime current_obt);

void startup_tm(TMHandler * const tm_handler);

#endif
