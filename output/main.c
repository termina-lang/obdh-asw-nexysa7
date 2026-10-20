
#include <termina.h>

#include "app.h"

static max_align_t termina__pool_memory__tc_pool[termina__pool__area_length(sizeof(TCHandler), 10U)];
static max_align_t termina__pool_memory__tm_pool[termina__pool__area_length(sizeof(TMHandler), 10U)];

static void termina__app__init_tasks(termina__error_code_t * const status) {
    
    *status = termina__error__none;

    bkg_tc_executor._task_id = bkg_tc_executor__task_id;

    bkg_tc_executor._task_msg_queue_id = bkg_tc_executor__task_msg_queue_id;

    termina__task__init(bkg_tc_executor__task_id, 8, 4096U, &termina__task_entry__CBKGTCExecutorTask, &bkg_tc_executor, status);

    if (termina__error__none == *status) {
        
        hk_fdir._task_id = hk_fdir__task_id;

        hk_fdir._task_msg_queue_id = hk_fdir__task_msg_queue_id;

        termina__task__init(hk_fdir__task_id, 6, 4096U, &termina__task_entry__CHousekeepingFDIRTask, &hk_fdir, status);

    }

    if (termina__error__none == *status) {
        
        obdh_manager._task_id = obdh_manager__task_id;

        obdh_manager._task_msg_queue_id = obdh_manager__task_msg_queue_id;

        termina__task__init(obdh_manager__task_id, 5, 4096U, &termina__task_entry__COBDHManagerTask, &obdh_manager, status);

    }

}

static void termina__app__init_handlers(void) {
    
    init_hdlr._handler_id = init_hdlr__handler_id;

    uart_hdlr._handler_id = uart_hdlr__handler_id;

}

static void termina__app__init_emitters(termina__error_code_t * const status) {
    
    termina__periodic_timer_connection_t timer_connection;

    termina__interrupt_connection_t interrupt_connection;

    *status = termina__error__none;

    timer_connection.type = termina__emitter_connection_type__task;
    timer_connection.task.task_msg_queue_id = hk_fdir__task_msg_queue_id;
    timer_connection.task.sink_msgq_id = hk_fdir__hk_fdir_timer_ev__sink_msg_queue_id;
    timer_connection.task.sink_port_id = CHousekeepingFDIRTask__hk_fdir_timer_ev;

    hk_fdir.hk_fdir_timer_ev = hk_fdir__hk_fdir_timer_ev__sink_msg_queue_id;

    termina__periodic_timer__init(hk_fdir_timer__timer_id, hk_fdir_timer__emitter_id, &timer_connection, &hk_fdir_timer.period, status);

    if (termina__error__none == *status) {
        
        interrupt_connection.type = termina__emitter_connection_type__handler;
        interrupt_connection.handler.handler_object = (void *)&uart_hdlr;
        interrupt_connection.handler.handler_id = uart_hdlr__handler_id;
        interrupt_connection.handler.handler_action = &CTMTCFrameIRQHandler__irq_handler;

        termina__interrupt__init(2, irq_2__emitter_id, &interrupt_connection, status);

    }

}

static void termina__app__init_mutexes(termina__error_code_t * const status) {
    
    MutexProtocol protocol;

    *status = termina__error__none;

    protocol._variant = MutexProtocol__Ceiling;
    protocol.Ceiling._0 = 5;

    termina__mutex__init(obt_manager__mutex_id, protocol, status);

}

static void termina__app__init_pools(termina__error_code_t * const status) {
    
    *status = termina__error__none;

    tc_pool.pool_id = tc_pool__pool_id;

    termina__pool__init(&tc_pool, (void *)termina__pool_memory__tc_pool, sizeof(termina__pool_memory__tc_pool), sizeof(TCHandler), status);

    if (termina__error__none == *status) {
        
        tm_pool.pool_id = tm_pool__pool_id;

        termina__pool__init(&tm_pool, (void *)termina__pool_memory__tm_pool, sizeof(termina__pool_memory__tm_pool), sizeof(TMHandler), status);

    }

}

static void termina__app__init_msg_queues(termina__error_code_t * const status) {
    
    *status = termina__error__none;

    termina__msg_queue__init(obdh_manager__task_msg_queue_id, sizeof(termina__event_t), 10U + 5U, status);

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(hk_fdir__task_msg_queue_id, sizeof(termina__event_t), 1U + 10U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(bkg_tc_executor__task_msg_queue_id, sizeof(termina__event_t), 10U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(hk_fdir__hk_fdir_timer_ev__sink_msg_queue_id, sizeof(TimeVal), 1U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(tc_message_queue__channel_msg_queue_id, sizeof(termina__box_t), 10U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(hkfdir_message_queue__channel_msg_queue_id, sizeof(termina__box_t), 10U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(bkg_message_queue__channel_msg_queue_id, sizeof(termina__box_t), 10U, status);

    }

    if (termina__error__none == *status) {
        
        termina__msg_queue__init(action_tc_message_queue__channel_msg_queue_id, sizeof(termina__box_t), 5U, status);

    }

}

static void termina__app__enable_protection(void) {
    
    obt_manager._lock_type.type = termina__resource_lock_type__mutex;
    obt_manager._lock_type.mutex.mutex_id = obt_manager__mutex_id;

    tm_counter._lock_type.type = termina__resource_lock_type__irq;

    tm_frame_transmitter._lock_type.type = termina__resource_lock_type__irq;

    uart_drv._lock_type.type = termina__resource_lock_type__irq;

    tc_pool._lock_type.type = termina__resource_lock_type__irq;

    tm_pool._lock_type.type = termina__resource_lock_type__irq;

}

static void termina__app__init_channel_connections(void) {
    
    action_tc_message_queue.task_id = obdh_manager__task_id;
    action_tc_message_queue.task_msg_queue_id = obdh_manager__task_msg_queue_id;
    action_tc_message_queue.channel_msg_queue_id = action_tc_message_queue__channel_msg_queue_id;
    action_tc_message_queue.port_id = COBDHManagerTask__action_tc_message_queue_input;

    obdh_manager.action_tc_message_queue_input = action_tc_message_queue__channel_msg_queue_id;

    bkg_message_queue.task_id = bkg_tc_executor__task_id;
    bkg_message_queue.task_msg_queue_id = bkg_tc_executor__task_msg_queue_id;
    bkg_message_queue.channel_msg_queue_id = bkg_message_queue__channel_msg_queue_id;
    bkg_message_queue.port_id = CBKGTCExecutorTask__bkg_message_queue_input;

    bkg_tc_executor.bkg_message_queue_input = bkg_message_queue__channel_msg_queue_id;

    hkfdir_message_queue.task_id = hk_fdir__task_id;
    hkfdir_message_queue.task_msg_queue_id = hk_fdir__task_msg_queue_id;
    hkfdir_message_queue.channel_msg_queue_id = hkfdir_message_queue__channel_msg_queue_id;
    hkfdir_message_queue.port_id = CHousekeepingFDIRTask__hkfdir_message_queue_input;

    hk_fdir.hkfdir_message_queue_input = hkfdir_message_queue__channel_msg_queue_id;

    tc_message_queue.task_id = obdh_manager__task_id;
    tc_message_queue.task_msg_queue_id = obdh_manager__task_msg_queue_id;
    tc_message_queue.channel_msg_queue_id = tc_message_queue__channel_msg_queue_id;
    tc_message_queue.port_id = COBDHManagerTask__tc_message_queue_input;

    obdh_manager.tc_message_queue_input = tc_message_queue__channel_msg_queue_id;

}

static void termina__app__initial_event(void) {
    
    termina__system_init_connection_t connection;

    connection.handler_object = (void *)&init_hdlr;
    connection.handler_id = init_hdlr__handler_id;
    connection.handler_action = &CInitHandler__init;

    termina__system_init__dispatch(system_init__emitter_id, &connection);

    return;

}

void termina__app__init(termina__error_code_t * const status) {
    
    *status = termina__error__none;

    termina__app__init_globals();

    termina__app__init_msg_queues(status);

    if (termina__error__none == *status) {
        
        termina__app__init_channel_connections();

        termina__app__init_pools(status);

    }

    if (termina__error__none == *status) {
        
        termina__app__initial_event();

        termina__app__init_mutexes(status);

    }

    if (termina__error__none == *status) {
        
        termina__app__enable_protection();

        termina__app__init_emitters(status);

    }

    if (termina__error__none == *status) {
        
        termina__app__init_handlers();

        termina__app__init_tasks(status);

    }

}
