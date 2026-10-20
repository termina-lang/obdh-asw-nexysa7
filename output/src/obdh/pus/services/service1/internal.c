
#include "obdh/pus/services/service1/internal.h"

const uint8_t ACCEPT_ACK_ENABLED_MASK = 0x1U;

const uint8_t EXEC_START_ACK_ENABLED_MASK = 0x2U;

const uint8_t EXEC_PROGRESS_ACK_ENABLED_MASK = 0x4U;

const uint8_t EXEC_COMPLETION_ACK_ENABLED_MASK = 0x8U;

_Bool is_crc_valid(const TCDescriptor * const tc_descriptor) {
    
    #line 80 "src/obdh/pus/services/service1/internal.fin"
    const uint16_t cal_crc_value = cal_crc_16(tc_descriptor->tc_bytes, tc_descriptor->tc_num_bytes - 2U);

    #line 81 "src/obdh/pus/services/service1/internal.fin"
    uint16_t packet_error_ctrl = get_packet_seq_ctrl(tc_descriptor->tc_bytes);

    #line 83 "src/obdh/pus/services/service1/internal.fin"
    _Bool is_valid = cal_crc_value == packet_error_ctrl;

    #line 85 "src/obdh/pus/services/service1/internal.fin"
    return is_valid;

}

_Bool is_apid_valid(const TCDescriptor * const tc_descriptor) {
    
    #line 96 "src/obdh/pus/services/service1/internal.fin"
    const uint16_t epd_apid = 0x32CU;

    #line 97 "src/obdh/pus/services/service1/internal.fin"
    uint16_t tc_apid = get_APID(tc_descriptor->tc_bytes);

    #line 99 "src/obdh/pus/services/service1/internal.fin"
    _Bool is_valid = epd_apid == tc_apid;

    #line 101 "src/obdh/pus/services/service1/internal.fin"
    return is_valid;

}

_Bool is_sourceID_valid(const TCDescriptor * const tc_descriptor) {
    
    #line 112 "src/obdh/pus/services/service1/internal.fin"
    const uint16_t System_SourceID = 0x78U;

    #line 114 "src/obdh/pus/services/service1/internal.fin"
    uint16_t sourceID = get_source_id(tc_descriptor->tc_bytes);

    #line 116 "src/obdh/pus/services/service1/internal.fin"
    _Bool is_valid = System_SourceID == sourceID;

    #line 118 "src/obdh/pus/services/service1/internal.fin"
    return is_valid;

}

_Bool is_tc_ack_accept_enabled(const uint8_t flags_ack) {
    
    #line 129 "src/obdh/pus/services/service1/internal.fin"
    _Bool ack_enabled = false;

    #line 131 "src/obdh/pus/services/service1/internal.fin"
    if ((uint8_t)(flags_ack & 0x1U) != 0U) {
        
        #line 132 "src/obdh/pus/services/service1/internal.fin"
        ack_enabled = true;

    }

    #line 134 "src/obdh/pus/services/service1/internal.fin"
    return ack_enabled;

}

_Bool is_tc_ack_start_exec_enabled(const uint8_t flags_ack) {
    
    #line 147 "src/obdh/pus/services/service1/internal.fin"
    _Bool ack_enabled = false;

    #line 149 "src/obdh/pus/services/service1/internal.fin"
    if ((uint8_t)(flags_ack & 0x2U) != 0U) {
        
        #line 150 "src/obdh/pus/services/service1/internal.fin"
        ack_enabled = true;

    }

    #line 152 "src/obdh/pus/services/service1/internal.fin"
    return ack_enabled;

}

_Bool is_tc_ack_progress_exec_enabled(const uint8_t flags_ack) {
    
    #line 164 "src/obdh/pus/services/service1/internal.fin"
    _Bool ack_enabled = false;

    #line 166 "src/obdh/pus/services/service1/internal.fin"
    if ((uint8_t)(flags_ack & 0x4U) != 0U) {
        
        #line 167 "src/obdh/pus/services/service1/internal.fin"
        ack_enabled = true;

    }

    #line 169 "src/obdh/pus/services/service1/internal.fin"
    return ack_enabled;

}

_Bool is_tc_ack_completion_exec_enabled(const uint8_t flags_ack) {
    
    #line 181 "src/obdh/pus/services/service1/internal.fin"
    _Bool ack_enabled = false;

    #line 183 "src/obdh/pus/services/service1/internal.fin"
    if ((uint8_t)(flags_ack & 0x8U) != 0U) {
        
        #line 184 "src/obdh/pus/services/service1/internal.fin"
        ack_enabled = true;

    }

    #line 186 "src/obdh/pus/services/service1/internal.fin"
    return ack_enabled;

}

uint8_t get_failure_subtype(const TCVerifyStage verify_stage) {
    
    #line 198 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype;

    #line 201 "src/obdh/pus/services/service1/internal.fin"
    if (verify_stage._variant == TCVerifyStage__Acceptation) {
        
        #line 202 "src/obdh/pus/services/service1/internal.fin"
        subtype = 2U;

    } else
    #line 204 "src/obdh/pus/services/service1/internal.fin"
    if (verify_stage._variant == TCVerifyStage__ExecStart) {
        
        #line 205 "src/obdh/pus/services/service1/internal.fin"
        subtype = 4U;

    } else
    #line 207 "src/obdh/pus/services/service1/internal.fin"
    if (verify_stage._variant == TCVerifyStage__Progress) {
        
        #line 208 "src/obdh/pus/services/service1/internal.fin"
        subtype = 6U;

    } else
    {
        
        #line 211 "src/obdh/pus/services/service1/internal.fin"
        subtype = 8U;

    }

    #line 215 "src/obdh/pus/services/service1/internal.fin"
    return subtype;

}

Status__TMHandlerError build_tm_1_X_no_failure_data(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const TCVerifyStage verify_stage, const uint8_t failure_code, const CUCTime current_obt) {
    
    #line 234 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype = get_failure_subtype(verify_stage);

    #line 236 "src/obdh/pus/services/service1/internal.fin"
    startup_tm(p_tm_handler);

    #line 237 "src/obdh/pus/services/service1/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, tc_packet_id);

    #line 238 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 239 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, tc_packet_seq_ctrl);

    }

    #line 241 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 242 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_code);

    }

    #line 244 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 245 "src/obdh/pus/services/service1/internal.fin"
        close_tm(p_tm_handler, 1U, subtype, tm_seq_counter, current_obt);

    }

    #line 248 "src/obdh/pus/services/service1/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_1_X_u8_failure_data(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const TCVerifyStage verify_stage, const uint8_t failure_code, const uint8_t failure_data, const CUCTime current_obt) {
    
    #line 259 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype = get_failure_subtype(verify_stage);

    #line 261 "src/obdh/pus/services/service1/internal.fin"
    startup_tm(p_tm_handler);

    #line 262 "src/obdh/pus/services/service1/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, tc_packet_id);

    #line 263 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 264 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, tc_packet_seq_ctrl);

    }

    #line 266 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 267 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_code);

    }

    #line 269 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 270 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_data);

    }

    #line 272 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 273 "src/obdh/pus/services/service1/internal.fin"
        close_tm(p_tm_handler, 1U, subtype, tm_seq_counter, current_obt);

    }

    #line 276 "src/obdh/pus/services/service1/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_1_X_u16_failure_data(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const TCVerifyStage verify_stage, const uint8_t failure_code, const uint16_t failure_data, const CUCTime current_obt) {
    
    #line 287 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype = get_failure_subtype(verify_stage);

    #line 289 "src/obdh/pus/services/service1/internal.fin"
    startup_tm(p_tm_handler);

    #line 290 "src/obdh/pus/services/service1/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, tc_packet_id);

    #line 291 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 292 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, tc_packet_seq_ctrl);

    }

    #line 294 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 295 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_code);

    }

    #line 297 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 298 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, failure_data);

    }

    #line 300 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 301 "src/obdh/pus/services/service1/internal.fin"
        close_tm(p_tm_handler, 1U, subtype, tm_seq_counter, current_obt);

    }

    #line 304 "src/obdh/pus/services/service1/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_1_X_u32_failure_data(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const TCVerifyStage verify_stage, const uint8_t failure_code, const uint32_t failure_data, const CUCTime current_obt) {
    
    #line 315 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype = get_failure_subtype(verify_stage);

    #line 317 "src/obdh/pus/services/service1/internal.fin"
    startup_tm(p_tm_handler);

    #line 318 "src/obdh/pus/services/service1/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, tc_packet_id);

    #line 319 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 320 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, tc_packet_seq_ctrl);

    }

    #line 322 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 323 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_code);

    }

    #line 325 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 326 "src/obdh/pus/services/service1/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, failure_data);

    }

    #line 328 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 329 "src/obdh/pus/services/service1/internal.fin"
        close_tm(p_tm_handler, 1U, subtype, tm_seq_counter, current_obt);

    }

    #line 332 "src/obdh/pus/services/service1/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_1_X_u8_u32_failure_data(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const TCVerifyStage verify_stage, const uint8_t failure_code, const uint8_t failure_data1, const uint32_t failure_data2, const CUCTime current_obt) {
    
    #line 345 "src/obdh/pus/services/service1/internal.fin"
    uint8_t subtype = get_failure_subtype(verify_stage);

    #line 347 "src/obdh/pus/services/service1/internal.fin"
    startup_tm(p_tm_handler);

    #line 348 "src/obdh/pus/services/service1/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, tc_packet_id);

    #line 349 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 350 "src/obdh/pus/services/service1/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, tc_packet_seq_ctrl);

    }

    #line 352 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 353 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_code);

    }

    #line 355 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 356 "src/obdh/pus/services/service1/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, failure_data1);

    }

    #line 358 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 359 "src/obdh/pus/services/service1/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, failure_data2);

    }

    #line 361 "src/obdh/pus/services/service1/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 362 "src/obdh/pus/services/service1/internal.fin"
        close_tm(p_tm_handler, 1U, subtype, tm_seq_counter, current_obt);

    }

    #line 365 "src/obdh/pus/services/service1/internal.fin"
    return status;

}
