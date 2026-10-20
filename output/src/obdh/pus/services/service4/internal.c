
#include "obdh/pus/services/service4/internal.h"

Status__TMHandlerError build_tm_4_2(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const size_t stats_index, const uint8_t N, const StatsConfig * const stats_config_table, const StatsDef param_stats[4U], const CUCTime current_obt) {
    
    #line 72 "src/obdh/pus/services/service4/internal.fin"
    startup_tm(p_tm_handler);

    #line 74 "src/obdh/pus/services/service4/internal.fin"
    Status__TMHandlerError status = append_u32_appdata_field(p_tm_handler, stats_config_table->start_time[termina__check__array_index(4U, stats_index)].seconds);

    #line 75 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 76 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, current_obt.seconds);

    }

    #line 78 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 79 "src/obdh/pus/services/service4/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, N);

    }

    #line 81 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 82 "src/obdh/pus/services/service4/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, stats_config_table->PID[termina__check__array_index(4U, stats_index)]);

    }

    #line 84 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 85 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].samples);

    }

    #line 87 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 88 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].max);

    }

    #line 90 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 91 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].max_obt.seconds);

    }

    #line 93 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 94 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].min);

    }

    #line 96 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 97 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].min_obt.seconds);

    }

    #line 99 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 100 "src/obdh/pus/services/service4/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, param_stats[termina__check__array_index(4U, stats_index)].mean_value);

    }

    #line 103 "src/obdh/pus/services/service4/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 104 "src/obdh/pus/services/service4/internal.fin"
        close_tm(p_tm_handler, 4U, 2U, tm_seq_counter, current_obt);

    }

    #line 107 "src/obdh/pus/services/service4/internal.fin"
    return status;

}
