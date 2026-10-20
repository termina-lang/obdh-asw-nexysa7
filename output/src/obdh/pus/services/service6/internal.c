
#include "obdh/pus/services/service6/internal.h"

Status__TMHandlerError build_tm_6_6(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const PS6TCRequest * const mem_data) {
    
    #line 44 "src/obdh/pus/services/service6/internal.fin"
    startup_tm(p_tm_handler);

    #line 45 "src/obdh/pus/services/service6/internal.fin"
    Status__TMHandlerError status = append_u8_appdata_field(p_tm_handler, mem_data->mem_id);

    #line 46 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 47 "src/obdh/pus/services/service6/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, 1U);

    }

    #line 49 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 50 "src/obdh/pus/services/service6/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, mem_data->address);

    }

    #line 52 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 53 "src/obdh/pus/services/service6/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, mem_data->length);

    }

    #line 55 "src/obdh/pus/services/service6/internal.fin"
    for (size_t i = 0U; i < 256U && (status._variant == Status__Success && i < (size_t)mem_data->length); i = i + 1U) {
        
        #line 56 "src/obdh/pus/services/service6/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, mem_data->data[i]);

    }

    #line 58 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 59 "src/obdh/pus/services/service6/internal.fin"
        close_tm(p_tm_handler, 6U, 6U, tm_seq_counter, current_obt);

    }

    #line 62 "src/obdh/pus/services/service6/internal.fin"
    return status;

}

Status__TMHandlerError build_tm_6_10(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt, const PS6TCRequest * const mem_data, const uint16_t checksum) {
    
    #line 68 "src/obdh/pus/services/service6/internal.fin"
    startup_tm(p_tm_handler);

    #line 69 "src/obdh/pus/services/service6/internal.fin"
    Status__TMHandlerError status = append_u8_appdata_field(p_tm_handler, mem_data->mem_id);

    #line 70 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 71 "src/obdh/pus/services/service6/internal.fin"
        status = append_u8_appdata_field(p_tm_handler, 1U);

    }

    #line 73 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 74 "src/obdh/pus/services/service6/internal.fin"
        status = append_u32_appdata_field(p_tm_handler, mem_data->address);

    }

    #line 76 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 77 "src/obdh/pus/services/service6/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, mem_data->length);

    }

    #line 79 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 80 "src/obdh/pus/services/service6/internal.fin"
        status = append_u16_appdata_field(p_tm_handler, checksum);

    }

    #line 82 "src/obdh/pus/services/service6/internal.fin"
    if (status._variant == Status__Success) {
        
        #line 83 "src/obdh/pus/services/service6/internal.fin"
        close_tm(p_tm_handler, 6U, 10U, tm_seq_counter, current_obt);

    }

    #line 86 "src/obdh/pus/services/service6/internal.fin"
    return status;

}
