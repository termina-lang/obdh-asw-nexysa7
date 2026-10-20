
#include "obdh/pus/services/service12.h"

static _Bool CPUSService12__PID_has_expected_masked_value(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamValueCheckDefinition * const expected_value_check_definition);

static _Bool CPUSService12__PID_is_above_upper_limit(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamLimitCheckDefinition * const limit_check_def);

static _Bool CPUSService12__PID_is_below_lower_limit(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamLimitCheckDefinition * const limit_check_def);

static void CPUSService12__add_monitoring_transition(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info, const CheckState new_status, const CheckState prev_status);

static void CPUSService12__add_valid_mng_mon_def(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static ParamValueCheckDefinition CPUSService12__get_expected_value_monitoring_definition(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static CheckValueResult CPUSService12__check_PID_status_exp_val_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static ParamLimitCheckDefinition CPUSService12__get_limits_monitoring_definition(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static CheckLimitsResult CPUSService12__check_PID_status_limits_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static _Bool CPUSService12__is_expected_value_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static _Bool CPUSService12__is_limits_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID);

static Option__CheckState CPUSService12__manage_new_status(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const CheckState new_state);

static MonitoringOutcome CPUSService12__manage_expected_value(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info);

static _Bool CPUSService12__manage_interval_control(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID);

static MonitoringOutcome CPUSService12__manage_param_above_upper_limit(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID);

static MonitoringOutcome CPUSService12__manage_param_below_lower_limit(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID);

static MonitoringOutcome CPUSService12__manage_param_within_limits(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info);

static MonitoringOutcome CPUSService12__manage_unexpected_value(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID);

static Status__PUSService12Error CPUSService12__exec12_1TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static void CPUSService12__set_unchecked(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static Status__PUSService12Error CPUSService12__exec12_2TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static Status__PUSService12Error CPUSService12__exec12_5TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static Status__PUSService12Error CPUSService12__exec12_6TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request);

static _Bool CPUSService12__PID_has_expected_masked_value(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamValueCheckDefinition * const expected_value_check_definition) {
    
    (void)termina__ev;

    #line 238 "src/obdh/pus/services/service12.fin"
    _Bool res = false;

    #line 239 "src/obdh/pus/services/service12.fin"
    uint16_t PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

    #line 240 "src/obdh/pus/services/service12.fin"
    uint32_t SDP_value = 0U;

    #line 241 "src/obdh/pus/services/service12.fin"
    DataPoolItem type = sys_data_pool_get_item(PID);

    #line 245 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U32Item) {
        
        #line 245 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U32Item._0;

        #line 246 "src/obdh/pus/services/service12.fin"
        SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

    } else
    #line 248 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U8Item) {
        
        #line 248 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U8Item._0;

        #line 249 "src/obdh/pus/services/service12.fin"
        uint8_t SDP_value_u8 = 0U;

        #line 250 "src/obdh/pus/services/service12.fin"
        SDP_value_u8 = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 251 "src/obdh/pus/services/service12.fin"
        SDP_value = (uint32_t)SDP_value_u8;

    } else
    {
        

    }

    #line 258 "src/obdh/pus/services/service12.fin"
    if ((uint32_t)(SDP_value & expected_value_check_definition->mask_value) == (uint32_t)(expected_value_check_definition->expected_value & expected_value_check_definition->mask_value)) {
        
        #line 260 "src/obdh/pus/services/service12.fin"
        res = true;

    }

    #line 263 "src/obdh/pus/services/service12.fin"
    return res;

}

static _Bool CPUSService12__PID_is_above_upper_limit(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamLimitCheckDefinition * const limit_check_def) {
    
    (void)termina__ev;

    #line 174 "src/obdh/pus/services/service12.fin"
    _Bool res = false;

    #line 175 "src/obdh/pus/services/service12.fin"
    uint32_t upper_limit = limit_check_def->high_limit;

    #line 176 "src/obdh/pus/services/service12.fin"
    uint16_t PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

    #line 177 "src/obdh/pus/services/service12.fin"
    DataPoolItem type = sys_data_pool_get_item(PID);

    #line 178 "src/obdh/pus/services/service12.fin"
    uint32_t SDP_value = 0U;

    #line 182 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U32Item) {
        
        #line 182 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U32Item._0;

        #line 183 "src/obdh/pus/services/service12.fin"
        SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

    } else
    #line 185 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U8Item) {
        
        #line 185 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U8Item._0;

        #line 186 "src/obdh/pus/services/service12.fin"
        uint8_t SDP_value_u8 = 0U;

        #line 187 "src/obdh/pus/services/service12.fin"
        SDP_value_u8 = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 189 "src/obdh/pus/services/service12.fin"
        SDP_value = (uint32_t)SDP_value_u8;

    } else
    {
        

    }

    #line 196 "src/obdh/pus/services/service12.fin"
    if (SDP_value > upper_limit) {
        
        #line 198 "src/obdh/pus/services/service12.fin"
        res = true;

    }

    #line 201 "src/obdh/pus/services/service12.fin"
    return res;

}

static _Bool CPUSService12__PID_is_below_lower_limit(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID, const ParamLimitCheckDefinition * const limit_check_def) {
    
    (void)termina__ev;

    #line 206 "src/obdh/pus/services/service12.fin"
    _Bool res = false;

    #line 207 "src/obdh/pus/services/service12.fin"
    uint32_t lower_limit = limit_check_def->low_limit;

    #line 208 "src/obdh/pus/services/service12.fin"
    uint16_t PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

    #line 209 "src/obdh/pus/services/service12.fin"
    DataPoolItem type = sys_data_pool_get_item(PID);

    #line 210 "src/obdh/pus/services/service12.fin"
    uint32_t SDP_value = 0U;

    #line 214 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U32Item) {
        
        #line 214 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U32Item._0;

        #line 215 "src/obdh/pus/services/service12.fin"
        SDP_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

    } else
    #line 217 "src/obdh/pus/services/service12.fin"
    if (type._variant == DataPoolItem__U8Item) {
        
        #line 217 "src/obdh/pus/services/service12.fin"
        const size_t sdp_index = type.U8Item._0;

        #line 218 "src/obdh/pus/services/service12.fin"
        uint8_t SDP_value_u8 = 0U;

        #line 219 "src/obdh/pus/services/service12.fin"
        SDP_value_u8 = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

        #line 220 "src/obdh/pus/services/service12.fin"
        SDP_value = (uint32_t)SDP_value_u8;

    } else
    {
        

    }

    #line 227 "src/obdh/pus/services/service12.fin"
    if (SDP_value < lower_limit) {
        
        #line 229 "src/obdh/pus/services/service12.fin"
        res = true;

    }

    #line 232 "src/obdh/pus/services/service12.fin"
    return res;

}

static void CPUSService12__add_monitoring_transition(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info, const CheckState new_status, const CheckState prev_status) {
    
    #line 543 "src/obdh/pus/services/service12.fin"
    if ((size_t)self->monitoring_transition_counter < 1U) {
        
        #line 545 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

        #line 546 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].PMONID = PMONID;

        #line 547 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].type = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].type;

        #line 549 "src/obdh/pus/services/service12.fin"
        if ((*fault_info)._variant == FaultInfo__ParamOutOfLimit) {
            
            #line 549 "src/obdh/pus/services/service12.fin"
            const ParamOutOfLimitInfo out_of_limit_info = (*fault_info).ParamOutOfLimit._0;

            #line 550 "src/obdh/pus/services/service12.fin"
            self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].limit_value = out_of_limit_info.PID_limit;

            #line 551 "src/obdh/pus/services/service12.fin"
            self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].new_value = out_of_limit_info.PID_value;

        } else
        #line 553 "src/obdh/pus/services/service12.fin"
        if ((*fault_info)._variant == FaultInfo__ParamFaultValue) {
            
            #line 553 "src/obdh/pus/services/service12.fin"
            const ParamFaultValueInfo fault_value_info = (*fault_info).ParamFaultValue._0;

            #line 554 "src/obdh/pus/services/service12.fin"
            self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].limit_value = fault_value_info.PID_expected_value;

            #line 555 "src/obdh/pus/services/service12.fin"
            self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].new_value = fault_value_info.PID_value;

        } else
        {
            

        }

        #line 564 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamValueCheck) {
            
            #line 564 "src/obdh/pus/services/service12.fin"
            const ParamValueCheckDefinition value_definition = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamValueCheck._0;

            #line 566 "src/obdh/pus/services/service12.fin"
            self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].mask_value = value_definition.mask_value;

        } else
        {
            

        }

        #line 575 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].new_status = new_status;

        #line 576 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].prev_status = prev_status;

        #line 577 "src/obdh/pus/services/service12.fin"
        self->param_mon_transitions_table[termina__check__array_index(1U, (size_t)self->monitoring_transition_counter)].trans_obt = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].transition_obt;

        #line 579 "src/obdh/pus/services/service12.fin"
        self->monitoring_transition_counter = self->monitoring_transition_counter + 1U;

    }

    #line 582 "src/obdh/pus/services/service12.fin"
    if ((size_t)self->monitoring_transition_counter == 1U) {
        
        #line 584 "src/obdh/pus/services/service12.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 585 "src/obdh/pus/services/service12.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 589 "src/obdh/pus/services/service12.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 589 "src/obdh/pus/services/service12.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 591 "src/obdh/pus/services/service12.fin"
            uint16_t tm_count = 0U;

            #line 592 "src/obdh/pus/services/service12.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 593 "src/obdh/pus/services/service12.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 594 "src/obdh/pus/services/service12.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 596 "src/obdh/pus/services/service12.fin"
            const Status__TMHandlerError monitoring_status = build_tm_12_12((TMHandler *)b_tm_handler.data, tm_count, current_obt, self->monitoring_transition_counter, self->param_mon_transitions_table);

            #line 598 "src/obdh/pus/services/service12.fin"
            if (monitoring_status._variant == Status__Success) {
                
                #line 599 "src/obdh/pus/services/service12.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 602 "src/obdh/pus/services/service12.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 603 "src/obdh/pus/services/service12.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        } else
        {
            
            #line 609 "src/obdh/pus/services/service12.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

        #line 615 "src/obdh/pus/services/service12.fin"
        self->monitoring_transition_counter = 0U;

    }

    #line 618 "src/obdh/pus/services/service12.fin"
    return;

}

static void CPUSService12__add_valid_mng_mon_def(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    (void)termina__ev;

    #line 833 "src/obdh/pus/services/service12.fin"
    const size_t PMONID = (size_t)tc_request->tc_data_5.PMONID;

    #line 835 "src/obdh/pus/services/service12.fin"
    self->param_mon_config_table[termina__check__array_index(16U, PMONID)] = tc_request->tc_data_5.mon_config;

    #line 837 "src/obdh/pus/services/service12.fin"
    self->param_mon_config_table[termina__check__array_index(16U, PMONID)].enabled = false;

    #line 840 "src/obdh/pus/services/service12.fin"
    if (PMONID < 16U) {
        
        #line 844 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[PMONID].type._variant == MonitorCheckType__ExpectedValue) {
            
            #line 846 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state._variant = CheckState__ParamValueStatus;
            #line 846 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state.ParamValueStatus._0._variant = Option__None;

        } else
        #line 848 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[PMONID].type._variant == MonitorCheckType__Limits) {
            
            #line 850 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state._variant = CheckState__ParamLimitStatus;
            #line 850 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state.ParamLimitStatus._0._variant = Option__None;

        } else
        #line 853 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[PMONID].type._variant == MonitorCheckType__Delta) {
            
            #line 855 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state._variant = CheckState__ParamDeltaStatus;
            #line 855 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[PMONID].current_state.ParamDeltaStatus._0._variant = Option__None;

        } else
        {
            

        }

    }

    #line 868 "src/obdh/pus/services/service12.fin"
    return;

}

static ParamValueCheckDefinition CPUSService12__get_expected_value_monitoring_definition(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    (void)termina__ev;

    #line 88 "src/obdh/pus/services/service12.fin"
    ParamValueCheckDefinition monitoring_definition = { .EvID = 0U, .expected_value = 0U, .mask_value = 0U };

    #line 96 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamValueCheck) {
        
        #line 96 "src/obdh/pus/services/service12.fin"
        const ParamValueCheckDefinition param_check_definition = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamValueCheck._0;

        #line 98 "src/obdh/pus/services/service12.fin"
        monitoring_definition = param_check_definition;

    } else
    {
        

    }

    #line 107 "src/obdh/pus/services/service12.fin"
    return monitoring_definition;

}

static CheckValueResult CPUSService12__check_PID_status_exp_val_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    #line 155 "src/obdh/pus/services/service12.fin"
    ParamValueCheckDefinition current_monitor_definition = CPUSService12__get_expected_value_monitoring_definition(termina__ev, self, PMONID);

    #line 156 "src/obdh/pus/services/service12.fin"
    CheckValueResult check_status;

    #line 158 "src/obdh/pus/services/service12.fin"
    if (CPUSService12__PID_has_expected_masked_value(termina__ev, self, PMONID, &current_monitor_definition)) {
        
        #line 160 "src/obdh/pus/services/service12.fin"
        check_status._variant = CheckValueResult__MonitorValueExpected;

    } else
    {
        
        #line 165 "src/obdh/pus/services/service12.fin"
        check_status._variant = CheckValueResult__MonitorValueUnexpected;

    }

    #line 169 "src/obdh/pus/services/service12.fin"
    return check_status;

}

static ParamLimitCheckDefinition CPUSService12__get_limits_monitoring_definition(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    (void)termina__ev;

    #line 63 "src/obdh/pus/services/service12.fin"
    ParamLimitCheckDefinition monitoring_definition = { .high_limit = 0U, .high_limit_evID = 0U, .low_limit = 0U, .low_limit_evID = 0U };

    #line 72 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamLimitCheck) {
        
        #line 72 "src/obdh/pus/services/service12.fin"
        const ParamLimitCheckDefinition limit_check_def = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamLimitCheck._0;

        #line 74 "src/obdh/pus/services/service12.fin"
        monitoring_definition = limit_check_def;

    } else
    {
        

    }

    #line 82 "src/obdh/pus/services/service12.fin"
    return monitoring_definition;

}

static CheckLimitsResult CPUSService12__check_PID_status_limits_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    #line 130 "src/obdh/pus/services/service12.fin"
    ParamLimitCheckDefinition current_monitor_definition = CPUSService12__get_limits_monitoring_definition(termina__ev, self, PMONID);

    #line 131 "src/obdh/pus/services/service12.fin"
    CheckLimitsResult check_status;

    #line 133 "src/obdh/pus/services/service12.fin"
    if (CPUSService12__PID_is_above_upper_limit(termina__ev, self, PMONID, &current_monitor_definition)) {
        
        #line 135 "src/obdh/pus/services/service12.fin"
        check_status._variant = CheckLimitsResult__MonitorAboveHighLimit;

    } else
    #line 138 "src/obdh/pus/services/service12.fin"
    if (CPUSService12__PID_is_below_lower_limit(termina__ev, self, PMONID, &current_monitor_definition)) {
        
        #line 140 "src/obdh/pus/services/service12.fin"
        check_status._variant = CheckLimitsResult__MonitorBelowLowLimit;

    } else
    {
        
        #line 146 "src/obdh/pus/services/service12.fin"
        check_status._variant = CheckLimitsResult__MonitorWithinLimits;

    }

    #line 149 "src/obdh/pus/services/service12.fin"
    return check_status;

}

static _Bool CPUSService12__is_expected_value_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    (void)termina__ev;

    #line 51 "src/obdh/pus/services/service12.fin"
    _Bool is_exp_val_mon = false;

    #line 53 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].type._variant == MonitorCheckType__ExpectedValue) {
        
        #line 55 "src/obdh/pus/services/service12.fin"
        is_exp_val_mon = true;

    }

    #line 58 "src/obdh/pus/services/service12.fin"
    return is_exp_val_mon;

}

static _Bool CPUSService12__is_limits_monitoring(const termina__event_t * const termina__ev, const CPUSService12 * const self, const uint16_t PMONID) {
    
    (void)termina__ev;

    #line 38 "src/obdh/pus/services/service12.fin"
    _Bool is_limits_mon = false;

    #line 40 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].type._variant == MonitorCheckType__Limits) {
        
        #line 42 "src/obdh/pus/services/service12.fin"
        is_limits_mon = true;

    }

    #line 45 "src/obdh/pus/services/service12.fin"
    return is_limits_mon;

}

static Option__CheckState CPUSService12__manage_new_status(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const CheckState new_state) {
    
    #line 503 "src/obdh/pus/services/service12.fin"
    Option__CheckState prev_state = { ._variant = Option__None };

    #line 504 "src/obdh/pus/services/service12.fin"
    CheckState current_state = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].current_state;

    #line 505 "src/obdh/pus/services/service12.fin"
    CheckState temp_state = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].temp_state;

    #line 507 "src/obdh/pus/services/service12.fin"
    if (are_status_equal(new_state, current_state) == false) {
        
        #line 509 "src/obdh/pus/services/service12.fin"
        if (are_status_equal(new_state, temp_state)) {
            
            #line 511 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control + 1U;

        } else
        {
            
            #line 515 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].temp_state = new_state;

            #line 516 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control = 1U;

            #line 517 "src/obdh/pus/services/service12.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 518 "src/obdh/pus/services/service12.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 519 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].transition_obt = current_obt;

        }

        #line 522 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control >= self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition) {
            
            #line 524 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control = 0U;

            #line 525 "src/obdh/pus/services/service12.fin"
            prev_state._variant = Option__Some;
            #line 525 "src/obdh/pus/services/service12.fin"
            prev_state.Some._0 = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].current_state;

            #line 526 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].current_state = new_state;

        }

    } else
    {
        
        #line 532 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].temp_state = new_state;

        #line 533 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].repetition_control = 0U;

    }

    #line 537 "src/obdh/pus/services/service12.fin"
    return prev_state;

}

static MonitoringOutcome CPUSService12__manage_expected_value(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info) {
    
    #line 334 "src/obdh/pus/services/service12.fin"
    const MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoEvent };

    #line 336 "src/obdh/pus/services/service12.fin"
    const CheckValueResult check_status = { ._variant = CheckValueResult__MonitorValueExpected };

    #line 337 "src/obdh/pus/services/service12.fin"
    const CheckState new_status = { ._variant = CheckState__ParamValueStatus, .ParamValueStatus = { ._0 = { ._variant = Option__Some, .Some = { ._0 = check_status } } } };

    #line 339 "src/obdh/pus/services/service12.fin"
    Option__CheckState prev_status = CPUSService12__manage_new_status(termina__ev, self, PMONID, new_status);

    #line 342 "src/obdh/pus/services/service12.fin"
    if (prev_status._variant == Option__Some) {
        
        #line 342 "src/obdh/pus/services/service12.fin"
        const CheckState transition_prev_status = prev_status.Some._0;

        #line 343 "src/obdh/pus/services/service12.fin"
        CPUSService12__add_monitoring_transition(termina__ev, self, PMONID, fault_info, new_status, transition_prev_status);

    } else
    {
        

    }

    #line 349 "src/obdh/pus/services/service12.fin"
    return outcome;

}

static _Bool CPUSService12__manage_interval_control(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID) {
    
    (void)termina__ev;

    #line 113 "src/obdh/pus/services/service12.fin"
    _Bool check_due = false;

    #line 115 "src/obdh/pus/services/service12.fin"
    self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].interval_control = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].interval_control + 1U;

    #line 117 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].interval_control >= self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].interval) {
        
        #line 120 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].interval_control = 0U;

        #line 121 "src/obdh/pus/services/service12.fin"
        check_due = true;

    }

    #line 125 "src/obdh/pus/services/service12.fin"
    return check_due;

}

static MonitoringOutcome CPUSService12__manage_param_above_upper_limit(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID) {
    
    #line 354 "src/obdh/pus/services/service12.fin"
    MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoEvent };

    #line 358 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamLimitCheck) {
        
        #line 358 "src/obdh/pus/services/service12.fin"
        const ParamLimitCheckDefinition check_definition = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamLimitCheck._0;

        #line 360 "src/obdh/pus/services/service12.fin"
        ParamOutOfLimitInfo fault_info = { .PID = 0U, .PID_limit = 0U, .PID_value = 0U };

        #line 364 "src/obdh/pus/services/service12.fin"
        fault_info.PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

        #line 365 "src/obdh/pus/services/service12.fin"
        fault_info.PID_limit = check_definition.high_limit;

        #line 367 "src/obdh/pus/services/service12.fin"
        DataPoolItem type = sys_data_pool_get_item(fault_info.PID);

        #line 368 "src/obdh/pus/services/service12.fin"
        _Bool valid_PID = true;

        #line 372 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U32Item) {
            
            #line 372 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U32Item._0;

            #line 373 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        } else
        #line 375 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U8Item) {
            
            #line 375 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U8Item._0;

            #line 376 "src/obdh/pus/services/service12.fin"
            uint8_t value = 0U;

            #line 377 "src/obdh/pus/services/service12.fin"
            value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

            #line 378 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = (uint32_t)value;

        } else
        {
            
            #line 381 "src/obdh/pus/services/service12.fin"
            valid_PID = false;

        }

        #line 385 "src/obdh/pus/services/service12.fin"
        const CheckLimitsResult check_status = { ._variant = CheckLimitsResult__MonitorAboveHighLimit };

        #line 386 "src/obdh/pus/services/service12.fin"
        const CheckState new_status = { ._variant = CheckState__ParamLimitStatus, .ParamLimitStatus = { ._0 = { ._variant = Option__Some, .Some = { ._0 = check_status } } } };

        #line 387 "src/obdh/pus/services/service12.fin"
        Option__CheckState prev_status = CPUSService12__manage_new_status(termina__ev, self, PMONID, new_status);

        #line 390 "src/obdh/pus/services/service12.fin"
        if (prev_status._variant == Option__Some) {
            
            #line 390 "src/obdh/pus/services/service12.fin"
            const CheckState transition_prev_status = prev_status.Some._0;

            #line 391 "src/obdh/pus/services/service12.fin"
            const FaultInfo event_fault_info = { ._variant = FaultInfo__ParamOutOfLimit, .ParamOutOfLimit = { ._0 = fault_info } };

            #line 392 "src/obdh/pus/services/service12.fin"
            CPUSService12__add_monitoring_transition(termina__ev, self, PMONID, &event_fault_info, new_status, transition_prev_status);

            #line 393 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__EventTriggered;
            #line 393 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._0 = check_definition.high_limit_evID;
            #line 393 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._1 = event_fault_info;

        } else
        {
            

        }

        #line 400 "src/obdh/pus/services/service12.fin"
        if (valid_PID == false) {
            
            #line 401 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__NoReport;

        }

    } else
    {
        
        #line 406 "src/obdh/pus/services/service12.fin"
        outcome._variant = MonitoringOutcome__NoReport;

    }

    #line 411 "src/obdh/pus/services/service12.fin"
    return outcome;

}

static MonitoringOutcome CPUSService12__manage_param_below_lower_limit(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID) {
    
    #line 416 "src/obdh/pus/services/service12.fin"
    MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoEvent };

    #line 420 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamLimitCheck) {
        
        #line 420 "src/obdh/pus/services/service12.fin"
        const ParamLimitCheckDefinition check_definition = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamLimitCheck._0;

        #line 422 "src/obdh/pus/services/service12.fin"
        ParamOutOfLimitInfo fault_info = { .PID = 0U, .PID_limit = 0U, .PID_value = 0U };

        #line 426 "src/obdh/pus/services/service12.fin"
        fault_info.PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

        #line 427 "src/obdh/pus/services/service12.fin"
        fault_info.PID_limit = check_definition.low_limit;

        #line 429 "src/obdh/pus/services/service12.fin"
        DataPoolItem type = sys_data_pool_get_item(fault_info.PID);

        #line 430 "src/obdh/pus/services/service12.fin"
        _Bool valid_PID = true;

        #line 434 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U32Item) {
            
            #line 434 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U32Item._0;

            #line 435 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        } else
        #line 437 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U8Item) {
            
            #line 437 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U8Item._0;

            #line 438 "src/obdh/pus/services/service12.fin"
            uint8_t value = 0U;

            #line 439 "src/obdh/pus/services/service12.fin"
            value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

            #line 440 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = (uint32_t)value;

        } else
        {
            
            #line 443 "src/obdh/pus/services/service12.fin"
            valid_PID = false;

        }

        #line 447 "src/obdh/pus/services/service12.fin"
        const CheckLimitsResult check_status = { ._variant = CheckLimitsResult__MonitorBelowLowLimit };

        #line 448 "src/obdh/pus/services/service12.fin"
        const CheckState new_status = { ._variant = CheckState__ParamLimitStatus, .ParamLimitStatus = { ._0 = { ._variant = Option__Some, .Some = { ._0 = check_status } } } };

        #line 449 "src/obdh/pus/services/service12.fin"
        Option__CheckState prev_status = CPUSService12__manage_new_status(termina__ev, self, PMONID, new_status);

        #line 452 "src/obdh/pus/services/service12.fin"
        if (prev_status._variant == Option__Some) {
            
            #line 452 "src/obdh/pus/services/service12.fin"
            const CheckState transition_prev_status = prev_status.Some._0;

            #line 453 "src/obdh/pus/services/service12.fin"
            const FaultInfo event_fault_info = { ._variant = FaultInfo__ParamOutOfLimit, .ParamOutOfLimit = { ._0 = fault_info } };

            #line 454 "src/obdh/pus/services/service12.fin"
            CPUSService12__add_monitoring_transition(termina__ev, self, PMONID, &event_fault_info, new_status, transition_prev_status);

            #line 455 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__EventTriggered;
            #line 455 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._0 = check_definition.low_limit_evID;
            #line 455 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._1 = event_fault_info;

        } else
        {
            

        }

        #line 462 "src/obdh/pus/services/service12.fin"
        if (valid_PID == false) {
            
            #line 463 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__NoReport;

        }

    } else
    {
        
        #line 468 "src/obdh/pus/services/service12.fin"
        outcome._variant = MonitoringOutcome__NoReport;

    }

    #line 472 "src/obdh/pus/services/service12.fin"
    return outcome;

}

static MonitoringOutcome CPUSService12__manage_param_within_limits(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID, const FaultInfo * const fault_info) {
    
    #line 477 "src/obdh/pus/services/service12.fin"
    const MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoEvent };

    #line 479 "src/obdh/pus/services/service12.fin"
    CheckLimitsResult within_limits = { ._variant = CheckLimitsResult__MonitorWithinLimits };

    #line 480 "src/obdh/pus/services/service12.fin"
    CheckState new_status = { ._variant = CheckState__ParamLimitStatus, .ParamLimitStatus = { ._0 = { ._variant = Option__Some, .Some = { ._0 = within_limits } } } };

    #line 481 "src/obdh/pus/services/service12.fin"
    const CheckState current_status = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].current_state;

    #line 483 "src/obdh/pus/services/service12.fin"
    if (are_status_equal(new_status, current_status) == false) {
        
        #line 485 "src/obdh/pus/services/service12.fin"
        Option__CheckState prev_status = CPUSService12__manage_new_status(termina__ev, self, PMONID, new_status);

        #line 488 "src/obdh/pus/services/service12.fin"
        if (prev_status._variant == Option__Some) {
            
            #line 488 "src/obdh/pus/services/service12.fin"
            const CheckState transition_prev_status = prev_status.Some._0;

            #line 489 "src/obdh/pus/services/service12.fin"
            CPUSService12__add_monitoring_transition(termina__ev, self, PMONID, fault_info, new_status, transition_prev_status);

        } else
        {
            

        }

    }

    #line 496 "src/obdh/pus/services/service12.fin"
    return outcome;

}

static MonitoringOutcome CPUSService12__manage_unexpected_value(const termina__event_t * const termina__ev, CPUSService12 * const self, const uint16_t PMONID) {
    
    #line 269 "src/obdh/pus/services/service12.fin"
    MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoEvent };

    #line 273 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition._variant == MonitorDefinition__ParamValueCheck) {
        
        #line 273 "src/obdh/pus/services/service12.fin"
        const ParamValueCheckDefinition check_definition = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].definition.ParamValueCheck._0;

        #line 275 "src/obdh/pus/services/service12.fin"
        ParamFaultValueInfo fault_info = { .PID = 0U, .PID_expected_value = 0U, .PID_mask = 0U, .PID_value = 0U };

        #line 280 "src/obdh/pus/services/service12.fin"
        fault_info.PID = self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].PID;

        #line 281 "src/obdh/pus/services/service12.fin"
        fault_info.PID_expected_value = check_definition.expected_value;

        #line 282 "src/obdh/pus/services/service12.fin"
        fault_info.PID_mask = check_definition.mask_value;

        #line 284 "src/obdh/pus/services/service12.fin"
        DataPoolItem type = sys_data_pool_get_item(fault_info.PID);

        #line 285 "src/obdh/pus/services/service12.fin"
        _Bool valid_PID = true;

        #line 289 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U32Item) {
            
            #line 289 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U32Item._0;

            #line 290 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = atomic_load(&self->system_data_pool_u32[termina__check__array_index(12U, sdp_index)]);

        } else
        #line 292 "src/obdh/pus/services/service12.fin"
        if (type._variant == DataPoolItem__U8Item) {
            
            #line 292 "src/obdh/pus/services/service12.fin"
            const size_t sdp_index = type.U8Item._0;

            #line 293 "src/obdh/pus/services/service12.fin"
            uint8_t value = 0U;

            #line 294 "src/obdh/pus/services/service12.fin"
            value = atomic_load(&self->system_data_pool_u8[termina__check__array_index(18U, sdp_index)]);

            #line 295 "src/obdh/pus/services/service12.fin"
            fault_info.PID_value = (uint32_t)value;

        } else
        {
            
            #line 299 "src/obdh/pus/services/service12.fin"
            valid_PID = false;

        }

        #line 303 "src/obdh/pus/services/service12.fin"
        const CheckValueResult check_status = { ._variant = CheckValueResult__MonitorValueUnexpected };

        #line 304 "src/obdh/pus/services/service12.fin"
        const CheckState new_status = { ._variant = CheckState__ParamValueStatus, .ParamValueStatus = { ._0 = { ._variant = Option__Some, .Some = { ._0 = check_status } } } };

        #line 305 "src/obdh/pus/services/service12.fin"
        Option__CheckState prev_status = CPUSService12__manage_new_status(termina__ev, self, PMONID, new_status);

        #line 308 "src/obdh/pus/services/service12.fin"
        if (prev_status._variant == Option__Some) {
            
            #line 308 "src/obdh/pus/services/service12.fin"
            const CheckState transition_prev_status = prev_status.Some._0;

            #line 309 "src/obdh/pus/services/service12.fin"
            const FaultInfo event_fault_info = { ._variant = FaultInfo__ParamFaultValue, .ParamFaultValue = { ._0 = fault_info } };

            #line 310 "src/obdh/pus/services/service12.fin"
            CPUSService12__add_monitoring_transition(termina__ev, self, PMONID, &event_fault_info, new_status, transition_prev_status);

            #line 311 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__EventTriggered;
            #line 311 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._0 = check_definition.EvID;
            #line 311 "src/obdh/pus/services/service12.fin"
            outcome.EventTriggered._1 = event_fault_info;

        } else
        {
            

        }

        #line 318 "src/obdh/pus/services/service12.fin"
        if (valid_PID == false) {
            
            #line 319 "src/obdh/pus/services/service12.fin"
            outcome._variant = MonitoringOutcome__NoReport;

        }

    } else
    {
        
        #line 324 "src/obdh/pus/services/service12.fin"
        outcome._variant = MonitoringOutcome__NoReport;

    }

    #line 328 "src/obdh/pus/services/service12.fin"
    return outcome;

}

void CPUSService12__do_monitoring(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t PMONID, uint16_t * const evID, FaultInfo * const fault_info, _Bool * const event_triggered) {
    
    #line 629 "src/obdh/pus/services/service12.fin"
    CPUSService12 * self = (CPUSService12 *)termina__this;

    #line 629 "src/obdh/pus/services/service12.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 632 "src/obdh/pus/services/service12.fin"
    MonitoringOutcome outcome = { ._variant = MonitoringOutcome__NoReport };

    #line 634 "src/obdh/pus/services/service12.fin"
    if (is_PMONID_valid(PMONID)) {
        
        #line 636 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)PMONID)].enabled == true) {
            
            #line 638 "src/obdh/pus/services/service12.fin"
            if (CPUSService12__manage_interval_control(termina__ev, self, PMONID)) {
                
                #line 640 "src/obdh/pus/services/service12.fin"
                if (CPUSService12__is_limits_monitoring(termina__ev, self, PMONID)) {
                    
                    #line 642 "src/obdh/pus/services/service12.fin"
                    CheckLimitsResult limits_monitoring_status = CPUSService12__check_PID_status_limits_monitoring(termina__ev, self, PMONID);

                    #line 645 "src/obdh/pus/services/service12.fin"
                    if (limits_monitoring_status._variant == CheckLimitsResult__MonitorAboveHighLimit) {
                        
                        #line 647 "src/obdh/pus/services/service12.fin"
                        outcome = CPUSService12__manage_param_above_upper_limit(termina__ev, self, PMONID);

                    } else
                    #line 649 "src/obdh/pus/services/service12.fin"
                    if (limits_monitoring_status._variant == CheckLimitsResult__MonitorBelowLowLimit) {
                        
                        #line 651 "src/obdh/pus/services/service12.fin"
                        outcome = CPUSService12__manage_param_below_lower_limit(termina__ev, self, PMONID);

                    } else
                    {
                        
                        #line 656 "src/obdh/pus/services/service12.fin"
                        outcome = CPUSService12__manage_param_within_limits(termina__ev, self, PMONID, fault_info);

                    }

                } else
                #line 661 "src/obdh/pus/services/service12.fin"
                if (CPUSService12__is_expected_value_monitoring(termina__ev, self, PMONID)) {
                    
                    #line 663 "src/obdh/pus/services/service12.fin"
                    CheckValueResult exp_value_monitoring_status = CPUSService12__check_PID_status_exp_val_monitoring(termina__ev, self, PMONID);

                    #line 666 "src/obdh/pus/services/service12.fin"
                    if (exp_value_monitoring_status._variant == CheckValueResult__MonitorValueUnexpected) {
                        
                        #line 668 "src/obdh/pus/services/service12.fin"
                        outcome = CPUSService12__manage_unexpected_value(termina__ev, self, PMONID);

                    } else
                    {
                        
                        #line 672 "src/obdh/pus/services/service12.fin"
                        outcome = CPUSService12__manage_expected_value(termina__ev, self, PMONID, fault_info);

                    }

                } else
                {
                    

                }

            }

        }

    }

    #line 686 "src/obdh/pus/services/service12.fin"
    if (outcome._variant == MonitoringOutcome__EventTriggered) {
        
        #line 686 "src/obdh/pus/services/service12.fin"
        const uint16_t event_evID = outcome.EventTriggered._0;
        #line 686 "src/obdh/pus/services/service12.fin"
        const FaultInfo event_fault_info = outcome.EventTriggered._1;

        #line 687 "src/obdh/pus/services/service12.fin"
        *evID = event_evID;

        #line 688 "src/obdh/pus/services/service12.fin"
        *fault_info = event_fault_info;

        #line 689 "src/obdh/pus/services/service12.fin"
        *event_triggered = true;

    } else
    #line 691 "src/obdh/pus/services/service12.fin"
    if (outcome._variant == MonitoringOutcome__NoEvent) {
        
        #line 692 "src/obdh/pus/services/service12.fin"
        *event_triggered = false;

    } else
    {
        

    }

    #line 698 "src/obdh/pus/services/service12.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 698 "src/obdh/pus/services/service12.fin"
    return;

}

static Status__PUSService12Error CPUSService12__exec12_1TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    #line 743 "src/obdh/pus/services/service12.fin"
    Status__PUSService12Error status = { ._variant = Status__Success };

    #line 745 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_1_2_6.N != 1U) {
        
        #line 747 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 747 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__NumOfInstrNotValid;
        #line 747 "src/obdh/pus/services/service12.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data_1_2_6.N;

    } else
    {
        
        #line 750 "src/obdh/pus/services/service12.fin"
        size_t PMONID = (size_t)tc_request->tc_data_1_2_6.PMONID;

        #line 752 "src/obdh/pus/services/service12.fin"
        if (is_PMONID_valid(tc_request->tc_data_1_2_6.PMONID)) {
            
            #line 754 "src/obdh/pus/services/service12.fin"
            if ((self->param_mon_config_table[termina__check__array_index(16U, PMONID)].type._variant == MonitorCheckType__Free) == false) {
                
                #line 756 "src/obdh/pus/services/service12.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

                #line 761 "src/obdh/pus/services/service12.fin"
                self->param_mon_config_table[termina__check__array_index(16U, PMONID)].enabled = true;

                #line 762 "src/obdh/pus/services/service12.fin"
                self->param_mon_config_table[termina__check__array_index(16U, PMONID)].interval_control = 0U;

                #line 763 "src/obdh/pus/services/service12.fin"
                self->param_mon_config_table[termina__check__array_index(16U, PMONID)].repetition_control = 0U;

                #line 765 "src/obdh/pus/services/service12.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            } else
            {
                
                #line 772 "src/obdh/pus/services/service12.fin"
                status._variant = Status__Failure;
                #line 772 "src/obdh/pus/services/service12.fin"
                status.Failure._0._variant = PUSService12Error__PMONUndefined;
                #line 772 "src/obdh/pus/services/service12.fin"
                status.Failure._0.PMONUndefined._0 = tc_request->tc_data_1_2_6.PMONID;

            }

        } else
        {
            
            #line 778 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 778 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__PMONIDInvalid;
            #line 778 "src/obdh/pus/services/service12.fin"
            status.Failure._0.PMONIDInvalid._0 = tc_request->tc_data_1_2_6.PMONID;

        }

    }

    #line 783 "src/obdh/pus/services/service12.fin"
    return status;

}

static void CPUSService12__set_unchecked(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    (void)termina__ev;

    #line 718 "src/obdh/pus/services/service12.fin"
    size_t valid_PMONID = (size_t)tc_request->tc_data_1_2_6.PMONID;

    #line 722 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].type._variant == MonitorCheckType__ExpectedValue) {
        
        #line 723 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state._variant = CheckState__ParamValueStatus;
        #line 723 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state.ParamValueStatus._0._variant = Option__None;

    } else
    #line 725 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].type._variant == MonitorCheckType__Limits) {
        
        #line 726 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state._variant = CheckState__ParamLimitStatus;
        #line 726 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state.ParamLimitStatus._0._variant = Option__None;

    } else
    #line 728 "src/obdh/pus/services/service12.fin"
    if (self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].type._variant == MonitorCheckType__Delta) {
        
        #line 729 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state._variant = CheckState__ParamDeltaStatus;
        #line 729 "src/obdh/pus/services/service12.fin"
        self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state.ParamDeltaStatus._0._variant = Option__None;

    } else
    {
        

    }

    #line 736 "src/obdh/pus/services/service12.fin"
    self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].temp_state = self->param_mon_config_table[termina__check__array_index(16U, valid_PMONID)].current_state;

    #line 738 "src/obdh/pus/services/service12.fin"
    return;

}

static Status__PUSService12Error CPUSService12__exec12_2TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    #line 788 "src/obdh/pus/services/service12.fin"
    Status__PUSService12Error status = { ._variant = Status__Success };

    #line 791 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_1_2_6.N != 1U) {
        
        #line 793 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 793 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__NumOfInstrNotValid;
        #line 793 "src/obdh/pus/services/service12.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data_1_2_6.N;

    } else
    {
        
        #line 797 "src/obdh/pus/services/service12.fin"
        if (is_PMONID_valid(tc_request->tc_data_1_2_6.PMONID)) {
            
            #line 799 "src/obdh/pus/services/service12.fin"
            if ((self->param_mon_config_table[termina__check__array_index(16U, (size_t)tc_request->tc_data_1_2_6.PMONID)].type._variant == MonitorCheckType__Free) == false) {
                
                #line 801 "src/obdh/pus/services/service12.fin"
                self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

                #line 806 "src/obdh/pus/services/service12.fin"
                self->param_mon_config_table[termina__check__array_index(16U, (size_t)tc_request->tc_data_1_2_6.PMONID)].enabled = false;

                #line 807 "src/obdh/pus/services/service12.fin"
                CPUSService12__set_unchecked(termina__ev, self, tc_request);

                #line 809 "src/obdh/pus/services/service12.fin"
                self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            } else
            {
                
                #line 817 "src/obdh/pus/services/service12.fin"
                status._variant = Status__Failure;
                #line 817 "src/obdh/pus/services/service12.fin"
                status.Failure._0._variant = PUSService12Error__PMONUndefined;
                #line 817 "src/obdh/pus/services/service12.fin"
                status.Failure._0.PMONUndefined._0 = tc_request->tc_data_1_2_6.PMONID;

            }

        } else
        {
            
            #line 823 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 823 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__PMONIDInvalid;
            #line 823 "src/obdh/pus/services/service12.fin"
            status.Failure._0.PMONIDInvalid._0 = tc_request->tc_data_1_2_6.PMONID;

        }

    }

    #line 828 "src/obdh/pus/services/service12.fin"
    return status;

}

static Status__PUSService12Error CPUSService12__exec12_5TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    #line 873 "src/obdh/pus/services/service12.fin"
    Status__PUSService12Error status = { ._variant = Status__Success };

    #line 876 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_5.N != 1U) {
        
        #line 878 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 878 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__NumOfInstrNotValid;
        #line 878 "src/obdh/pus/services/service12.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data_5.N;

    } else
    #line 880 "src/obdh/pus/services/service12.fin"
    if (sys_data_pool_is_valid_PID(tc_request->tc_data_5.mon_config.PID) == false) {
        
        #line 882 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 882 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__PIDNotValid;
        #line 882 "src/obdh/pus/services/service12.fin"
        status.Failure._0.PIDNotValid._0 = tc_request->tc_data_5.mon_config.PID;

    } else
    #line 884 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_5.mon_config.type._variant == MonitorCheckType__Limits) {
        
        #line 886 "src/obdh/pus/services/service12.fin"
        if (is_valid_check_limit_def(&tc_request->tc_data_5.mon_config.definition)) {
            
            #line 888 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            #line 893 "src/obdh/pus/services/service12.fin"
            CPUSService12__add_valid_mng_mon_def(termina__ev, self, tc_request);

            #line 895 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 902 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 902 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__PMONDefinitionInvalid;
            #line 902 "src/obdh/pus/services/service12.fin"
            status.Failure._0.PMONDefinitionInvalid._0 = tc_request->tc_data_5.PMONID;

        }

    } else
    #line 906 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_5.mon_config.type._variant == MonitorCheckType__ExpectedValue) {
        
        #line 908 "src/obdh/pus/services/service12.fin"
        self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        #line 913 "src/obdh/pus/services/service12.fin"
        CPUSService12__add_valid_mng_mon_def(termina__ev, self, tc_request);

        #line 915 "src/obdh/pus/services/service12.fin"
        self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

    } else
    {
        
        #line 921 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 921 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__PMONDefinitionInvalid;
        #line 921 "src/obdh/pus/services/service12.fin"
        status.Failure._0.PMONDefinitionInvalid._0 = tc_request->tc_data_5.PMONID;

    }

    #line 925 "src/obdh/pus/services/service12.fin"
    return status;

}

static Status__PUSService12Error CPUSService12__exec12_6TC(const termina__event_t * const termina__ev, CPUSService12 * const self, const PS12TCRequest * const tc_request) {
    
    #line 931 "src/obdh/pus/services/service12.fin"
    Status__PUSService12Error status = { ._variant = Status__Success };

    #line 933 "src/obdh/pus/services/service12.fin"
    if (tc_request->tc_data_1_2_6.N != 1U) {
        
        #line 935 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 935 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__NumOfInstrNotValid;
        #line 935 "src/obdh/pus/services/service12.fin"
        status.Failure._0.NumOfInstrNotValid._0 = tc_request->tc_data_1_2_6.N;

    } else
    {
        
        #line 939 "src/obdh/pus/services/service12.fin"
        MonitorCheckType PMON_type = get_check_type((uint8_t)tc_request->tc_data_1_2_6.PMONID);

        #line 941 "src/obdh/pus/services/service12.fin"
        if (PMON_type._variant == MonitorCheckType__Free) {
            
            #line 943 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 943 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__PMONUndefined;
            #line 943 "src/obdh/pus/services/service12.fin"
            status.Failure._0.PMONUndefined._0 = tc_request->tc_data_1_2_6.PMONID;

        } else
        #line 945 "src/obdh/pus/services/service12.fin"
        if (self->param_mon_config_table[termina__check__array_index(16U, (size_t)tc_request->tc_data_1_2_6.PMONID)].enabled == false) {
            
            #line 947 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.notify_tm_1_3(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

            #line 952 "src/obdh/pus/services/service12.fin"
            self->param_mon_config_table[termina__check__array_index(16U, (size_t)tc_request->tc_data_1_2_6.PMONID)].type._variant = MonitorCheckType__Free;

            #line 954 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.notify_tm_1_7(termina__ev, self->pus_service_1._that, tc_request->packet_id, tc_request->packet_seq_ctrl, tc_request->flags_ack);

        } else
        {
            
            #line 961 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 961 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__PMONEnabled;
            #line 961 "src/obdh/pus/services/service12.fin"
            status.Failure._0.PMONEnabled._0 = tc_request->tc_data_1_2_6.PMONID;

        }

    }

    #line 968 "src/obdh/pus/services/service12.fin"
    return status;

}

void CPUSService12__exec_tc(const termina__event_t * const termina__ev, void * const termina__this, TCHandler * const tc_handler) {
    
    #line 973 "src/obdh/pus/services/service12.fin"
    CPUSService12 * self = (CPUSService12 *)termina__this;

    #line 973 "src/obdh/pus/services/service12.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 975 "src/obdh/pus/services/service12.fin"
    Status__PUSService12Error status = { ._variant = Status__Success };

    #line 976 "src/obdh/pus/services/service12.fin"
    Status__TCHandlerError tc_data_status = { ._variant = Status__Success };

    #line 977 "src/obdh/pus/services/service12.fin"
    uint8_t subtype = tc_handler->df_header.subtype;

    #line 978 "src/obdh/pus/services/service12.fin"
    PS12TCRequest tc_request = { .flags_ack = 0U, .packet_id = 0U, .packet_seq_ctrl = 0U, .tc_data_1_2_6 = { .N = 0U, .PMONID = 0U }, .tc_data_5 = { .N = 0U, .PMONID = 0U, .mon_config = { .PID = 0U, .current_state = { ._variant = CheckState__Unselected }, .definition = { ._variant = MonitorDefinition__Unselected }, .enabled = false, .interval = 0U, .interval_control = 0U, .repetition = 0U, .repetition_control = 0U, .temp_state = { ._variant = CheckState__Unselected }, .transition_obt = { .finetime = 0U, .seconds = 0U }, .type = { ._variant = MonitorCheckType__Free } } }, .tc_num_bytes = 0U };

    #line 980 "src/obdh/pus/services/service12.fin"
    tc_request.packet_id = tc_handler->packet_header.packet_id;

    #line 981 "src/obdh/pus/services/service12.fin"
    tc_request.packet_seq_ctrl = tc_handler->packet_header.packet_seq_ctrl;

    #line 982 "src/obdh/pus/services/service12.fin"
    tc_request.flags_ack = tc_handler->df_header.flag_ver_ack;

    #line 983 "src/obdh/pus/services/service12.fin"
    tc_request.tc_num_bytes = tc_handler->tc_descriptor.tc_num_bytes;

    #line 985 "src/obdh/pus/services/service12.fin"
    if (subtype == 1U || subtype == 2U || subtype == 6U) {
        
        #line 987 "src/obdh/pus/services/service12.fin"
        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_data_1_2_6.N);

        #line 989 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 990 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.tc_data_1_2_6.PMONID);

        }

    } else
    #line 993 "src/obdh/pus/services/service12.fin"
    if (subtype == 5U) {
        
        #line 995 "src/obdh/pus/services/service12.fin"
        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_data_5.N);

        #line 997 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 998 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.tc_data_5.PMONID);

        }

        #line 1000 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 1001 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &tc_request.tc_data_5.mon_config.PID);

        }

        #line 1003 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 1004 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_data_5.mon_config.interval);

        }

        #line 1006 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 1007 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &tc_request.tc_data_5.mon_config.repetition);

        }

        #line 1009 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 1010 "src/obdh/pus/services/service12.fin"
            uint8_t aux = 0U;

            #line 1011 "src/obdh/pus/services/service12.fin"
            tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &aux);

            #line 1012 "src/obdh/pus/services/service12.fin"
            tc_request.tc_data_5.mon_config.type = get_check_type(aux);

        }

        #line 1015 "src/obdh/pus/services/service12.fin"
        if (tc_data_status._variant == Status__Success) {
            
            #line 1017 "src/obdh/pus/services/service12.fin"
            if (tc_request.tc_data_5.mon_config.type._variant == MonitorCheckType__ExpectedValue) {
                
                #line 1019 "src/obdh/pus/services/service12.fin"
                ParamValueCheckDefinition value_def = { .EvID = 0U, .expected_value = 0U, .mask_value = 0U };

                #line 1025 "src/obdh/pus/services/service12.fin"
                DataPoolItem type = sys_data_pool_get_item(tc_request.tc_data_5.mon_config.PID);

                #line 1029 "src/obdh/pus/services/service12.fin"
                if (type._variant == DataPoolItem__U8Item) {
                    
                    #line 1031 "src/obdh/pus/services/service12.fin"
                    uint8_t mask = 0U;

                    #line 1034 "src/obdh/pus/services/service12.fin"
                    tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &mask);

                    #line 1035 "src/obdh/pus/services/service12.fin"
                    value_def.mask_value = (uint32_t)mask;

                    #line 1038 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1039 "src/obdh/pus/services/service12.fin"
                        uint8_t expected_value = 0U;

                        #line 1040 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &expected_value);

                        #line 1041 "src/obdh/pus/services/service12.fin"
                        value_def.expected_value = (uint32_t)expected_value;

                    }

                    #line 1045 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1046 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &value_def.EvID);

                    }

                    #line 1049 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition._variant = MonitorDefinition__ParamValueCheck;
                    #line 1049 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition.ParamValueCheck._0 = value_def;

                } else
                #line 1052 "src/obdh/pus/services/service12.fin"
                if (type._variant == DataPoolItem__U32Item) {
                    
                    #line 1055 "src/obdh/pus/services/service12.fin"
                    tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &value_def.mask_value);

                    #line 1058 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1059 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &value_def.expected_value);

                    }

                    #line 1063 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1064 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &value_def.EvID);

                    }

                    #line 1067 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition._variant = MonitorDefinition__ParamValueCheck;
                    #line 1067 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition.ParamValueCheck._0 = value_def;

                } else
                {
                    
                    #line 1071 "src/obdh/pus/services/service12.fin"
                    status._variant = Status__Failure;
                    #line 1071 "src/obdh/pus/services/service12.fin"
                    status.Failure._0._variant = PUSService12Error__PIDNotValid;
                    #line 1071 "src/obdh/pus/services/service12.fin"
                    status.Failure._0.PIDNotValid._0 = tc_request.tc_data_5.mon_config.PID;

                }

            } else
            #line 1076 "src/obdh/pus/services/service12.fin"
            if (tc_request.tc_data_5.mon_config.type._variant == MonitorCheckType__Limits) {
                
                #line 1078 "src/obdh/pus/services/service12.fin"
                ParamLimitCheckDefinition limits_def = { .high_limit = 0U, .high_limit_evID = 0U, .low_limit = 0U, .low_limit_evID = 0U };

                #line 1085 "src/obdh/pus/services/service12.fin"
                DataPoolItem type = sys_data_pool_get_item(tc_request.tc_data_5.mon_config.PID);

                #line 1089 "src/obdh/pus/services/service12.fin"
                if (type._variant == DataPoolItem__U8Item) {
                    
                    #line 1091 "src/obdh/pus/services/service12.fin"
                    uint8_t low_limit = 0U;

                    #line 1094 "src/obdh/pus/services/service12.fin"
                    tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &low_limit);

                    #line 1095 "src/obdh/pus/services/service12.fin"
                    limits_def.low_limit = (uint32_t)low_limit;

                    #line 1098 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1099 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &limits_def.low_limit_evID);

                    }

                    #line 1103 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1104 "src/obdh/pus/services/service12.fin"
                        uint8_t high_limit = 0U;

                        #line 1105 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u8_appdata_field(tc_handler, &high_limit);

                        #line 1106 "src/obdh/pus/services/service12.fin"
                        limits_def.high_limit = (uint32_t)high_limit;

                    }

                    #line 1110 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1111 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &limits_def.high_limit_evID);

                    }

                    #line 1114 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition._variant = MonitorDefinition__ParamLimitCheck;
                    #line 1114 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition.ParamLimitCheck._0 = limits_def;

                } else
                #line 1117 "src/obdh/pus/services/service12.fin"
                if (type._variant == DataPoolItem__U32Item) {
                    
                    #line 1120 "src/obdh/pus/services/service12.fin"
                    tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &limits_def.low_limit);

                    #line 1123 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1124 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &limits_def.low_limit_evID);

                    }

                    #line 1128 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1129 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u32_appdata_field(tc_handler, &limits_def.high_limit);

                    }

                    #line 1133 "src/obdh/pus/services/service12.fin"
                    if (tc_data_status._variant == Status__Success) {
                        
                        #line 1134 "src/obdh/pus/services/service12.fin"
                        tc_data_status = tc_handler_get_u16_appdata_field(tc_handler, &limits_def.high_limit_evID);

                    }

                    #line 1137 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition._variant = MonitorDefinition__ParamLimitCheck;
                    #line 1137 "src/obdh/pus/services/service12.fin"
                    tc_request.tc_data_5.mon_config.definition.ParamLimitCheck._0 = limits_def;

                } else
                {
                    
                    #line 1141 "src/obdh/pus/services/service12.fin"
                    status._variant = Status__Failure;
                    #line 1141 "src/obdh/pus/services/service12.fin"
                    status.Failure._0._variant = PUSService12Error__PIDNotValid;
                    #line 1141 "src/obdh/pus/services/service12.fin"
                    status.Failure._0.PIDNotValid._0 = tc_request.tc_data_5.mon_config.PID;

                }

            } else
            {
                

            }

        }

    } else
    {
        

    }

    #line 1157 "src/obdh/pus/services/service12.fin"
    if (tc_data_status._variant == Status__Failure) {
        
        #line 1158 "src/obdh/pus/services/service12.fin"
        status._variant = Status__Failure;
        #line 1158 "src/obdh/pus/services/service12.fin"
        status.Failure._0._variant = PUSService12Error__AppDataOutOfRange;
        #line 1158 "src/obdh/pus/services/service12.fin"
        status.Failure._0.AppDataOutOfRange._0 = tc_request.tc_num_bytes;

    }

    #line 1161 "src/obdh/pus/services/service12.fin"
    if (status._variant == Status__Success) {
        
        #line 1163 "src/obdh/pus/services/service12.fin"
        if (subtype == 1U) {
            
            #line 1165 "src/obdh/pus/services/service12.fin"
            status = CPUSService12__exec12_1TC(termina__ev, self, &tc_request);

        } else
        #line 1167 "src/obdh/pus/services/service12.fin"
        if (subtype == 2U) {
            
            #line 1169 "src/obdh/pus/services/service12.fin"
            status = CPUSService12__exec12_2TC(termina__ev, self, &tc_request);

        } else
        #line 1171 "src/obdh/pus/services/service12.fin"
        if (subtype == 5U) {
            
            #line 1173 "src/obdh/pus/services/service12.fin"
            status = CPUSService12__exec12_5TC(termina__ev, self, &tc_request);

        } else
        #line 1175 "src/obdh/pus/services/service12.fin"
        if (subtype == 6U) {
            
            #line 1177 "src/obdh/pus/services/service12.fin"
            status = CPUSService12__exec12_6TC(termina__ev, self, &tc_request);

        } else
        {
            
            #line 1181 "src/obdh/pus/services/service12.fin"
            status._variant = Status__Failure;
            #line 1181 "src/obdh/pus/services/service12.fin"
            status.Failure._0._variant = PUSService12Error__ErrorInAcceptance;

        }

    }

    #line 1188 "src/obdh/pus/services/service12.fin"
    if (status._variant == Status__Success) {
        

    } else
    {
        
        #line 1191 "src/obdh/pus/services/service12.fin"
        const PUSService12Error error = status.Failure._0;

        #line 1195 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__ErrorInAcceptance) {
            
            #line 1197 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_error_in_acceptance(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl);

        } else
        #line 1202 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__AppDataOutOfRange) {
            
            #line 1202 "src/obdh/pus/services/service12.fin"
            const size_t tc_num_bytes = error.AppDataOutOfRange._0;

            #line 1204 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_short_pack_length(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, tc_num_bytes);

        } else
        #line 1210 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__NumOfInstrNotValid) {
            
            #line 1210 "src/obdh/pus/services/service12.fin"
            const uint8_t N = error.NumOfInstrNotValid._0;

            #line 1212 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_num_of_instr_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, N);

        } else
        #line 1218 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__PIDNotValid) {
            
            #line 1218 "src/obdh/pus/services/service12.fin"
            const uint16_t PID = error.PIDNotValid._0;

            #line 1220 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_PID_not_valid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PID);

        } else
        #line 1226 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__PMONUndefined) {
            
            #line 1226 "src/obdh/pus/services/service12.fin"
            const uint16_t PMONID = error.PMONUndefined._0;

            #line 1228 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_PMON_undefined(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PMONID);

        } else
        #line 1234 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__PMONIDInvalid) {
            
            #line 1234 "src/obdh/pus/services/service12.fin"
            const uint16_t PMONID = error.PMONIDInvalid._0;

            #line 1236 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_PMONID_invalid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PMONID);

        } else
        #line 1242 "src/obdh/pus/services/service12.fin"
        if (error._variant == PUSService12Error__PMONDefinitionInvalid) {
            
            #line 1242 "src/obdh/pus/services/service12.fin"
            const uint16_t PMONID = error.PMONDefinitionInvalid._0;

            #line 1244 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_PMON_definition_invalid(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PMONID);

        } else
        {
            
            #line 1250 "src/obdh/pus/services/service12.fin"
            const uint16_t PMONID = error.PMONEnabled._0;

            #line 1252 "src/obdh/pus/services/service12.fin"
            self->pus_service_1.send_tm_1_4_PMON_enabled(termina__ev, self->pus_service_1._that, tc_request.packet_id, tc_request.packet_seq_ctrl, PMONID);

        }

    }

    #line 1263 "src/obdh/pus/services/service12.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1263 "src/obdh/pus/services/service12.fin"
    return;

}

void CPUSService12__is_PMON_enabled(const termina__event_t * const termina__ev, void * const termina__this, const size_t PMONID, _Bool * const is_enabled) {
    
    #line 701 "src/obdh/pus/services/service12.fin"
    CPUSService12 * self = (CPUSService12 *)termina__this;

    #line 701 "src/obdh/pus/services/service12.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 703 "src/obdh/pus/services/service12.fin"
    *is_enabled = false;

    #line 705 "src/obdh/pus/services/service12.fin"
    if (PMONID < 16U) {
        
        #line 707 "src/obdh/pus/services/service12.fin"
        if ((self->param_mon_config_table[PMONID].type._variant == MonitorCheckType__Free) == false) {
            
            #line 709 "src/obdh/pus/services/service12.fin"
            *is_enabled = self->param_mon_config_table[(size_t)PMONID].enabled;

        }

    }

    #line 713 "src/obdh/pus/services/service12.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 713 "src/obdh/pus/services/service12.fin"
    return;

}
