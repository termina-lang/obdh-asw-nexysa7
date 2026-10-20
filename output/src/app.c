
#include "app.h"

PeriodicTimer hk_fdir_timer;

termina__msg_queue_t tc_message_queue;

termina__msg_queue_t hkfdir_message_queue;

termina__msg_queue_t bkg_message_queue;

termina__msg_queue_t action_tc_message_queue;

termina__pool_t tm_pool;

termina__pool_t tc_pool;

termina__box_t termina__deque_items__tc_frame_deque[1U];
termina__deque_t tc_frame_deque;

termina__box_t termina__deque_items__tm_frame_deque[10U];
termina__deque_t tm_frame_deque;

_Atomic uint32_t u32_system_data_pool[12U];

_Atomic uint8_t u8_system_data_pool[18U];

CTCFrameReceiver tc_frame_receiver;

CAPBUARTDriver uart_drv;

CGPIODriver gpio_drv;

CTMCounter tm_counter;

CTMFrameTransmitter tm_frame_transmitter;

COBTManager obt_manager;

CPUSService1 pus_service_1;

CPUSService9 pus_service_9;

CPUSService5 pus_service_5;

CPUSService3 pus_service_3;

CPUSService12 pus_service_12;

CPUSService19 pus_service_19;

CPUSService20 pus_service_20;

CPUSService17 pus_service_17;

CPUSService128 pus_service_128;

CPUSService2 pus_service_2;

CNexysA7Memory memory_drv;

CPUSService6 pus_service_6;

CPUSService4 pus_service_4;

CManagerTExecutor mng_tc_executor;

CInitHandler init_hdlr;

CTMTCFrameIRQHandler uart_hdlr;

COBDHManagerTask obdh_manager;

CHousekeepingFDIRTask hk_fdir;

CBKGTCExecutorTask bkg_tc_executor;
