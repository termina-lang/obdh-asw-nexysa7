#ifndef OBDH__PUS__SERVICES__SERVICE1__TC_ACCEPTANCE_H__
#define OBDH__PUS__SERVICES__SERVICE1__TC_ACCEPTANCE_H__

#include <termina.h>

#include "obdh/pus/services/service1/internal.h"

#include "option.h"

TCExecutionCtrl handle_tc(const TCDescriptor * const tc_descriptor);

TCStatus try_tc_acceptation(const TCDescriptor * const tc_descriptor);

#endif
