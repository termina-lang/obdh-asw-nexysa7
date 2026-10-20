
#include "obdh/pus/services/service1.h"

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

void CPUSService1__notify_tm_1_1(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack) {
    
    #line 346 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 346 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 349 "src/obdh/pus/services/service1.fin"
    if (is_tc_ack_accept_enabled(flags_ack)) {
        
        #line 351 "src/obdh/pus/services/service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 353 "src/obdh/pus/services/service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 357 "src/obdh/pus/services/service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 357 "src/obdh/pus/services/service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 359 "src/obdh/pus/services/service1.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 363 "src/obdh/pus/services/service1.fin"
            uint16_t tm_count = 0U;

            #line 365 "src/obdh/pus/services/service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 366 "src/obdh/pus/services/service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 368 "src/obdh/pus/services/service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 370 "src/obdh/pus/services/service1.fin"
            Status__TMHandlerError status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 372 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 373 "src/obdh/pus/services/service1.fin"
                status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 376 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 377 "src/obdh/pus/services/service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 1U, tm_count, current_obt);

                #line 378 "src/obdh/pus/services/service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 380 "src/obdh/pus/services/service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 381 "src/obdh/pus/services/service1.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        } else
        {
            
            #line 387 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    }

    #line 393 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 393 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__notify_tm_1_3(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack) {
    
    #line 510 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 510 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 513 "src/obdh/pus/services/service1.fin"
    if (is_tc_ack_start_exec_enabled(flags_ack)) {
        
        #line 515 "src/obdh/pus/services/service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 517 "src/obdh/pus/services/service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 521 "src/obdh/pus/services/service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 521 "src/obdh/pus/services/service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 523 "src/obdh/pus/services/service1.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 527 "src/obdh/pus/services/service1.fin"
            uint16_t tm_count = 0U;

            #line 529 "src/obdh/pus/services/service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 530 "src/obdh/pus/services/service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 532 "src/obdh/pus/services/service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 533 "src/obdh/pus/services/service1.fin"
            Status__TMHandlerError status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 535 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 536 "src/obdh/pus/services/service1.fin"
                status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 539 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 540 "src/obdh/pus/services/service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 3U, tm_count, current_obt);

                #line 541 "src/obdh/pus/services/service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 543 "src/obdh/pus/services/service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 544 "src/obdh/pus/services/service1.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        } else
        {
            
            #line 550 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    }

    #line 556 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 556 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__notify_tm_1_7(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t flags_ack) {
    
    #line 1438 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1438 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1441 "src/obdh/pus/services/service1.fin"
    if (is_tc_ack_completion_exec_enabled(flags_ack)) {
        
        #line 1443 "src/obdh/pus/services/service1.fin"
        Option__box tm_handler = { ._variant = Option__None };

        #line 1445 "src/obdh/pus/services/service1.fin"
        self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

        #line 1449 "src/obdh/pus/services/service1.fin"
        if (tm_handler._variant == Option__Some) {
            
            #line 1449 "src/obdh/pus/services/service1.fin"
            const termina__box_t b_tm_handler = tm_handler.Some._0;

            #line 1451 "src/obdh/pus/services/service1.fin"
            CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

            #line 1455 "src/obdh/pus/services/service1.fin"
            uint16_t tm_count = 0U;

            #line 1457 "src/obdh/pus/services/service1.fin"
            self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

            #line 1458 "src/obdh/pus/services/service1.fin"
            self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

            #line 1460 "src/obdh/pus/services/service1.fin"
            startup_tm((TMHandler *)b_tm_handler.data);

            #line 1461 "src/obdh/pus/services/service1.fin"
            Status__TMHandlerError status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_id);

            #line 1463 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 1464 "src/obdh/pus/services/service1.fin"
                status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_packet_seq_ctrl);

            }

            #line 1467 "src/obdh/pus/services/service1.fin"
            if (status._variant == Status__Success) {
                
                #line 1468 "src/obdh/pus/services/service1.fin"
                close_tm((TMHandler *)b_tm_handler.data, 1U, 7U, tm_count, current_obt);

                #line 1469 "src/obdh/pus/services/service1.fin"
                self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

            } else
            {
                
                #line 1471 "src/obdh/pus/services/service1.fin"
                self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

                #line 1472 "src/obdh/pus/services/service1.fin"
                self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

            }

        } else
        {
            
            #line 1478 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    }

    #line 1484 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1484 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_2(const termina__event_t * const termina__ev, void * const termina__this, const TCStatus * const tc_status, const TCHandler * const tc_handler) {
    
    #line 397 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 397 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 400 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 402 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 406 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 406 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 408 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 412 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 414 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 415 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 417 "src/obdh/pus/services/service1.fin"
        startup_tm((TMHandler *)b_tm_handler.data);

        #line 418 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_header.packet_id);

        #line 420 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 421 "src/obdh/pus/services/service1.fin"
            status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_error_ctrl);

        }

        #line 424 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 426 "src/obdh/pus/services/service1.fin"
            uint8_t error_code;

            #line 430 "src/obdh/pus/services/service1.fin"
            if (tc_status->error_code._variant == TCErrorType__CRCError) {
                
                #line 432 "src/obdh/pus/services/service1.fin"
                error_code = 2U;

                #line 434 "src/obdh/pus/services/service1.fin"
                status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 436 "src/obdh/pus/services/service1.fin"
                uint16_t calculated_crc = cal_crc_16(tc_handler->tc_descriptor.tc_bytes, tc_handler->tc_descriptor.tc_num_bytes - 2U);

                #line 440 "src/obdh/pus/services/service1.fin"
                if (status._variant == Status__Success) {
                    
                    #line 441 "src/obdh/pus/services/service1.fin"
                    status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->packet_error_ctrl);

                }

                #line 444 "src/obdh/pus/services/service1.fin"
                if (status._variant == Status__Success) {
                    
                    #line 445 "src/obdh/pus/services/service1.fin"
                    status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, calculated_crc);

                }

            } else
            #line 449 "src/obdh/pus/services/service1.fin"
            if (tc_status->error_code._variant == TCErrorType__APIDError) {
                
                #line 451 "src/obdh/pus/services/service1.fin"
                error_code = 3U;

                #line 452 "src/obdh/pus/services/service1.fin"
                status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

            } else
            #line 455 "src/obdh/pus/services/service1.fin"
            if (tc_status->error_code._variant == TCErrorType__SourceIDError) {
                
                #line 457 "src/obdh/pus/services/service1.fin"
                error_code = 4U;

                #line 458 "src/obdh/pus/services/service1.fin"
                status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 460 "src/obdh/pus/services/service1.fin"
                if (status._variant == Status__Success) {
                    
                    #line 461 "src/obdh/pus/services/service1.fin"
                    status = append_u16_appdata_field((TMHandler *)b_tm_handler.data, (uint16_t)tc_handler->df_header.sourceID);

                }

            } else
            #line 466 "src/obdh/pus/services/service1.fin"
            if (tc_status->error_code._variant == TCErrorType__TypeError) {
                
                #line 468 "src/obdh/pus/services/service1.fin"
                error_code = 5U;

                #line 469 "src/obdh/pus/services/service1.fin"
                status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 471 "src/obdh/pus/services/service1.fin"
                if (status._variant == Status__Success) {
                    
                    #line 472 "src/obdh/pus/services/service1.fin"
                    status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->df_header.type);

                }

            } else
            #line 476 "src/obdh/pus/services/service1.fin"
            if (tc_status->error_code._variant == TCErrorType__SubTypeError) {
                
                #line 478 "src/obdh/pus/services/service1.fin"
                error_code = 6U;

                #line 479 "src/obdh/pus/services/service1.fin"
                status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, error_code);

                #line 480 "src/obdh/pus/services/service1.fin"
                if (status._variant == Status__Success) {
                    
                    #line 481 "src/obdh/pus/services/service1.fin"
                    status = append_u8_appdata_field((TMHandler *)b_tm_handler.data, tc_handler->df_header.subtype);

                }

            } else
            {
                

            }

        }

        #line 491 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 492 "src/obdh/pus/services/service1.fin"
            close_tm((TMHandler *)b_tm_handler.data, 1U, 2U, tm_count, current_obt);

            #line 493 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 495 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 496 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 501 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 506 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 506 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_EvID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t EvID) {
    
    #line 839 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 839 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 842 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 844 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 848 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 848 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 850 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 854 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 856 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 857 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 859 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 861 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 7U, EvID, current_obt);

        #line 865 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 866 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 868 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 869 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 875 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 880 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 880 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID) {
    
    #line 886 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 886 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 889 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 891 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 895 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 895 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 897 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 901 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 903 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 904 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 906 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 908 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 22U, PID, current_obt);

        #line 912 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 913 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 915 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 916 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 922 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 927 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 927 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_read_only_via_TC(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID) {
    
    #line 1346 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1346 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1349 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1351 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1355 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1355 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1357 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1361 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1363 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1364 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1366 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1368 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 23U, PID, current_obt);

        #line 1372 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1373 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1375 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1376 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1382 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1387 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1387 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PID_stats_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID) {
    
    #line 1300 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1300 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1303 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1305 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1309 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1309 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1311 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1315 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1317 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1318 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1320 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1322 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 6U, PID, current_obt);

        #line 1326 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1327 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1329 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1330 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1336 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1341 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1341 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMONID_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID) {
    
    #line 1070 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1070 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1073 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1075 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1079 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1079 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1081 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1085 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1087 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1088 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1090 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1092 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 16U, PMONID, current_obt);

        #line 1096 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1097 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1099 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1100 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1106 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1111 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1111 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID) {
    
    #line 978 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 978 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 981 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 983 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 987 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 987 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 989 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 993 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 995 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 996 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 998 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1000 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 14U, PMONID, current_obt);

        #line 1004 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1005 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1007 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1008 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1014 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1019 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1019 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_definition_invalid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID) {
    
    #line 1115 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1115 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1118 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1120 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1124 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1124 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1126 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1130 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1132 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1133 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1135 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1137 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 17U, PMONID, current_obt);

        #line 1141 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1142 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1144 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1145 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1151 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1156 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1156 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID) {
    
    #line 1024 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1024 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1027 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1029 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1033 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1033 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1035 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1039 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1041 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1042 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1044 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1046 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 15U, PMONID, current_obt);

        #line 1050 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1051 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1053 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1054 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1060 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1065 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1065 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_PMON_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PMONID) {
    
    #line 932 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 932 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 935 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 937 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 941 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 941 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 943 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 947 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 949 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 950 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 952 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 954 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 13U, PMONID, current_obt);

        #line 958 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 959 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 961 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 962 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 968 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 973 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 973 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_SID_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t SID) {
    
    #line 700 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 700 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 703 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 705 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 709 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 709 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 711 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 715 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 717 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 718 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 720 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 722 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 5U, SID, current_obt);

        #line 726 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 727 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 729 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 730 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 735 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 740 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 740 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_device_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t device_address) {
    
    #line 653 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 653 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 656 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 658 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 662 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 662 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 664 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 668 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 670 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 671 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 673 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 675 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 4U, device_address, current_obt);

        #line 680 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 681 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 683 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 684 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 690 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 695 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 695 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_error_in_acceptance(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl) {
    
    #line 1392 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1392 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1395 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1397 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1401 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1401 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1403 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1407 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1409 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1410 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1412 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1414 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_no_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 24U, current_obt);

        #line 1418 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1419 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1421 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1422 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1428 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1433 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1433 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_enabled(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID) {
    
    #line 1161 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1161 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1164 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1166 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1170 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1170 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1172 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1176 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1178 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1179 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1181 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1183 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 19U, event_ID, current_obt);

        #line 1187 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1188 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1190 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1191 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1197 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1202 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1202 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_rejected(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID) {
    
    #line 1207 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1207 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1210 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1212 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1216 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1216 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1218 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1222 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1224 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1225 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1227 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1229 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 20U, event_ID, current_obt);

        #line 1233 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1234 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1236 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1237 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1243 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1248 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1248 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_ev_action_undefined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t event_ID) {
    
    #line 1254 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1254 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1257 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1259 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1263 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1263 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1265 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1269 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1271 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1272 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1274 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 1276 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 21U, event_ID, current_obt);

        #line 1280 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1281 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1283 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1284 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1290 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1295 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1295 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_mem_address_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id, const uint32_t mem_address) {
    
    #line 745 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 745 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 748 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 750 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 754 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 754 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 756 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 760 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 762 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 763 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 765 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 767 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u8_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 8U, mem_id, mem_address, current_obt);

        #line 772 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 773 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 775 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 776 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 782 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 787 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 787 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_mem_id_read_only(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_id) {
    
    #line 792 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 792 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 795 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 797 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 801 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 801 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 803 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 807 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 809 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 810 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 812 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 814 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 9U, mem_id, current_obt);

        #line 819 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 820 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 822 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 823 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 829 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 834 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 834 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_num_of_instr_not_valid(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t N) {
    
    #line 608 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 608 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 611 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 613 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 617 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 617 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 619 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 623 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 625 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 626 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 628 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 630 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 2U, N, current_obt);

        #line 634 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 635 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 637 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 638 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 643 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 648 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 648 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_4_short_pack_length(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const size_t tc_bytes) {
    
    #line 560 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 560 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 563 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 565 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 569 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 569 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 571 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 575 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 577 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 578 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 580 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecStart };

        #line 581 "src/obdh/pus/services/service1.fin"
        uint16_t failure_data = (uint16_t)tc_bytes;

        #line 583 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 1U, failure_data, current_obt);

        #line 588 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 589 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 591 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 592 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 598 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 603 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 603 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_device_command_exec_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint32_t on_off_command) {
    
    #line 1582 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1582 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1585 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1587 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1591 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1591 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1593 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1597 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1599 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1600 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1602 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1604 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u32_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 2U, on_off_command, current_obt);

        #line 1609 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1610 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1612 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1613 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1619 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1624 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1624 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_max_ev_actions_defined(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t evID) {
    
    #line 1488 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1488 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1491 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1493 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1497 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1497 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1499 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1503 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1505 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1506 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1508 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1510 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 6U, evID, current_obt);

        #line 1515 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1516 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1518 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1519 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1525 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1530 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1530 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_mem_access_error(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint8_t mem_ID) {
    
    #line 1676 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1676 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1679 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1681 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1685 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1685 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1687 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1691 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1693 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1694 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1696 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1698 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u8_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 4U, mem_ID, current_obt);

        #line 1702 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1703 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1705 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1706 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1712 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1717 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1717 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_not_free_stats_config(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl, const uint16_t PID) {
    
    #line 1629 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1629 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1632 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1634 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1638 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1638 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1640 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1644 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1646 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1647 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1649 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1651 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_u16_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 3U, PID, current_obt);

        #line 1656 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1657 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1659 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1660 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1666 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1671 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1671 "src/obdh/pus/services/service1.fin"
    return;

}

void CPUSService1__send_tm_1_8_tm_exceed_limit_appdata(const termina__event_t * const termina__ev, void * const termina__this, const uint16_t tc_packet_id, const uint16_t tc_packet_seq_ctrl) {
    
    #line 1536 "src/obdh/pus/services/service1.fin"
    CPUSService1 * self = (CPUSService1 *)termina__this;

    #line 1536 "src/obdh/pus/services/service1.fin"
    termina__lock_t termina__lock = termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    #line 1539 "src/obdh/pus/services/service1.fin"
    Option__box tm_handler = { ._variant = Option__None };

    #line 1541 "src/obdh/pus/services/service1.fin"
    self->tm_handler_pool.alloc(termina__ev, self->tm_handler_pool._that, &tm_handler);

    #line 1545 "src/obdh/pus/services/service1.fin"
    if (tm_handler._variant == Option__Some) {
        
        #line 1545 "src/obdh/pus/services/service1.fin"
        const termina__box_t b_tm_handler = tm_handler.Some._0;

        #line 1547 "src/obdh/pus/services/service1.fin"
        CUCTime current_obt = { .finetime = 0U, .seconds = 0U };

        #line 1551 "src/obdh/pus/services/service1.fin"
        uint16_t tm_count = 0U;

        #line 1553 "src/obdh/pus/services/service1.fin"
        self->tm_counter.get_next_tm_count(termina__ev, self->tm_counter._that, &tm_count);

        #line 1554 "src/obdh/pus/services/service1.fin"
        self->obt_manager.get_current_obt(termina__ev, self->obt_manager._that, &current_obt);

        #line 1556 "src/obdh/pus/services/service1.fin"
        TCVerifyStage verify_stage = { ._variant = TCVerifyStage__ExecCompletion };

        #line 1558 "src/obdh/pus/services/service1.fin"
        Status__TMHandlerError status = build_tm_1_X_no_failure_data((TMHandler *)b_tm_handler.data, tm_count, tc_packet_id, tc_packet_seq_ctrl, verify_stage, 1U, current_obt);

        #line 1562 "src/obdh/pus/services/service1.fin"
        if (status._variant == Status__Success) {
            
            #line 1563 "src/obdh/pus/services/service1.fin"
            self->tm_channel.send_tm(termina__ev, self->tm_channel._that, b_tm_handler);

        } else
        {
            
            #line 1565 "src/obdh/pus/services/service1.fin"
            self->tm_handler_pool.free(termina__ev, self->tm_handler_pool._that, b_tm_handler);

            #line 1566 "src/obdh/pus/services/service1.fin"
            self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

        }

    } else
    {
        
        #line 1572 "src/obdh/pus/services/service1.fin"
        self->tm_counter.count_lost_tm(termina__ev, self->tm_counter._that);

    }

    #line 1577 "src/obdh/pus/services/service1.fin"
    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

    #line 1577 "src/obdh/pus/services/service1.fin"
    return;

}
