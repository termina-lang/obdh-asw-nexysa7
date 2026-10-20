#ifndef APP_H__
#define APP_H__

#include <termina.h>

#include "drivers/gaisler/apbuart.h"
#include "drivers/gaisler/grgpio.h"
#include "drivers/memory/nexysa7.h"
#include "obdh/bkg_tc_executor.h"
#include "obdh/hk_fdir.h"
#include "obdh/init.h"
#include "obdh/manager.h"
#include "obdh/obt_manager.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service12.h"
#include "obdh/pus/services/service17.h"
#include "obdh/pus/services/service19.h"
#include "obdh/pus/services/service2.h"
#include "obdh/pus/services/service20.h"
#include "obdh/pus/services/service3.h"
#include "obdh/pus/services/service4.h"
#include "obdh/pus/services/service5.h"
#include "obdh/pus/services/service6.h"
#include "obdh/pus/services/service9.h"
#include "obdh/tm_counter.h"
#include "obdh/tmtc/frame_irq_handler.h"
#include "obdh/tmtc/tc_frame_receiver.h"
#include "obdh/tmtc/tm_frame_transmitter.h"

#include "option.h"

extern PeriodicTimer hk_fdir_timer;

extern termina__msg_queue_t tc_message_queue;

extern termina__msg_queue_t hkfdir_message_queue;

extern termina__msg_queue_t bkg_message_queue;

extern termina__msg_queue_t action_tc_message_queue;

extern termina__pool_t tm_pool;

extern termina__pool_t tc_pool;

extern termina__box_t termina__deque_items__tc_frame_deque[1U];
extern termina__deque_t tc_frame_deque;

extern termina__box_t termina__deque_items__tm_frame_deque[10U];
extern termina__deque_t tm_frame_deque;

extern _Atomic uint32_t u32_system_data_pool[12U];

extern _Atomic uint8_t u8_system_data_pool[18U];

extern CTCFrameReceiver tc_frame_receiver;

extern CAPBUARTDriver uart_drv;

extern CGRGPIODriver gpio_drv;

extern CTMCounter tm_counter;

extern CTMFrameTransmitter tm_frame_transmitter;

extern COBTManager obt_manager;

extern CPUSService1 pus_service_1;

extern CPUSService9 pus_service_9;

extern CPUSService5 pus_service_5;

extern CPUSService3 pus_service_3;

extern CPUSService12 pus_service_12;

extern CPUSService19 pus_service_19;

extern CPUSService20 pus_service_20;

extern CPUSService17 pus_service_17;

extern CPUSService128 pus_service_128;

extern CPUSService2 pus_service_2;

extern CNexysA7Memory memory_drv;

extern CPUSService6 pus_service_6;

extern CPUSService4 pus_service_4;

extern CManagerTExecutor mng_tc_executor;

extern CInitHandler init_hdlr;

extern CTMTCFrameIRQHandler uart_hdlr;

extern COBDHManagerTask obdh_manager;

extern CHousekeepingFDIRTask hk_fdir;

extern CBKGTCExecutorTask bkg_tc_executor;

#endif
