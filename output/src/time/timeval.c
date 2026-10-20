
#include "time/timeval.h"

TimeVal substract_TimeVal(const TimeVal timeval1, const TimeVal timeval2) {
    
    #line 14 "src/time/timeval.fin"
    TimeVal result = { .tv_sec = 0U, .tv_usec = 0U };

    #line 16 "src/time/timeval.fin"
    if (timeval1.tv_usec < timeval2.tv_usec) {
        
        #line 17 "src/time/timeval.fin"
        result.tv_sec = (uint32_t)(timeval1.tv_sec - timeval2.tv_sec) - 1U;

        #line 18 "src/time/timeval.fin"
        result.tv_usec = (uint32_t)(1000000U - timeval2.tv_usec) + timeval1.tv_usec;

    } else
    {
        
        #line 20 "src/time/timeval.fin"
        result.tv_sec = timeval1.tv_sec - timeval2.tv_sec;

        #line 21 "src/time/timeval.fin"
        result.tv_usec = timeval1.tv_usec - timeval2.tv_usec;

    }

    #line 24 "src/time/timeval.fin"
    return result;

}
