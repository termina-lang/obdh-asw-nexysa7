
#include "obdh/pus/services/service12/internal.h"

uint8_t get_check_status_index(const CheckState status) {
    
    #line 190 "src/obdh/pus/services/service12/internal.fin"
    uint8_t status_index = 0U;

    #line 194 "src/obdh/pus/services/service12/internal.fin"
    if (status._variant == CheckState__ParamValueStatus) {
        
        #line 194 "src/obdh/pus/services/service12/internal.fin"
        const Option__CheckValueResult param_status = status.ParamValueStatus._0;

        #line 198 "src/obdh/pus/services/service12/internal.fin"
        if (param_status._variant == Option__None) {
            
            #line 199 "src/obdh/pus/services/service12/internal.fin"
            status_index = 1U;

        } else
        {
            
            #line 201 "src/obdh/pus/services/service12/internal.fin"
            const CheckValueResult result = param_status.Some._0;

            #line 205 "src/obdh/pus/services/service12/internal.fin"
            if (result._variant == CheckValueResult__MonitorValueUnexpected) {
                
                #line 206 "src/obdh/pus/services/service12/internal.fin"
                status_index = 2U;

            } else
            {
                
                #line 209 "src/obdh/pus/services/service12/internal.fin"
                status_index = 3U;

            }

        }

    } else
    #line 216 "src/obdh/pus/services/service12/internal.fin"
    if (status._variant == CheckState__ParamLimitStatus) {
        
        #line 216 "src/obdh/pus/services/service12/internal.fin"
        const Option__CheckLimitsResult limit_status = status.ParamLimitStatus._0;

        #line 220 "src/obdh/pus/services/service12/internal.fin"
        if (limit_status._variant == Option__None) {
            
            #line 221 "src/obdh/pus/services/service12/internal.fin"
            status_index = 4U;

        } else
        {
            
            #line 223 "src/obdh/pus/services/service12/internal.fin"
            const CheckLimitsResult result = limit_status.Some._0;

            #line 227 "src/obdh/pus/services/service12/internal.fin"
            if (result._variant == CheckLimitsResult__MonitorAboveHighLimit) {
                
                #line 228 "src/obdh/pus/services/service12/internal.fin"
                status_index = 5U;

            } else
            #line 230 "src/obdh/pus/services/service12/internal.fin"
            if (result._variant == CheckLimitsResult__MonitorBelowLowLimit) {
                
                #line 231 "src/obdh/pus/services/service12/internal.fin"
                status_index = 6U;

            } else
            {
                
                #line 234 "src/obdh/pus/services/service12/internal.fin"
                status_index = 7U;

            }

        }

    } else
    #line 241 "src/obdh/pus/services/service12/internal.fin"
    if (status._variant == CheckState__ParamDeltaStatus) {
        
        #line 241 "src/obdh/pus/services/service12/internal.fin"
        const Option__CheckDeltaResult delta_status = status.ParamDeltaStatus._0;

        #line 245 "src/obdh/pus/services/service12/internal.fin"
        if (delta_status._variant == Option__None) {
            
            #line 246 "src/obdh/pus/services/service12/internal.fin"
            status_index = 8U;

        } else
        {
            
            #line 248 "src/obdh/pus/services/service12/internal.fin"
            const CheckDeltaResult result = delta_status.Some._0;

            #line 252 "src/obdh/pus/services/service12/internal.fin"
            if (result._variant == CheckDeltaResult__MonitorDeltaLow) {
                
                #line 253 "src/obdh/pus/services/service12/internal.fin"
                status_index = 9U;

            } else
            #line 255 "src/obdh/pus/services/service12/internal.fin"
            if (result._variant == CheckDeltaResult__MonitorDeltaHigh) {
                
                #line 256 "src/obdh/pus/services/service12/internal.fin"
                status_index = 10U;

            } else
            {
                
                #line 259 "src/obdh/pus/services/service12/internal.fin"
                status_index = 11U;

            }

        }

    } else
    {
        

    }

    #line 271 "src/obdh/pus/services/service12/internal.fin"
    return status_index;

}

uint8_t get_type_index(const MonitorCheckType type) {
    
    #line 276 "src/obdh/pus/services/service12/internal.fin"
    uint8_t type_index;

    #line 280 "src/obdh/pus/services/service12/internal.fin"
    if (type._variant == MonitorCheckType__ExpectedValue) {
        
        #line 281 "src/obdh/pus/services/service12/internal.fin"
        type_index = 0U;

    } else
    #line 283 "src/obdh/pus/services/service12/internal.fin"
    if (type._variant == MonitorCheckType__Limits) {
        
        #line 284 "src/obdh/pus/services/service12/internal.fin"
        type_index = 1U;

    } else
    #line 286 "src/obdh/pus/services/service12/internal.fin"
    if (type._variant == MonitorCheckType__Delta) {
        
        #line 287 "src/obdh/pus/services/service12/internal.fin"
        type_index = 2U;

    } else
    {
        
        #line 290 "src/obdh/pus/services/service12/internal.fin"
        type_index = 0xFFU;

    }

    #line 294 "src/obdh/pus/services/service12/internal.fin"
    return type_index;

}

_Bool are_status_equal(const CheckState status1, const CheckState status2) {
    
    #line 300 "src/obdh/pus/services/service12/internal.fin"
    _Bool equal = get_check_status_index(status1) == get_check_status_index(status2);

    #line 302 "src/obdh/pus/services/service12/internal.fin"
    return equal;

}

_Bool is_PMONID_valid(const uint16_t PMONID) {
    
    #line 309 "src/obdh/pus/services/service12/internal.fin"
    _Bool is_valid = false;

    #line 311 "src/obdh/pus/services/service12/internal.fin"
    if ((size_t)PMONID < 16U) {
        
        #line 313 "src/obdh/pus/services/service12/internal.fin"
        is_valid = true;

    }

    #line 316 "src/obdh/pus/services/service12/internal.fin"
    return is_valid;

}

MonitorCheckType get_check_type(const uint8_t aux) {
    
    #line 322 "src/obdh/pus/services/service12/internal.fin"
    MonitorCheckType monitor_check;

    #line 324 "src/obdh/pus/services/service12/internal.fin"
    if (aux == 0U) {
        
        #line 326 "src/obdh/pus/services/service12/internal.fin"
        monitor_check._variant = MonitorCheckType__ExpectedValue;

    } else
    #line 328 "src/obdh/pus/services/service12/internal.fin"
    if (aux == 1U) {
        
        #line 330 "src/obdh/pus/services/service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Limits;

    } else
    #line 332 "src/obdh/pus/services/service12/internal.fin"
    if (aux == 2U) {
        
        #line 334 "src/obdh/pus/services/service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Delta;

    } else
    {
        
        #line 338 "src/obdh/pus/services/service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Free;

    }

    #line 342 "src/obdh/pus/services/service12/internal.fin"
    return monitor_check;

}

_Bool is_valid_check_limit_def(const MonitorDefinition * const param_limit_check_definition) {
    
    #line 348 "src/obdh/pus/services/service12/internal.fin"
    _Bool res = false;

    #line 352 "src/obdh/pus/services/service12/internal.fin"
    if ((*param_limit_check_definition)._variant == MonitorDefinition__ParamLimitCheck) {
        
        #line 352 "src/obdh/pus/services/service12/internal.fin"
        const ParamLimitCheckDefinition param_limit_def = (*param_limit_check_definition).ParamLimitCheck._0;

        #line 354 "src/obdh/pus/services/service12/internal.fin"
        if (param_limit_def.low_limit < param_limit_def.high_limit) {
            
            #line 356 "src/obdh/pus/services/service12/internal.fin"
            res = true;

        }

    } else
    {
        
        #line 362 "src/obdh/pus/services/service12/internal.fin"
        res = false;

    }

    #line 366 "src/obdh/pus/services/service12/internal.fin"
    return res;

}

Status__TMHandlerError build_tm_12_12(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const uint8_t counter, const ParamMonitoringTransition param_mon_transitions_table[1U]) {
    
    #line 372 "src/obdh/pus/services/service12/internal.fin"
    startup_tm(p_tm_handler);

    #line 373 "src/obdh/pus/services/service12/internal.fin"
    Status__TMHandlerError status = append_u8_appdata_field(p_tm_handler, counter);

    #line 375 "src/obdh/pus/services/service12/internal.fin"
    for (size_t i = 0U; i < 1U && i < (size_t)counter; i = i + 1U) {
        
        #line 377 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 378 "src/obdh/pus/services/service12/internal.fin"
            status = append_u16_appdata_field(p_tm_handler, param_mon_transitions_table[i].PMONID);

        }

        #line 380 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 381 "src/obdh/pus/services/service12/internal.fin"
            status = append_u16_appdata_field(p_tm_handler, param_mon_transitions_table[i].PID);

        }

        #line 383 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 384 "src/obdh/pus/services/service12/internal.fin"
            uint8_t type_id = get_type_index(param_mon_transitions_table[i].type);

            #line 385 "src/obdh/pus/services/service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, type_id);

        }

        #line 389 "src/obdh/pus/services/service12/internal.fin"
        if (param_mon_transitions_table[i].type._variant == MonitorCheckType__ExpectedValue && status._variant == Status__Success) {
            
            #line 390 "src/obdh/pus/services/service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].mask_value);

        }

        #line 393 "src/obdh/pus/services/service12/internal.fin"
        uint8_t aux_prev_status = get_check_status_index(param_mon_transitions_table[i].prev_status);

        #line 394 "src/obdh/pus/services/service12/internal.fin"
        uint8_t aux_new_status = get_check_status_index(param_mon_transitions_table[i].new_status);

        #line 396 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 397 "src/obdh/pus/services/service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].new_value);

        }

        #line 399 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 400 "src/obdh/pus/services/service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].limit_value);

        }

        #line 402 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 403 "src/obdh/pus/services/service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, aux_prev_status);

        }

        #line 405 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 406 "src/obdh/pus/services/service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, aux_new_status);

        }

        #line 408 "src/obdh/pus/services/service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 409 "src/obdh/pus/services/service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].trans_obt.seconds);

        }

    }

    #line 412 "src/obdh/pus/services/service12/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 413 "src/obdh/pus/services/service12/internal.fin"
        close_tm(p_tm_handler, 12U, 12U, tm_seq_counter, current_obt);

    }

    #line 417 "src/obdh/pus/services/service12/internal.fin"
    return status;

}
