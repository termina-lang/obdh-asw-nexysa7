
#include "obdh/pus/services/service17/internal.h"

void build_tm_17_2(TMHandler * const p_tm_handler, const uint16_t tm_seq_counter, const CUCTime current_obt) {
    
    #line 40 "src/obdh/pus/services/service17/internal.fin"
    startup_tm(p_tm_handler);

    #line 41 "src/obdh/pus/services/service17/internal.fin"
    close_tm(p_tm_handler, 17U, 2U, tm_seq_counter, current_obt);

    #line 42 "src/obdh/pus/services/service17/internal.fin"
    return;

}
