
#include <termina.h>

#include "app.h"
#include "checksum/crc16.h"
#include "drivers/gaisler/apbuart.h"
#include "drivers/memory.h"
#include "drivers/memory/nexysa7.h"
#include "obdh/hk_fdir.h"
#include "obdh/init.h"
#include "obdh/pus/services/service1.h"
#include "obdh/pus/services/service1/internal.h"
#include "obdh/pus/services/service12/internal.h"
#include "obdh/pus/services/service128/types.h"
#include "obdh/pus/services/service17/internal.h"
#include "obdh/pus/services/service19/types.h"
#include "obdh/pus/services/service2/types.h"
#include "obdh/pus/services/service20/types.h"
#include "obdh/pus/services/service3/internal.h"
#include "obdh/pus/services/service4/internal.h"
#include "obdh/pus/services/service5/internal.h"
#include "obdh/pus/services/service6/internal.h"
#include "obdh/pus/services/service9/types.h"
#include "obdh/pus/tc_handler.h"
#include "obdh/pus/tc_packet.h"
#include "obdh/pus/tm_handler.h"
#include "obdh/pus/tm_packet.h"
#include "obdh/system_data_pool.h"
#include "obdh/tmtc/tm_frame_transmitter.h"

void termina__app__init_globals(void) {
    
    hk_fdir_timer.period.tv_sec = 1U;
    hk_fdir_timer.period.tv_usec = 0U;
    tm_pool._lock_type.type = termina__resource_lock_type__none;
    tc_pool._lock_type.type = termina__resource_lock_type__none;
    termina__deque__init(&tc_frame_deque, termina__deque_items__tc_frame_deque,
                         1U);
    termina__deque__init(&tm_frame_deque, termina__deque_items__tm_frame_deque,
                         10U);
    for (size_t termina__i0 = 0U;
         termina__i0 < 12U;
         termina__i0 = termina__i0 + 1U) {
        atomic_store(&u32_system_data_pool[termina__i0], 0U);
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 18U;
         termina__i0 = termina__i0 + 1U) {
        atomic_store(&u8_system_data_pool[termina__i0], 0U);
    }
    tc_frame_receiver._lock_type.type = termina__resource_lock_type__none;
    for (size_t termina__i0 = 0U;
         termina__i0 < 2U;
         termina__i0 = termina__i0 + 1U) {
        tc_frame_receiver.raw_rx_tc_length[termina__i0] = 0U;
    }
    tc_frame_receiver.rx_index = 0U;
    tc_frame_receiver.rx_status._variant = TCFrameRxStatus__SyncBytesRx;
    tc_frame_receiver.sync_index = 0U;
    tc_frame_receiver.sync_word[0U] = 0xBEU;
    tc_frame_receiver.sync_word[1U] = 0xBAU;
    tc_frame_receiver.sync_word[2U] = 0xBEU;
    tc_frame_receiver.sync_word[3U] = 0xEFU;
    tc_frame_receiver.tc_frame = &tc_frame_deque;
    tc_frame_receiver.tc_handler_pool._that = &tc_pool;
    tc_frame_receiver.tc_handler_pool.alloc = termina__pool__alloc;
    tc_frame_receiver.tc_handler_pool.free = termina__pool__free;
    uart_drv._lock_type.type = termina__resource_lock_type__none;
    uart_drv.registers = (volatile APBUARTRegs *)0x80000100U;
    gpio_drv._lock_type.type = termina__resource_lock_type__none;
    gpio_drv.output_mask = 0x7800000U;
    gpio_drv.registers = (volatile GPIO_registers *)0x80000A00U;
    tm_counter._lock_type.type = termina__resource_lock_type__none;
    tm_counter.lost_tm = 0U;
    tm_counter.tm_count = 0U;
    tm_frame_transmitter._lock_type.type = termina__resource_lock_type__none;
    tm_frame_transmitter.char_dev._that = &uart_drv;
    tm_frame_transmitter.char_dev.tx_ready = &CAPBUARTDriver__tx_ready;
    tm_frame_transmitter.char_dev.write_byte = &CAPBUARTDriver__write_byte;
    tm_frame_transmitter.char_dev.enable_tx_irq = &CAPBUARTDriver__enable_tx_irq;
    tm_frame_transmitter.char_dev.disable_tx_irq = &CAPBUARTDriver__disable_tx_irq;
    tm_frame_transmitter.sync_word[0U] = 0xBEU;
    tm_frame_transmitter.sync_word[1U] = 0xBAU;
    tm_frame_transmitter.sync_word[2U] = 0xBEU;
    tm_frame_transmitter.sync_word[3U] = 0xEFU;
    tm_frame_transmitter.tm_counter._that = &tm_counter;
    tm_frame_transmitter.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    tm_frame_transmitter.tm_frames = &tm_frame_deque;
    tm_frame_transmitter.tm_handler_pool._that = &tm_pool;
    tm_frame_transmitter.tm_handler_pool.alloc = termina__pool__alloc;
    tm_frame_transmitter.tm_handler_pool.free = termina__pool__free;
    tm_frame_transmitter.tx_index = 0U;
    obt_manager._lock_type.type = termina__resource_lock_type__none;
    obt_manager.ref_obt.finetime = 0U;
    obt_manager.ref_obt.seconds = 0U;
    obt_manager.ref_time_val_from_power_on.tv_sec = 0U;
    obt_manager.ref_time_val_from_power_on.tv_usec = 0U;
    obt_manager.system_api.clock_get_uptime = &SystemEntry__clock_get_uptime;
    pus_service_1._lock_type.type = termina__resource_lock_type__none;
    pus_service_1.obt_manager._that = &obt_manager;
    pus_service_1.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_1.tm_channel._that = &tm_frame_transmitter;
    pus_service_1.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_1.tm_counter._that = &tm_counter;
    pus_service_1.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_1.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_1.tm_handler_pool._that = &tm_pool;
    pus_service_1.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_1.tm_handler_pool.free = termina__pool__free;
    pus_service_9._lock_type.type = termina__resource_lock_type__none;
    pus_service_9.obt_manager._that = &obt_manager;
    pus_service_9.obt_manager.set_obt = &COBTManager__set_obt;
    pus_service_9.pus_service_1._that = &pus_service_1;
    pus_service_9.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_9.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_9.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_9.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_5._lock_type.type = termina__resource_lock_type__none;
    pus_service_5.Ev_ID_enable_config[0U] = 0x7U;
    pus_service_5.Ev_ID_enable_config[1U] = 0x0U;
    pus_service_5.Ev_ID_enable_config[2U] = 0x0U;
    pus_service_5.Ev_ID_enable_config[3U] = 0x7U;
    pus_service_5.obt_manager._that = &obt_manager;
    pus_service_5.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_5.pus_service_1._that = &pus_service_1;
    pus_service_5.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_5.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_5.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_5.pus_service_1.send_tm_1_4_EvID_not_valid = &CPUSService1__send_tm_1_4_EvID_not_valid;
    pus_service_5.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_5.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_5.tm_channel._that = &tm_frame_transmitter;
    pus_service_5.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_5.tm_counter._that = &tm_counter;
    pus_service_5.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_5.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_5.tm_handler_pool._that = &tm_pool;
    pus_service_5.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_5.tm_handler_pool.free = termina__pool__free;
    pus_service_3._lock_type.type = termina__resource_lock_type__none;
    pus_service_3.hk_config_table[0U].SID = 0U;
    pus_service_3.hk_config_table[0U].enabled = true;
    pus_service_3.hk_config_table[0U].interval = 2U;
    pus_service_3.hk_config_table[0U].interval_control = 0U;
    pus_service_3.hk_config_table[0U].num_params = 5U;
    pus_service_3.hk_config_table[0U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[1U] = 1U;
    pus_service_3.hk_config_table[0U].params_def[2U] = 2U;
    pus_service_3.hk_config_table[0U].params_def[3U] = 3U;
    pus_service_3.hk_config_table[0U].params_def[4U] = 4U;
    pus_service_3.hk_config_table[0U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[0U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[1U].SID = 10U;
    pus_service_3.hk_config_table[1U].enabled = false;
    pus_service_3.hk_config_table[1U].interval = 30U;
    pus_service_3.hk_config_table[1U].interval_control = 0U;
    pus_service_3.hk_config_table[1U].num_params = 3U;
    pus_service_3.hk_config_table[1U].params_def[0U] = 5U;
    pus_service_3.hk_config_table[1U].params_def[1U] = 6U;
    pus_service_3.hk_config_table[1U].params_def[2U] = 7U;
    pus_service_3.hk_config_table[1U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[1U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[2U].SID = 11U;
    pus_service_3.hk_config_table[2U].enabled = false;
    pus_service_3.hk_config_table[2U].interval = 60U;
    pus_service_3.hk_config_table[2U].interval_control = 0U;
    pus_service_3.hk_config_table[2U].num_params = 3U;
    pus_service_3.hk_config_table[2U].params_def[0U] = 8U;
    pus_service_3.hk_config_table[2U].params_def[1U] = 9U;
    pus_service_3.hk_config_table[2U].params_def[2U] = 10U;
    pus_service_3.hk_config_table[2U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[2U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[3U].SID = 0U;
    pus_service_3.hk_config_table[3U].enabled = false;
    pus_service_3.hk_config_table[3U].interval = 0U;
    pus_service_3.hk_config_table[3U].interval_control = 0U;
    pus_service_3.hk_config_table[3U].num_params = 0U;
    pus_service_3.hk_config_table[3U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[1U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[2U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[3U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[4U].SID = 0U;
    pus_service_3.hk_config_table[4U].enabled = false;
    pus_service_3.hk_config_table[4U].interval = 0U;
    pus_service_3.hk_config_table[4U].interval_control = 0U;
    pus_service_3.hk_config_table[4U].num_params = 0U;
    pus_service_3.hk_config_table[4U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[1U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[2U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[4U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[5U].SID = 0U;
    pus_service_3.hk_config_table[5U].enabled = false;
    pus_service_3.hk_config_table[5U].interval = 0U;
    pus_service_3.hk_config_table[5U].interval_control = 0U;
    pus_service_3.hk_config_table[5U].num_params = 0U;
    pus_service_3.hk_config_table[5U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[1U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[2U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[5U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[6U].SID = 0U;
    pus_service_3.hk_config_table[6U].enabled = false;
    pus_service_3.hk_config_table[6U].interval = 0U;
    pus_service_3.hk_config_table[6U].interval_control = 0U;
    pus_service_3.hk_config_table[6U].num_params = 0U;
    pus_service_3.hk_config_table[6U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[1U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[2U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[6U].params_def[15U] = 0U;
    pus_service_3.hk_config_table[7U].SID = 0U;
    pus_service_3.hk_config_table[7U].enabled = false;
    pus_service_3.hk_config_table[7U].interval = 0U;
    pus_service_3.hk_config_table[7U].interval_control = 0U;
    pus_service_3.hk_config_table[7U].num_params = 0U;
    pus_service_3.hk_config_table[7U].params_def[0U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[1U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[2U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[3U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[4U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[5U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[6U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[7U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[8U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[9U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[10U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[11U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[12U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[13U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[14U] = 0U;
    pus_service_3.hk_config_table[7U].params_def[15U] = 0U;
    pus_service_3.obt_manager._that = &obt_manager;
    pus_service_3.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_3.pus_service_1._that = &pus_service_1;
    pus_service_3.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_3.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_3.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_3.pus_service_1.send_tm_1_4_SID_not_valid = &CPUSService1__send_tm_1_4_SID_not_valid;
    pus_service_3.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_3.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_3.pus_service_5._that = &pus_service_5;
    pus_service_3.pus_service_5.send_tm_5_2 = &CPUSService5__send_tm_5_2;
    pus_service_3.random_seed = 42U;
    pus_service_3.system_data_pool_u32 = u32_system_data_pool;
    pus_service_3.system_data_pool_u8 = u8_system_data_pool;
    pus_service_3.tm_channel._that = &tm_frame_transmitter;
    pus_service_3.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_3.tm_counter._that = &tm_counter;
    pus_service_3.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_3.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_3.tm_handler_pool._that = &tm_pool;
    pus_service_3.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_3.tm_handler_pool.free = termina__pool__free;
    pus_service_12._lock_type.type = termina__resource_lock_type__none;
    pus_service_12.monitoring_transition_counter = 0U;
    pus_service_12.obt_manager._that = &obt_manager;
    pus_service_12.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    for (size_t termina__i0 = 0U;
         termina__i0 < 16U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_12.param_mon_config_table[termina__i0].PID = 0U;
        pus_service_12.param_mon_config_table[termina__i0].current_state._variant = CheckState__Unselected;
        pus_service_12.param_mon_config_table[termina__i0].definition._variant = MonitorDefinition__Unselected;
        pus_service_12.param_mon_config_table[termina__i0].enabled = false;
        pus_service_12.param_mon_config_table[termina__i0].interval = 0U;
        pus_service_12.param_mon_config_table[termina__i0].interval_control = 0U;
        pus_service_12.param_mon_config_table[termina__i0].repetition = 0U;
        pus_service_12.param_mon_config_table[termina__i0].repetition_control = 0U;
        pus_service_12.param_mon_config_table[termina__i0].temp_state._variant = CheckState__Unselected;
        pus_service_12.param_mon_config_table[termina__i0].transition_obt.finetime = 0U;
        pus_service_12.param_mon_config_table[termina__i0].transition_obt.seconds = 0U;
        pus_service_12.param_mon_config_table[termina__i0].type._variant = MonitorCheckType__Free;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 1U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_12.param_mon_transitions_table[termina__i0].PID = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].PMONID = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].limit_value = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].mask_value = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].new_status._variant = CheckState__Unselected;
        pus_service_12.param_mon_transitions_table[termina__i0].new_value = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].prev_status._variant = CheckState__Unselected;
        pus_service_12.param_mon_transitions_table[termina__i0].trans_obt.finetime = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].trans_obt.seconds = 0U;
        pus_service_12.param_mon_transitions_table[termina__i0].type._variant = MonitorCheckType__Free;
    }
    pus_service_12.pus_service_1._that = &pus_service_1;
    pus_service_12.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_12.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_12.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_12.pus_service_1.send_tm_1_4_PID_not_valid = &CPUSService1__send_tm_1_4_PID_not_valid;
    pus_service_12.pus_service_1.send_tm_1_4_PMON_undefined = &CPUSService1__send_tm_1_4_PMON_undefined;
    pus_service_12.pus_service_1.send_tm_1_4_PMON_enabled = &CPUSService1__send_tm_1_4_PMON_enabled;
    pus_service_12.pus_service_1.send_tm_1_4_PMONID_invalid = &CPUSService1__send_tm_1_4_PMONID_invalid;
    pus_service_12.pus_service_1.send_tm_1_4_PMON_definition_invalid = &CPUSService1__send_tm_1_4_PMON_definition_invalid;
    pus_service_12.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_12.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_12.system_data_pool_u32 = u32_system_data_pool;
    pus_service_12.system_data_pool_u8 = u8_system_data_pool;
    pus_service_12.tm_channel._that = &tm_frame_transmitter;
    pus_service_12.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_12.tm_counter._that = &tm_counter;
    pus_service_12.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_12.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_12.tm_handler_pool._that = &tm_pool;
    pus_service_12.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_12.tm_handler_pool.free = termina__pool__free;
    pus_service_19._lock_type.type = termina__resource_lock_type__none;
    for (size_t termina__i0 = 0U;
         termina__i0 < 16U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.event_action_config[termina__i0].enabled = false;
        pus_service_19.event_action_config[termina__i0].event_ID = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 16U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.event_action_packets[termina__i0].app_data_index = 0U;
        pus_service_19.event_action_packets[termina__i0].df_header.flag_ver_ack = 0U;
        pus_service_19.event_action_packets[termina__i0].df_header.sourceID = 0U;
        pus_service_19.event_action_packets[termina__i0].df_header.subtype = 0U;
        pus_service_19.event_action_packets[termina__i0].df_header.type = 0U;
        pus_service_19.event_action_packets[termina__i0].packet_error_ctrl = 0U;
        pus_service_19.event_action_packets[termina__i0].packet_header.packet_id = 0U;
        pus_service_19.event_action_packets[termina__i0].packet_header.packet_length = 0U;
        pus_service_19.event_action_packets[termina__i0].packet_header.packet_seq_ctrl = 0U;
        for (size_t termina__i1 = 0U;
             termina__i1 < 256U;
             termina__i1 = termina__i1 + 1U) {
            pus_service_19.event_action_packets[termina__i0].tc_descriptor.tc_bytes[termina__i1] = 0U;
        }
        pus_service_19.event_action_packets[termina__i0].tc_descriptor.tc_num_bytes = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_head[termina__i0] = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_number[termina__i0] = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 8U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_queue_1I[termina__i0].app_data_index = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].df_header.flag_ver_ack = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].df_header.sourceID = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].df_header.subtype = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].df_header.type = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].packet_error_ctrl = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].packet_header.packet_id = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].packet_header.packet_length = 0U;
        pus_service_19.pending_action_queue_1I[termina__i0].packet_header.packet_seq_ctrl = 0U;
        for (size_t termina__i1 = 0U;
             termina__i1 < 256U;
             termina__i1 = termina__i1 + 1U) {
            pus_service_19.pending_action_queue_1I[termina__i0].tc_descriptor.tc_bytes[termina__i1] = 0U;
        }
        pus_service_19.pending_action_queue_1I[termina__i0].tc_descriptor.tc_num_bytes = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 8U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_queue_2LS[termina__i0].app_data_index = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].df_header.flag_ver_ack = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].df_header.sourceID = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].df_header.subtype = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].df_header.type = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].packet_error_ctrl = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].packet_header.packet_id = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].packet_header.packet_length = 0U;
        pus_service_19.pending_action_queue_2LS[termina__i0].packet_header.packet_seq_ctrl = 0U;
        for (size_t termina__i1 = 0U;
             termina__i1 < 256U;
             termina__i1 = termina__i1 + 1U) {
            pus_service_19.pending_action_queue_2LS[termina__i0].tc_descriptor.tc_bytes[termina__i1] = 0U;
        }
        pus_service_19.pending_action_queue_2LS[termina__i0].tc_descriptor.tc_num_bytes = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 8U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_queue_3MS[termina__i0].app_data_index = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].df_header.flag_ver_ack = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].df_header.sourceID = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].df_header.subtype = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].df_header.type = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].packet_error_ctrl = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].packet_header.packet_id = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].packet_header.packet_length = 0U;
        pus_service_19.pending_action_queue_3MS[termina__i0].packet_header.packet_seq_ctrl = 0U;
        for (size_t termina__i1 = 0U;
             termina__i1 < 256U;
             termina__i1 = termina__i1 + 1U) {
            pus_service_19.pending_action_queue_3MS[termina__i0].tc_descriptor.tc_bytes[termina__i1] = 0U;
        }
        pus_service_19.pending_action_queue_3MS[termina__i0].tc_descriptor.tc_num_bytes = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 8U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_19.pending_action_queue_4HS[termina__i0].app_data_index = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].df_header.flag_ver_ack = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].df_header.sourceID = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].df_header.subtype = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].df_header.type = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].packet_error_ctrl = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].packet_header.packet_id = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].packet_header.packet_length = 0U;
        pus_service_19.pending_action_queue_4HS[termina__i0].packet_header.packet_seq_ctrl = 0U;
        for (size_t termina__i1 = 0U;
             termina__i1 < 256U;
             termina__i1 = termina__i1 + 1U) {
            pus_service_19.pending_action_queue_4HS[termina__i0].tc_descriptor.tc_bytes[termina__i1] = 0U;
        }
        pus_service_19.pending_action_queue_4HS[termina__i0].tc_descriptor.tc_num_bytes = 0U;
    }
    pus_service_19.pus_service_1._that = &pus_service_1;
    pus_service_19.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_19.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_19.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_19.pus_service_1.send_tm_1_4_EvID_not_valid = &CPUSService1__send_tm_1_4_EvID_not_valid;
    pus_service_19.pus_service_1.send_tm_1_4_ev_action_enabled = &CPUSService1__send_tm_1_4_ev_action_enabled;
    pus_service_19.pus_service_1.send_tm_1_4_ev_action_rejected = &CPUSService1__send_tm_1_4_ev_action_rejected;
    pus_service_19.pus_service_1.send_tm_1_4_ev_action_undefined = &CPUSService1__send_tm_1_4_ev_action_undefined;
    pus_service_19.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_19.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_19.pus_service_1.send_tm_1_8_max_ev_actions_defined = &CPUSService1__send_tm_1_8_max_ev_actions_defined;
    pus_service_20._lock_type.type = termina__resource_lock_type__none;
    pus_service_20.obt_manager._that = &obt_manager;
    pus_service_20.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_20.pus_service_1._that = &pus_service_1;
    pus_service_20.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_20.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_20.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_20.pus_service_1.send_tm_1_4_PID_not_valid = &CPUSService1__send_tm_1_4_PID_not_valid;
    pus_service_20.pus_service_1.send_tm_1_4_PID_read_only_via_TC = &CPUSService1__send_tm_1_4_PID_read_only_via_TC;
    pus_service_20.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_20.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_20.system_data_pool_u32 = u32_system_data_pool;
    pus_service_20.system_data_pool_u8 = u8_system_data_pool;
    pus_service_20.tm_channel._that = &tm_frame_transmitter;
    pus_service_20.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_20.tm_counter._that = &tm_counter;
    pus_service_20.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_20.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_20.tm_handler_pool._that = &tm_pool;
    pus_service_20.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_20.tm_handler_pool.free = termina__pool__free;
    pus_service_17._lock_type.type = termina__resource_lock_type__none;
    pus_service_17.obt_manager._that = &obt_manager;
    pus_service_17.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_17.pus_service_1._that = &pus_service_1;
    pus_service_17.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_17.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_17.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_17.tm_channel._that = &tm_frame_transmitter;
    pus_service_17.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_17.tm_counter._that = &tm_counter;
    pus_service_17.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_17.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_17.tm_handler_pool._that = &tm_pool;
    pus_service_17.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_17.tm_handler_pool.free = termina__pool__free;
    pus_service_128._lock_type.type = termina__resource_lock_type__none;
    pus_service_128.pus_service_1._that = &pus_service_1;
    pus_service_128.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_2._lock_type.type = termina__resource_lock_type__none;
    pus_service_2.device_pins[0U]._variant = Option__None;
    pus_service_2.device_pins[1U]._variant = Option__None;
    pus_service_2.device_pins[2U]._variant = Option__None;
    pus_service_2.device_pins[3U]._variant = Option__None;
    pus_service_2.device_pins[4U]._variant = Option__None;
    pus_service_2.device_pins[5U]._variant = Option__None;
    pus_service_2.device_pins[6U]._variant = Option__Some;
    pus_service_2.device_pins[6U].Some._0.pin = 23U;
    pus_service_2.device_pins[6U].Some._0.port = 0U;
    pus_service_2.device_pins[7U]._variant = Option__Some;
    pus_service_2.device_pins[7U].Some._0.pin = 24U;
    pus_service_2.device_pins[7U].Some._0.port = 0U;
    pus_service_2.device_pins[8U]._variant = Option__Some;
    pus_service_2.device_pins[8U].Some._0.pin = 25U;
    pus_service_2.device_pins[8U].Some._0.port = 0U;
    pus_service_2.device_pins[9U]._variant = Option__Some;
    pus_service_2.device_pins[9U].Some._0.pin = 26U;
    pus_service_2.device_pins[9U].Some._0.port = 0U;
    pus_service_2.device_pins[10U]._variant = Option__None;
    pus_service_2.device_pins[11U]._variant = Option__None;
    pus_service_2.device_pins[12U]._variant = Option__None;
    pus_service_2.device_pins[13U]._variant = Option__None;
    pus_service_2.device_pins[14U]._variant = Option__None;
    pus_service_2.device_pins[15U]._variant = Option__None;
    pus_service_2.gpio._that = &gpio_drv;
    pus_service_2.gpio.write_pin = &CGRGPIODriver__write_pin;
    pus_service_2.pus_service_1._that = &pus_service_1;
    pus_service_2.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_2.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_2.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_2.pus_service_1.send_tm_1_4_device_address_not_valid = &CPUSService1__send_tm_1_4_device_address_not_valid;
    pus_service_2.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_2.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    memory_drv._lock_type.type = termina__resource_lock_type__none;
    memory_drv.ddr2 = (volatile uint8_t (*)[16777216U])0x40000000U;
    memory_drv.write_enabled[0U] = false;
    memory_drv.write_enabled[1U] = true;
    memory_drv.write_enabled[2U] = true;
    memory_drv.write_enabled[3U] = true;
    memory_drv.write_enabled[4U] = true;
    memory_drv.write_enabled[5U] = true;
    memory_drv.write_enabled[6U] = true;
    memory_drv.write_enabled[7U] = false;
    pus_service_6._lock_type.type = termina__resource_lock_type__none;
    pus_service_6.memory._that = &memory_drv;
    pus_service_6.memory.check_access = &CNexysA7Memory__check_access;
    pus_service_6.memory.read = &CNexysA7Memory__read;
    pus_service_6.memory.write = &CNexysA7Memory__write;
    pus_service_6.memory.checksum = &CNexysA7Memory__checksum;
    pus_service_6.obt_manager._that = &obt_manager;
    pus_service_6.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    pus_service_6.pus_service_1._that = &pus_service_1;
    pus_service_6.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_6.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_6.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_6.pus_service_1.send_tm_1_4_mem_address_not_valid = &CPUSService1__send_tm_1_4_mem_address_not_valid;
    pus_service_6.pus_service_1.send_tm_1_4_mem_id_read_only = &CPUSService1__send_tm_1_4_mem_id_read_only;
    pus_service_6.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_6.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_6.pus_service_1.send_tm_1_8_tm_exceed_limit_appdata = &CPUSService1__send_tm_1_8_tm_exceed_limit_appdata;
    pus_service_6.tm_channel._that = &tm_frame_transmitter;
    pus_service_6.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_6.tm_counter._that = &tm_counter;
    pus_service_6.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_6.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_6.tm_handler_pool._that = &tm_pool;
    pus_service_6.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_6.tm_handler_pool.free = termina__pool__free;
    pus_service_4._lock_type.type = termina__resource_lock_type__none;
    pus_service_4.obt_manager._that = &obt_manager;
    pus_service_4.obt_manager.get_current_obt = &COBTManager__get_current_obt;
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_4.param_stats[termina__i0].max = 0U;
        pus_service_4.param_stats[termina__i0].max_obt.finetime = 0U;
        pus_service_4.param_stats[termina__i0].max_obt.seconds = 0U;
        pus_service_4.param_stats[termina__i0].mean_value = 0U;
        pus_service_4.param_stats[termina__i0].min = 0U;
        pus_service_4.param_stats[termina__i0].min_obt.finetime = 0U;
        pus_service_4.param_stats[termina__i0].min_obt.seconds = 0U;
        pus_service_4.param_stats[termina__i0].samples = 0U;
    }
    pus_service_4.pus_service_1._that = &pus_service_1;
    pus_service_4.pus_service_1.notify_tm_1_3 = &CPUSService1__notify_tm_1_3;
    pus_service_4.pus_service_1.send_tm_1_4_short_pack_length = &CPUSService1__send_tm_1_4_short_pack_length;
    pus_service_4.pus_service_1.send_tm_1_4_num_of_instr_not_valid = &CPUSService1__send_tm_1_4_num_of_instr_not_valid;
    pus_service_4.pus_service_1.send_tm_1_4_PID_not_valid = &CPUSService1__send_tm_1_4_PID_not_valid;
    pus_service_4.pus_service_1.send_tm_1_4_PID_stats_undefined = &CPUSService1__send_tm_1_4_PID_stats_undefined;
    pus_service_4.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    pus_service_4.pus_service_1.notify_tm_1_7 = &CPUSService1__notify_tm_1_7;
    pus_service_4.pus_service_1.send_tm_1_8_not_free_stats_config = &CPUSService1__send_tm_1_8_not_free_stats_config;
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_4.stats_config_table.PID[termina__i0] = 0U;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_4.stats_config_table.defined[termina__i0] = false;
    }
    for (size_t termina__i0 = 0U;
         termina__i0 < 4U;
         termina__i0 = termina__i0 + 1U) {
        pus_service_4.stats_config_table.start_time[termina__i0].finetime = 0U;
        pus_service_4.stats_config_table.start_time[termina__i0].seconds = 0U;
    }
    pus_service_4.system_data_pool_u32 = u32_system_data_pool;
    pus_service_4.system_data_pool_u8 = u8_system_data_pool;
    pus_service_4.tm_channel._that = &tm_frame_transmitter;
    pus_service_4.tm_channel.send_tm = &CTMFrameTransmitter__send_tm;
    pus_service_4.tm_counter._that = &tm_counter;
    pus_service_4.tm_counter.get_next_tm_count = &CTMCounter__get_next_tm_count;
    pus_service_4.tm_counter.count_lost_tm = &CTMCounter__count_lost_tm;
    pus_service_4.tm_handler_pool._that = &tm_pool;
    pus_service_4.tm_handler_pool.alloc = termina__pool__alloc;
    pus_service_4.tm_handler_pool.free = termina__pool__free;
    mng_tc_executor._lock_type.type = termina__resource_lock_type__none;
    mng_tc_executor.pus_service_1._that = &pus_service_1;
    mng_tc_executor.pus_service_1.notify_tm_1_1 = &CPUSService1__notify_tm_1_1;
    mng_tc_executor.pus_service_1.send_tm_1_2 = &CPUSService1__send_tm_1_2;
    mng_tc_executor.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    mng_tc_executor.pus_service_128._that = &pus_service_128;
    mng_tc_executor.pus_service_128.exec_tc = &CPUSService128__exec_tc;
    mng_tc_executor.pus_service_17._that = &pus_service_17;
    mng_tc_executor.pus_service_17.exec_tc = &CPUSService17__exec_tc;
    mng_tc_executor.pus_service_2._that = &pus_service_2;
    mng_tc_executor.pus_service_2.exec_tc = &CPUSService2__exec_tc;
    mng_tc_executor.pus_service_9._that = &pus_service_9;
    mng_tc_executor.pus_service_9.exec_tc = &CPUSService9__exec_tc;
    init_hdlr.gpio_driver._that = &gpio_drv;
    init_hdlr.gpio_driver.init_gpio = &CGRGPIODriver__init_gpio;
    init_hdlr.system_data_pool_u32 = u32_system_data_pool;
    init_hdlr.system_data_pool_u8 = u8_system_data_pool;
    init_hdlr.uart_drv._that = &uart_drv;
    init_hdlr.uart_drv.initialize = &CAPBUARTDriver__initialize;
    uart_hdlr.char_dev._that = &uart_drv;
    uart_hdlr.char_dev.read_byte = &CAPBUARTDriver__read_byte;
    uart_hdlr.tc_frame_receiver._that = &tc_frame_receiver;
    uart_hdlr.tc_frame_receiver.receive = &CTCFrameReceiver__receive;
    uart_hdlr.tc_message_queue_output = &tc_message_queue;
    uart_hdlr.tm_frame_transmitter._that = &tm_frame_transmitter;
    uart_hdlr.tm_frame_transmitter.transmit = &CTMFrameTransmitter__transmit;
    obdh_manager.bkg_message_queue_output = &bkg_message_queue;
    obdh_manager.hkfdir_message_queue_output = &hkfdir_message_queue;
    obdh_manager.mng_tc_executor._that = &mng_tc_executor;
    obdh_manager.mng_tc_executor.PUS_prio_exec_tc = &CManagerTExecutor__PUS_prio_exec_tc;
    obdh_manager.mng_tc_executor.mng_tc_acceptation = &CManagerTExecutor__mng_tc_acceptation;
    obdh_manager.mng_tc_executor.mng_tc_rejection = &CManagerTExecutor__mng_tc_rejection;
    obdh_manager.tc_handler_pool._that = &tc_pool;
    obdh_manager.tc_handler_pool.alloc = termina__pool__alloc;
    obdh_manager.tc_handler_pool.free = termina__pool__free;
    hk_fdir.action_tc_message_queue_output = &action_tc_message_queue;
    hk_fdir.pus_service_1._that = &pus_service_1;
    hk_fdir.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    hk_fdir.pus_service_12._that = &pus_service_12;
    hk_fdir.pus_service_12.exec_tc = &CPUSService12__exec_tc;
    hk_fdir.pus_service_12.do_monitoring = &CPUSService12__do_monitoring;
    hk_fdir.pus_service_12.is_PMON_enabled = &CPUSService12__is_PMON_enabled;
    hk_fdir.pus_service_19._that = &pus_service_19;
    hk_fdir.pus_service_19.exec_tc = &CPUSService19__exec_tc;
    hk_fdir.pus_service_19.manage_event_action = &CPUSService19__manage_event_action;
    hk_fdir.pus_service_19.get_pending_action_number = &CPUSService19__get_pending_action_number;
    hk_fdir.pus_service_19.extract_action = &CPUSService19__extract_action;
    hk_fdir.pus_service_3._that = &pus_service_3;
    hk_fdir.pus_service_3.do_hk = &CPUSService3__do_hk;
    hk_fdir.pus_service_3.exec_tc = &CPUSService3__exec_tc;
    hk_fdir.pus_service_3.update_params = &CPUSService3__update_params;
    hk_fdir.pus_service_4._that = &pus_service_4;
    hk_fdir.pus_service_4.exec_tc = &CPUSService4__exec_tc;
    hk_fdir.pus_service_4.update_all_stats = &CPUSService4__update_all_stats;
    hk_fdir.pus_service_5._that = &pus_service_5;
    hk_fdir.pus_service_5.exec_tc = &CPUSService5__exec_tc;
    hk_fdir.pus_service_5.is_Ev_ID_enabled_ext = &CPUSService5__is_Ev_ID_enabled_ext;
    hk_fdir.pus_service_5.send_tm_5_x = &CPUSService5__send_tm_5_x;
    hk_fdir.tc_handler_pool._that = &tc_pool;
    hk_fdir.tc_handler_pool.alloc = termina__pool__alloc;
    hk_fdir.tc_handler_pool.free = termina__pool__free;
    bkg_tc_executor.pus_service_1._that = &pus_service_1;
    bkg_tc_executor.pus_service_1.send_tm_1_4_error_in_acceptance = &CPUSService1__send_tm_1_4_error_in_acceptance;
    bkg_tc_executor.pus_service_20._that = &pus_service_20;
    bkg_tc_executor.pus_service_20.exec_tc = &CPUSService20__exec_tc;
    bkg_tc_executor.pus_service_6._that = &pus_service_6;
    bkg_tc_executor.pus_service_6.exec_tc = &CPUSService6__exec_tc;
    bkg_tc_executor.tc_handler_pool._that = &tc_pool;
    bkg_tc_executor.tc_handler_pool.alloc = termina__pool__alloc;
    bkg_tc_executor.tc_handler_pool.free = termina__pool__free;

    return;

}
