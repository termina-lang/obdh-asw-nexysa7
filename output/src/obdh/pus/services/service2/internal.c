
#include "obdh/pus/services/service2/internal.h"

_Bool device_drv_is_on_off_address_valid(const PS2TCRequest * const tc_request) {
    
    #line 5 "src/obdh/pus/services/service2/internal.fin"
    _Bool is_valid = false;

    #line 6 "src/obdh/pus/services/service2/internal.fin"
    uint32_t device_address = tc_request->dev_address;

    #line 8 "src/obdh/pus/services/service2/internal.fin"
    if (device_address == 0x60000001U || device_address == 0x70000001U || device_address == 0x80000001U || device_address == 0x90000001U || device_address == 0x60000000U || device_address == 0x70000000U || device_address == 0x80000000U || device_address == 0x90000000U) {
        
        #line 16 "src/obdh/pus/services/service2/internal.fin"
        is_valid = true;

    }

    #line 19 "src/obdh/pus/services/service2/internal.fin"
    return is_valid;

}
