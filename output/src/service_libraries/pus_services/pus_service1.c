
#include "service_libraries/pus_services/pus_service1.h"

const uint8_t TM_1_4_TC_X_Y_TC_SHORT_PACK_LENGTH = 1U;

const uint8_t TM_1_4_TC_X_Y_TC_NOT_VALID_NUM_OF_INSTR = 2U;

const uint8_t TM_1_4_TC_2_X_DEVICE_NOT_VALID = 3U;

const uint8_t TM_1_4_TC_2_X_DEVICE_ADDRESS_NOT_VALID = 4U;

const uint8_t TM_1_4_TC_3_X_INVALID_SID = 5U;

const uint8_t TM_1_4_TC_4_7_PID_STATS_UNDEFINED = 6U;

const uint8_t TM_1_4_TC_5_X_INVALID_EV_ID = 7U;

const uint8_t TM_1_4_TC_6_X_INVALID_MEMORY_ADDRESS = 8U;

const uint8_t TM_1_4_TC_6_X_MEMORY_ID_READ_ONLY = 9U;

const uint8_t TM_1_4_TC_6_X_OUT_OF_MEMORY_ID_LIMITS = 10U;

const uint8_t TM_1_4_TC_11_X_SCHED_TC_REJECTED = 11U;

const uint8_t TM_1_4_TC_11_X_INVALID_SCHED_TIME = 12U;

const uint8_t TM_1_4_TC_12_X_PMON_UNDEFINED = 13U;

const uint8_t TM_1_4_TC_12_X_PMON_DEFINED = 14U;

const uint8_t TM_1_4_TC_12_X_PMON_ENABLED = 15U;

const uint8_t TM_1_4_TC_12_X_INVALID_PMONID = 16U;

const uint8_t TM_1_4_TC_12_X_INVALID_PMON_DEFINITION = 17U;

const uint8_t TM_1_4_TC_15_X_INVALID_PACKET_STORE = 18U;

const uint8_t TM_1_4_TC_19_X_EV_ACTION_IS_ENABLED = 19U;

const uint8_t TM_1_4_TC_19_1_EV_ACTION_REJECTED = 20U;

const uint8_t TM_1_4_TC_19_X_EV_ACTION_NOT_DEFINED = 21U;

const uint8_t TM_1_4_TC_20_X_INVALID_PID = 22U;

const uint8_t TM_1_4_TC_20_X_PID_READ_ONLY_VIA_TC = 23U;

const uint8_t TM_1_4_ERROR_IN_ACCEPTANCE = 24U;

const uint8_t TM_1_8_TM_X_Y_TM_EXCEED_LIMIT_APPDATA = 1U;

const uint8_t TM_1_8_TM_2_1_DEV_COMMAND_EXEC_ERROR = 2U;

const uint8_t TM_1_8_TC_4_1_NOT_FREE_PID_STATS_CONFIG = 3U;

const uint8_t TM_1_8_TC_6_X_MEM_ACCESS_FAIL = 4U;

const uint8_t TM_1_8_TC_11_X_SCHED_TC_POOL_EMPTY = 5U;

const uint8_t TM_1_8_TC_19_1_MAX_EV_ACTIONS_REACHED = 6U;

void CPUSService1__notify_tm_1_1(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack, Status__i32 * const status) {
    
    #line 398 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 398 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 402 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 404 "src/service_libraries/pus_services/pus_service1.fin"
    if (is_tc_ack_accept_enabled(flags_ack)) {
        
        #line 406 "src/service_libraries/pus_services/pus_service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 408 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 412 "src/service_libraries/pus_services/pus_service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 412 "src/service_libraries/pus_services/pus_service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 414 "src/service_libraries/pus_services/pus_service1.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 418 "src/service_libraries/pus_services/pus_service1.fin"
            uint16_t tm_count = 0U;

            #line 420 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 421 "src/service_libraries/pus_services/pus_service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 423 "src/service_libraries/pus_services/pus_service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 425 "src/service_libraries/pus_services/pus_service1.fin"
            *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 427 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 428 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 431 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 432 "src/service_libraries/pus_services/pus_service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 1U, tm_count, current_obt);

                #line 433 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

            } else
            {
                
                #line 435 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            }

        } else
        {
            
            #line 441 "src/service_libraries/pus_services/pus_service1.fin"
            (*status)._variant = Status__Failure;
            #line 441 "src/service_libraries/pus_services/pus_service1.fin"
            (*status).Failure._0 = 1L;

        }

    }

    #line 447 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 447 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__notify_tm_1_3(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack, Status__i32 * const status) {
    
    #line 565 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 565 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 569 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 571 "src/service_libraries/pus_services/pus_service1.fin"
    if (is_tc_ack_start_exec_enabled(flags_ack)) {
        
        #line 573 "src/service_libraries/pus_services/pus_service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 575 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 579 "src/service_libraries/pus_services/pus_service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 579 "src/service_libraries/pus_services/pus_service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 581 "src/service_libraries/pus_services/pus_service1.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 585 "src/service_libraries/pus_services/pus_service1.fin"
            uint16_t tm_count = 0U;

            #line 587 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 588 "src/service_libraries/pus_services/pus_service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 590 "src/service_libraries/pus_services/pus_service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 591 "src/service_libraries/pus_services/pus_service1.fin"
            *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 593 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 594 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 597 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 598 "src/service_libraries/pus_services/pus_service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 3U, tm_count, current_obt);

                #line 599 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

            } else
            {
                
                #line 601 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            }

        } else
        {
            
            #line 607 "src/service_libraries/pus_services/pus_service1.fin"
            (*status)._variant = Status__Failure;
            #line 607 "src/service_libraries/pus_services/pus_service1.fin"
            (*status).Failure._0 = 1L;

        }

    }

    #line 613 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 613 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__notify_tm_1_7(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack, Status__i32 * const status) {
    
    #line 1517 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1517 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1521 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1523 "src/service_libraries/pus_services/pus_service1.fin"
    if (is_tc_ack_completion_exec_enabled(flags_ack)) {
        
        #line 1525 "src/service_libraries/pus_services/pus_service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 1527 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 1531 "src/service_libraries/pus_services/pus_service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 1531 "src/service_libraries/pus_services/pus_service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 1533 "src/service_libraries/pus_services/pus_service1.fin"
            MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

            #line 1537 "src/service_libraries/pus_services/pus_service1.fin"
            uint16_t tm_count = 0U;

            #line 1539 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 1540 "src/service_libraries/pus_services/pus_service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 1542 "src/service_libraries/pus_services/pus_service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 1543 "src/service_libraries/pus_services/pus_service1.fin"
            *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 1545 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 1546 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 1549 "src/service_libraries/pus_services/pus_service1.fin"
            if ((*status)._variant == Status__Success) {
                
                #line 1550 "src/service_libraries/pus_services/pus_service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 7U, tm_count, current_obt);

                #line 1551 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

            } else
            {
                
                #line 1553 "src/service_libraries/pus_services/pus_service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            }

        } else
        {
            
            #line 1559 "src/service_libraries/pus_services/pus_service1.fin"
            (*status)._variant = Status__Failure;
            #line 1559 "src/service_libraries/pus_services/pus_service1.fin"
            (*status).Failure._0 = 1L;

        }

    }

    #line 1565 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1565 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_2(const termina__event_t * const termina__ev, void * const termina__this, const TCStatus * const tc_status, const TCHandler * const tc_handler, Status__i32 * const status) {
    
    #line 451 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 451 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 454 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 456 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 458 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 462 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 462 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 464 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 468 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 470 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 471 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 473 "src/service_libraries/pus_services/pus_service1.fin"
        startup_tm((TMHandler *)b_tm_handler.data);

        #line 474 "src/service_libraries/pus_services/pus_service1.fin"
        *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_header.packet_id);

        #line 476 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 477 "src/service_libraries/pus_services/pus_service1.fin"
            *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_error_ctrl);

        }

        #line 480 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 482 "src/service_libraries/pus_services/pus_service1.fin"
            uint8_t error_code;

            #line 486 "src/service_libraries/pus_services/pus_service1.fin"
            if (tc_status->error_code._variant == TCErrorType__CRCError) {
                
                #line 488 "src/service_libraries/pus_services/pus_service1.fin"
                error_code = 2U;

                #line 490 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 492 "src/service_libraries/pus_services/pus_service1.fin"
                uint16_t calculated_crc = cal_crc_16(tc_handler->tc_descriptor.tc_bytes, tc_handler->tc_descriptor.tc_num_bytes - 2U);

                #line 496 "src/service_libraries/pus_services/pus_service1.fin"
                if ((*status)._variant == Status__Success) {
                    
                    #line 497 "src/service_libraries/pus_services/pus_service1.fin"
                    *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_error_ctrl);

                }

                #line 500 "src/service_libraries/pus_services/pus_service1.fin"
                if ((*status)._variant == Status__Success) {
                    
                    #line 501 "src/service_libraries/pus_services/pus_service1.fin"
                    *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, calculated_crc);

                }

            } else
            #line 505 "src/service_libraries/pus_services/pus_service1.fin"
            if (tc_status->error_code._variant == TCErrorType__APIDError) {
                
                #line 507 "src/service_libraries/pus_services/pus_service1.fin"
                error_code = 3U;

                #line 508 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

            } else
            #line 511 "src/service_libraries/pus_services/pus_service1.fin"
            if (tc_status->error_code._variant == TCErrorType__SourceIDError) {
                
                #line 513 "src/service_libraries/pus_services/pus_service1.fin"
                error_code = 4U;

                #line 514 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 516 "src/service_libraries/pus_services/pus_service1.fin"
                if ((*status)._variant == Status__Success) {
                    
                    #line 517 "src/service_libraries/pus_services/pus_service1.fin"
                    *status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, (uint16_t)tc_handler->df_header.sourceID);

                }

            } else
            #line 522 "src/service_libraries/pus_services/pus_service1.fin"
            if (tc_status->error_code._variant == TCErrorType__TypeError) {
                
                #line 524 "src/service_libraries/pus_services/pus_service1.fin"
                error_code = 5U;

                #line 525 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 527 "src/service_libraries/pus_services/pus_service1.fin"
                if ((*status)._variant == Status__Success) {
                    
                    #line 528 "src/service_libraries/pus_services/pus_service1.fin"
                    *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->df_header.type);

                }

            } else
            #line 532 "src/service_libraries/pus_services/pus_service1.fin"
            if (tc_status->error_code._variant == TCErrorType__SubTypeError) {
                
                #line 534 "src/service_libraries/pus_services/pus_service1.fin"
                error_code = 6U;

                #line 535 "src/service_libraries/pus_services/pus_service1.fin"
                *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 536 "src/service_libraries/pus_services/pus_service1.fin"
                if ((*status)._variant == Status__Success) {
                    
                    #line 537 "src/service_libraries/pus_services/pus_service1.fin"
                    *status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->df_header.subtype);

                }

            } else
            {
                

            }

        }

        #line 547 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 548 "src/service_libraries/pus_services/pus_service1.fin"
            close_tm((TMHandler *)b_tm_handler.data, 1U, 2U, tm_count, current_obt);

            #line 549 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 551 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 556 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 556 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 561 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 561 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_EvID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t EvID, Status__i32 * const status) {
    
    #line 905 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 905 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 908 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 910 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 912 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 916 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 916 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 918 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 922 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 924 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 925 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 927 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 929 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 7U, EvID, current_obt);

        #line 933 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 934 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 936 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 942 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 942 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 947 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 947 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID, Status__i32 * const status) {
    
    #line 953 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 953 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 956 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 958 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 960 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 964 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 964 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 966 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 970 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 972 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 973 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 975 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 977 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 22U, PID, current_obt);

        #line 981 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 982 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 984 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 990 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 990 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 995 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 995 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_read_only_via_TC(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID, Status__i32 * const status) {
    
    #line 1423 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1423 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1426 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1428 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1430 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1434 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1434 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1436 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1440 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1442 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1443 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1445 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1447 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 23U, PID, current_obt);

        #line 1451 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1452 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1454 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1460 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1460 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1465 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1465 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_stats_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID, Status__i32 * const status) {
    
    #line 1376 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1376 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1379 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1381 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1383 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1387 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1387 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1389 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1393 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1395 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1396 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1398 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1400 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 6U, PID, current_obt);

        #line 1404 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1405 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1407 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1413 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1413 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1418 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1418 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMONID_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID, Status__i32 * const status) {
    
    #line 1141 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1141 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1144 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1146 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1148 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1152 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1152 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1154 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1158 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1160 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1161 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1163 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1165 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 16U, PMONID, current_obt);

        #line 1169 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1170 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1172 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1178 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1178 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1183 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1183 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID, Status__i32 * const status) {
    
    #line 1047 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1047 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1050 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1052 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1054 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1058 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1058 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1060 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1064 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1066 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1067 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1069 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1071 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 14U, PMONID, current_obt);

        #line 1075 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1076 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1078 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1084 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1084 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1089 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1089 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_definition_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID, Status__i32 * const status) {
    
    #line 1187 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1187 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1190 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1192 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1194 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1198 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1198 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1200 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1204 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1206 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1207 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1209 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1211 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 17U, PMONID, current_obt);

        #line 1215 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1216 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1218 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1224 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1224 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1229 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1229 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID, Status__i32 * const status) {
    
    #line 1094 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1094 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1097 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1099 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1101 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1105 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1105 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1107 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1111 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1113 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1114 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1116 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1118 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 15U, PMONID, current_obt);

        #line 1122 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1123 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1125 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1131 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1131 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1136 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1136 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID, Status__i32 * const status) {
    
    #line 1000 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1000 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1003 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1005 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1007 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1011 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1011 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1013 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1017 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1019 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1020 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1022 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1024 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 13U, PMONID, current_obt);

        #line 1028 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1029 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1031 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1037 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1037 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1042 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1042 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_SID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t SID, Status__i32 * const status) {
    
    #line 761 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 761 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 764 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 766 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 768 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 772 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 772 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 774 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 778 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 780 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 781 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 783 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 785 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 5U, SID, current_obt);

        #line 789 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 790 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 792 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 797 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 797 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 802 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 802 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_device_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t device_address, Status__i32 * const status) {
    
    #line 713 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 713 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 716 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 718 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 720 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 724 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 724 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 726 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 730 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 732 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 733 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 735 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 737 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 4U, device_address, current_obt);

        #line 742 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 743 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 745 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 751 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 751 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 756 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 756 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_error_in_acceptance(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, Status__i32 * const status) {
    
    #line 1470 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1470 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1473 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1475 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1477 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1481 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1481 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1483 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1487 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1489 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1490 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1492 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1494 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_no_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 24U, current_obt);

        #line 1498 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1499 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1501 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1507 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1507 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1512 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1512 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID, Status__i32 * const status) {
    
    #line 1234 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1234 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1237 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1239 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1241 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1245 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1245 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1247 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1251 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1253 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1254 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1256 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1258 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 19U, event_ID, current_obt);

        #line 1262 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1263 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1265 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1271 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1271 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1276 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1276 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_rejected(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID, Status__i32 * const status) {
    
    #line 1281 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1281 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1284 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1286 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1288 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1292 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1292 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1294 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1298 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1300 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1301 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1303 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1305 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 20U, event_ID, current_obt);

        #line 1309 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1310 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1312 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1318 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1318 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1323 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1323 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID, Status__i32 * const status) {
    
    #line 1329 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1329 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1332 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1334 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1336 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1340 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1340 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1342 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1346 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1348 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1349 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1351 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1353 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 21U, event_ID, current_obt);

        #line 1357 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1358 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1360 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1366 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1366 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1371 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1371 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_mem_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id, const uint32_t mem_address, Status__i32 * const status) {
    
    #line 807 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 807 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 811 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 813 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 815 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 819 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 819 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 821 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 825 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 827 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 828 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 830 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 832 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u8_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 8U, mem_id, mem_address, current_obt);

        #line 837 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 838 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 840 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 846 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 846 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 851 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 851 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_mem_id_read_only(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id, Status__i32 * const status) {
    
    #line 856 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 856 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 860 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 862 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 864 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 868 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 868 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 870 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 874 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 876 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 877 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 879 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 881 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 9U, mem_id, current_obt);

        #line 886 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 887 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 889 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 895 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 895 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 900 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 900 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_num_of_instr_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N, Status__i32 * const status) {
    
    #line 667 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 667 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 670 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 672 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 674 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 678 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 678 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 680 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 684 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 686 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 687 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 689 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 691 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 2U, N, current_obt);

        #line 695 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 696 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 698 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 703 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 703 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 708 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 708 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_short_pack_length(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes, Status__i32 * const status) {
    
    #line 617 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 617 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 621 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 623 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 625 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 629 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 629 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 631 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 635 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 637 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 638 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 640 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 641 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t failure_data = (uint16_t)tc_bytes;

        #line 643 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 1U, failure_data, current_obt);

        #line 648 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 649 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 651 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 657 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 657 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 662 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 662 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_device_command_exec_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t on_off_command, Status__i32 * const status) {
    
    #line 1665 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1665 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1668 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1670 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1672 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1676 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1676 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1678 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1682 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1684 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1685 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1687 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1689 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 2U, on_off_command, current_obt);

        #line 1694 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1695 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1697 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1703 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1703 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1708 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1708 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_max_ev_actions_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t evID, Status__i32 * const status) {
    
    #line 1569 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1569 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1572 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1574 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1576 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1580 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1580 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1582 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1586 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1588 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1589 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1591 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1593 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 6U, evID, current_obt);

        #line 1598 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1599 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1601 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1607 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1607 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1612 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1612 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_mem_access_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_ID, Status__i32 * const status) {
    
    #line 1761 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1761 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1764 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1766 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1768 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1772 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1772 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1774 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1778 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1780 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1781 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1783 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1785 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 4U, mem_ID, current_obt);

        #line 1789 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1790 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1792 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1798 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1798 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1803 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1803 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_not_free_stats_config(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID, Status__i32 * const status) {
    
    #line 1713 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1713 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1716 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1718 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1720 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1724 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1724 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1726 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1730 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1732 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1733 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1735 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1737 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 3U, PID, current_obt);

        #line 1742 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1743 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1745 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1751 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1751 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1756 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1756 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_tm_exceed_limit_appdata(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, Status__i32 * const status) {
    
    #line 1618 "src/service_libraries/pus_services/pus_service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1618 "src/service_libraries/pus_services/pus_service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1621 "src/service_libraries/pus_services/pus_service1.fin"
    (*status)._variant = Status__Success;

    #line 1623 "src/service_libraries/pus_services/pus_service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1625 "src/service_libraries/pus_services/pus_service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1629 "src/service_libraries/pus_services/pus_service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1629 "src/service_libraries/pus_services/pus_service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1631 "src/service_libraries/pus_services/pus_service1.fin"
        MissionOBT current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1635 "src/service_libraries/pus_services/pus_service1.fin"
        uint16_t tm_count = 0U;

        #line 1637 "src/service_libraries/pus_services/pus_service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1638 "src/service_libraries/pus_services/pus_service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1640 "src/service_libraries/pus_services/pus_service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1642 "src/service_libraries/pus_services/pus_service1.fin"
        *status = build_tm_1_X_no_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 1U, current_obt);

        #line 1646 "src/service_libraries/pus_services/pus_service1.fin"
        if ((*status)._variant == Status__Success) {
            
            #line 1647 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler, status);

        } else
        {
            
            #line 1649 "src/service_libraries/pus_services/pus_service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

        }

    } else
    {
        
        #line 1655 "src/service_libraries/pus_services/pus_service1.fin"
        (*status)._variant = Status__Failure;
        #line 1655 "src/service_libraries/pus_services/pus_service1.fin"
        (*status).Failure._0 = 1L;

    }

    #line 1660 "src/service_libraries/pus_services/pus_service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1660 "src/service_libraries/pus_services/pus_service1.fin"
    return;

}
