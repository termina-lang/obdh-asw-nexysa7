
#include "obdh/system_data_pool.h"

DataPoolItem sys_data_pool_get_item(const uint16_t PID) {
    
    #line 39 "src/obdh/system_data_pool.fin"
    DataPoolItem item;

    #line 41 "src/obdh/system_data_pool.fin"
    if ((size_t)PID < 12U) {
        
        #line 43 "src/obdh/system_data_pool.fin"
        item._variant = DataPoolItem__U32Item;
        #line 43 "src/obdh/system_data_pool.fin"
        item.U32Item._0 = (size_t)PID;

    } else
    #line 45 "src/obdh/system_data_pool.fin"
    if ((size_t)PID < 30U) {
        
        #line 47 "src/obdh/system_data_pool.fin"
        item._variant = DataPoolItem__U8Item;
        #line 47 "src/obdh/system_data_pool.fin"
        item.U8Item._0 = (size_t)PID - 12U;

    } else
    {
        
        #line 51 "src/obdh/system_data_pool.fin"
        item._variant = DataPoolItem__NoValidPID;

    }

    #line 55 "src/obdh/system_data_pool.fin"
    return item;

}

_Bool sys_data_pool_is_valid_PID(const uint16_t PID) {
    
    #line 66 "src/obdh/system_data_pool.fin"
    _Bool is_valid = (size_t)PID < 30U;

    #line 67 "src/obdh/system_data_pool.fin"
    return is_valid;

}

_Bool sys_data_pool_is_PID_update_via_TC_enabled(const uint16_t PID) {
    
    #line 82 "src/obdh/system_data_pool.fin"
    _Bool is_enable = PID >= 5U;

    #line 83 "src/obdh/system_data_pool.fin"
    return is_enable;

}
