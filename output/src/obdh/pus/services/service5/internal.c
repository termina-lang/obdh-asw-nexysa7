
#include "obdh/pus/services/service5/internal.h"

const uint16_t informative_Ev_IDs = 3U;

const uint16_t low_severity_anomaly_Ev_IDs = 4U;

const uint16_t medium_severity_anomaly_Ev_IDs = 0U;

const uint16_t high_severity_anomaly_Ev_IDs = 16U;

const uint16_t Ev_IDs_per_type[5U] = { 0U, 3U, 4U, 0U, 16U };

const uint16_t offset_mask = 0x1FU;

const uint16_t EvID_build_tm_error = 0x2100U;

Ev_IDType get_Ev_ID_type(const uint16_t Ev_ID) {
    
    #line 79 "src/obdh/pus/services/service5/internal.fin"
    Ev_IDType Ev_ID_type = { ._variant = Ev_IDType__Ev_IDNotValid };

    #line 80 "src/obdh/pus/services/service5/internal.fin"
    uint16_t aux_type = Ev_ID >> 12U;

    #line 82 "src/obdh/pus/services/service5/internal.fin"
    if (aux_type >= 1U && aux_type <= 4U) {
        
        #line 83 "src/obdh/pus/services/service5/internal.fin"
        uint16_t aux_id = Ev_ID & 0xFFFU;

        #line 84 "src/obdh/pus/services/service5/internal.fin"
        if (aux_id < Ev_IDs_per_type[(size_t)aux_type]) {
            
            #line 85 "src/obdh/pus/services/service5/internal.fin"
            if (aux_type == 1U) {
                
                #line 86 "src/obdh/pus/services/service5/internal.fin"
                Ev_ID_type._variant = Ev_IDType__Informative;

            } else
            #line 87 "src/obdh/pus/services/service5/internal.fin"
            if (aux_type == 2U) {
                
                #line 88 "src/obdh/pus/services/service5/internal.fin"
                Ev_ID_type._variant = Ev_IDType__LowSeverityAnomaly;

            } else
            #line 89 "src/obdh/pus/services/service5/internal.fin"
            if (aux_type == 3U) {
                
                #line 90 "src/obdh/pus/services/service5/internal.fin"
                Ev_ID_type._variant = Ev_IDType__MediumSeverityAnomaly;

            } else
            {
                
                #line 92 "src/obdh/pus/services/service5/internal.fin"
                Ev_ID_type._variant = Ev_IDType__HighSeverityAnomaly;

            }

        }

    }

    #line 97 "src/obdh/pus/services/service5/internal.fin"
    return Ev_ID_type;

}

_Bool is_Ev_ID_valid(const uint16_t evID) {
    
    #line 103 "src/obdh/pus/services/service5/internal.fin"
    _Bool is_valid = true;

    #line 104 "src/obdh/pus/services/service5/internal.fin"
    Ev_IDType evID_type = get_Ev_ID_type(evID);

    #line 105 "src/obdh/pus/services/service5/internal.fin"
    if (evID_type._variant == Ev_IDType__Ev_IDNotValid) {
        
        #line 106 "src/obdh/pus/services/service5/internal.fin"
        is_valid = false;

    } else
    {
        

    }

    #line 110 "src/obdh/pus/services/service5/internal.fin"
    return is_valid;

}

size_t get_Ev_ID_enable_config_index(const uint16_t Ev_ID) {
    
    #line 117 "src/obdh/pus/services/service5/internal.fin"
    Ev_IDType Ev_ID_type = get_Ev_ID_type(Ev_ID);

    #line 118 "src/obdh/pus/services/service5/internal.fin"
    size_t config_slot = 0U;

    #line 120 "src/obdh/pus/services/service5/internal.fin"
    if (Ev_ID_type._variant == Ev_IDType__Informative) {
        
        #line 121 "src/obdh/pus/services/service5/internal.fin"
        config_slot = 1U;

    } else
    #line 123 "src/obdh/pus/services/service5/internal.fin"
    if (Ev_ID_type._variant == Ev_IDType__LowSeverityAnomaly) {
        
        #line 124 "src/obdh/pus/services/service5/internal.fin"
        config_slot = 2U;

    } else
    #line 126 "src/obdh/pus/services/service5/internal.fin"
    if (Ev_ID_type._variant == Ev_IDType__MediumSeverityAnomaly) {
        
        #line 127 "src/obdh/pus/services/service5/internal.fin"
        config_slot = 3U;

    } else
    #line 129 "src/obdh/pus/services/service5/internal.fin"
    if (Ev_ID_type._variant == Ev_IDType__HighSeverityAnomaly) {
        
        #line 130 "src/obdh/pus/services/service5/internal.fin"
        config_slot = 4U;

    } else
    {
        

    }

    #line 136 "src/obdh/pus/services/service5/internal.fin"
    return config_slot;

}

uint8_t get_Ev_ID_enable_config_offset(const uint16_t Ev_ID) {
    
    #line 141 "src/obdh/pus/services/service5/internal.fin"
    return (uint8_t)(uint16_t)(Ev_ID & 0x1FU);

}

Status__TMHandlerError build_tm_5_x_param_out_of_limit(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const ParamOutOfLimitInfo fault_info, const uint16_t ev_ID, const CUCTime current_obt) {
    
    #line 148 "src/obdh/pus/services/service5/internal.fin"
    startup_tm(p_tm_handler);

    #line 149 "src/obdh/pus/services/service5/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, ev_ID);

    #line 150 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 151 "src/obdh/pus/services/service5/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, fault_info.PID);

    }

    #line 153 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 154 "src/obdh/pus/services/service5/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, fault_info.PID_value);

    }

    #line 156 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 157 "src/obdh/pus/services/service5/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, fault_info.PID_limit);

    }

    #line 159 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 160 "src/obdh/pus/services/service5/internal.fin"
        uint8_t subtype = (uint8_t)get_Ev_ID_enable_config_index(ev_ID);

        #line 161 "src/obdh/pus/services/service5/internal.fin"
        close_tm(p_tm_handler, 5U, subtype, tm_seq_counter, current_obt);

    }

    #line 164 "src/obdh/pus/services/service5/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_5_x_param_check_value_fail(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const ParamFaultValueInfo fault_info, const uint16_t ev_ID, const CUCTime current_obt) {
    
    #line 170 "src/obdh/pus/services/service5/internal.fin"
    startup_tm(p_tm_handler);

    #line 171 "src/obdh/pus/services/service5/internal.fin"
    Status__TMHandlerError status = append_u16_appdata_field(p_tm_handler, ev_ID);

    #line 172 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 173 "src/obdh/pus/services/service5/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, fault_info.PID);

    }

    #line 175 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 176 "src/obdh/pus/services/service5/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, fault_info.PID_value);

    }

    #line 178 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 179 "src/obdh/pus/services/service5/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, fault_info.PID_mask);

    }

    #line 181 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 182 "src/obdh/pus/services/service5/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, fault_info.PID_expected_value);

    }

    #line 184 "src/obdh/pus/services/service5/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 185 "src/obdh/pus/services/service5/internal.fin"
        uint8_t subtype = (uint8_t)get_Ev_ID_enable_config_index(ev_ID);

        #line 186 "src/obdh/pus/services/service5/internal.fin"
        close_tm(p_tm_handler, 5U, subtype, tm_seq_counter, current_obt);

    }

    #line 189 "src/obdh/pus/services/service5/internal.fin"
    return status;

}
