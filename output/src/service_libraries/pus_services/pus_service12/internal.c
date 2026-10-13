
#include "service_libraries/pus_services/pus_service12/internal.h"

uint8_t get_check_status_index(const CheckState status) {
    
    #line 195 "src/service_libraries/pus_services/pus_service12/internal.fin"
    uint8_t status_index = 0U;

    #line 199 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (status._variant == CheckState__ParamValueStatus) {
        
        #line 199 "src/service_libraries/pus_services/pus_service12/internal.fin"
        const Option__CheckValueResult param_status = status.ParamValueStatus._0;

        #line 203 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (param_status._variant == Option__None) {
            
            #line 204 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status_index = 1U;

        } else
        {
            
            #line 206 "src/service_libraries/pus_services/pus_service12/internal.fin"
            const CheckValueResult result = param_status.Some._0;

            #line 210 "src/service_libraries/pus_services/pus_service12/internal.fin"
            if (result._variant == CheckValueResult__MonitorValueUnexpected) {
                
                #line 211 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 2U;

            } else
            {
                
                #line 214 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 3U;

            }

        }

    } else
    #line 221 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (status._variant == CheckState__ParamLimitStatus) {
        
        #line 221 "src/service_libraries/pus_services/pus_service12/internal.fin"
        const Option__CheckLimitsResult limit_status = status.ParamLimitStatus._0;

        #line 225 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (limit_status._variant == Option__None) {
            
            #line 226 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status_index = 4U;

        } else
        {
            
            #line 228 "src/service_libraries/pus_services/pus_service12/internal.fin"
            const CheckLimitsResult result = limit_status.Some._0;

            #line 232 "src/service_libraries/pus_services/pus_service12/internal.fin"
            if (result._variant == CheckLimitsResult__MonitorAboveHighLimit) {
                
                #line 233 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 5U;

            } else
            #line 235 "src/service_libraries/pus_services/pus_service12/internal.fin"
            if (result._variant == CheckLimitsResult__MonitorBelowLowLimit) {
                
                #line 236 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 6U;

            } else
            {
                
                #line 239 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 7U;

            }

        }

    } else
    #line 246 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (status._variant == CheckState__ParamDeltaStatus) {
        
        #line 246 "src/service_libraries/pus_services/pus_service12/internal.fin"
        const Option__CheckDeltaResult delta_status = status.ParamDeltaStatus._0;

        #line 250 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (delta_status._variant == Option__None) {
            
            #line 251 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status_index = 8U;

        } else
        {
            
            #line 253 "src/service_libraries/pus_services/pus_service12/internal.fin"
            const CheckDeltaResult result = delta_status.Some._0;

            #line 257 "src/service_libraries/pus_services/pus_service12/internal.fin"
            if (result._variant == CheckDeltaResult__MonitorDeltaLow) {
                
                #line 258 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 9U;

            } else
            #line 260 "src/service_libraries/pus_services/pus_service12/internal.fin"
            if (result._variant == CheckDeltaResult__MonitorDeltaHigh) {
                
                #line 261 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 10U;

            } else
            {
                
                #line 264 "src/service_libraries/pus_services/pus_service12/internal.fin"
                status_index = 11U;

            }

        }

    } else
    {
        

    }

    #line 276 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return status_index;

}

uint8_t get_type_index(const MonitorCheckType type) {
    
    #line 281 "src/service_libraries/pus_services/pus_service12/internal.fin"
    uint8_t type_index;

    #line 285 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (type._variant == MonitorCheckType__ExpectedValue) {
        
        #line 286 "src/service_libraries/pus_services/pus_service12/internal.fin"
        type_index = 0U;

    } else
    #line 288 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (type._variant == MonitorCheckType__Limits) {
        
        #line 289 "src/service_libraries/pus_services/pus_service12/internal.fin"
        type_index = 1U;

    } else
    #line 291 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (type._variant == MonitorCheckType__Delta) {
        
        #line 292 "src/service_libraries/pus_services/pus_service12/internal.fin"
        type_index = 2U;

    } else
    {
        
        #line 295 "src/service_libraries/pus_services/pus_service12/internal.fin"
        type_index = 0xFFU;

    }

    #line 299 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return type_index;

}

_Bool are_status_equal(const CheckState status1, const CheckState status2) {
    
    #line 305 "src/service_libraries/pus_services/pus_service12/internal.fin"
    _Bool equal = get_check_status_index(status1) == get_check_status_index(status2);

    #line 307 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return equal;

}

MonitorCheckType get_check_type(const uint8_t aux) {
    
    #line 314 "src/service_libraries/pus_services/pus_service12/internal.fin"
    MonitorCheckType monitor_check;

    #line 316 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (aux == 0U) {
        
        #line 318 "src/service_libraries/pus_services/pus_service12/internal.fin"
        monitor_check._variant = MonitorCheckType__ExpectedValue;

    } else
    #line 320 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (aux == 1U) {
        
        #line 322 "src/service_libraries/pus_services/pus_service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Limits;

    } else
    #line 324 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (aux == 2U) {
        
        #line 326 "src/service_libraries/pus_services/pus_service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Delta;

    } else
    {
        
        #line 330 "src/service_libraries/pus_services/pus_service12/internal.fin"
        monitor_check._variant = MonitorCheckType__Free;

    }

    #line 334 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return monitor_check;

}

_Bool is_valid_check_limit_def(const MonitorDefinition * const param_limit_check_definition) {
    
    #line 340 "src/service_libraries/pus_services/pus_service12/internal.fin"
    _Bool res = false;

    #line 344 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if ((*param_limit_check_definition)._variant == MonitorDefinition__ParamLimitCheck) {
        
        #line 344 "src/service_libraries/pus_services/pus_service12/internal.fin"
        const ParamLimitCheckDefinition param_limit_def = (*param_limit_check_definition).ParamLimitCheck._0;

        #line 346 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (param_limit_def.low_limit < param_limit_def.high_limit) {
            
            #line 348 "src/service_libraries/pus_services/pus_service12/internal.fin"
            res = true;

        }

    } else
    {
        
        #line 354 "src/service_libraries/pus_services/pus_service12/internal.fin"
        res = false;

    }

    #line 358 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return res;

}

Status__i32 build_tm_12_12(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const MissionOBT current_obt, const uint8_t counter, const ParamMonitoringTransition param_mon_transitions_table[1U]) {
    
    #line 364 "src/service_libraries/pus_services/pus_service12/internal.fin"
    startup_tm(p_tm_handler);

    #line 365 "src/service_libraries/pus_services/pus_service12/internal.fin"
    Status__i32 status = append_u8_appdata_field(p_tm_handler, counter);

    #line 367 "src/service_libraries/pus_services/pus_service12/internal.fin"
    for (size_t i = 0U; i < 1U && i < (size_t)counter; i = i + 1U) {
        
        #line 369 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 370 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u16_appdata_field(p_tm_handler, param_mon_transitions_table[i].PMONID);

        }

        #line 372 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 373 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u16_appdata_field(p_tm_handler, param_mon_transitions_table[i].PID);

        }

        #line 375 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 376 "src/service_libraries/pus_services/pus_service12/internal.fin"
            uint8_t type_id = get_type_index(param_mon_transitions_table[i].type);

            #line 377 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, type_id);

        }

        #line 381 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (param_mon_transitions_table[i].type._variant == MonitorCheckType__ExpectedValue && status._variant == Status__Success) {
            
            #line 382 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].mask_value);

        }

        #line 385 "src/service_libraries/pus_services/pus_service12/internal.fin"
        uint8_t aux_prev_status = get_check_status_index(param_mon_transitions_table[i].prev_status);

        #line 386 "src/service_libraries/pus_services/pus_service12/internal.fin"
        uint8_t aux_new_status = get_check_status_index(param_mon_transitions_table[i].new_status);

        #line 388 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 389 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].new_value);

        }

        #line 391 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 392 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].limit_value);

        }

        #line 394 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 395 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, aux_prev_status);

        }

        #line 397 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 398 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u8_appdata_field(p_tm_handler, aux_new_status);

        }

        #line 400 "src/service_libraries/pus_services/pus_service12/internal.fin"
        if (status._variant == Status__Success) {
            
            #line 401 "src/service_libraries/pus_services/pus_service12/internal.fin"
            status = append_u32_appdata_field(p_tm_handler, param_mon_transitions_table[i].trans_obt.seconds);

        }

    }

    #line 404 "src/service_libraries/pus_services/pus_service12/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 405 "src/service_libraries/pus_services/pus_service12/internal.fin"
        close_tm(p_tm_handler, 12U, 12U, tm_seq_counter, current_obt);

    }

    #line 409 "src/service_libraries/pus_services/pus_service12/internal.fin"
    return status;

}
