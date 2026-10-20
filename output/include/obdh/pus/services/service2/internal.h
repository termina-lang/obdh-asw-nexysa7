#ifndef OBDH__PUS__SERVICES__SERVICE2__INTERNAL_H__
#define OBDH__PUS__SERVICES__SERVICE2__INTERNAL_H__

#include <termina.h>

#include "obdh/pus/services/service2/types.h"

#include "option.h"

_Bool device_drv_is_on_off_address_valid(const PS2TCRequest * const tc_request);

#endif
