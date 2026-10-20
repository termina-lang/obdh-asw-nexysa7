
#include "obdh/pus/services/service1/tc_acceptance.h"

TCExecutionCtrl handle_tc(const TCDescriptor * const tc_descriptor) {
    
    #line 25 "src/obdh/pus/services/service1/tc_acceptance.fin"
    uint8_t type = get_type(tc_descriptor->tc_bytes);

    #line 26 "src/obdh/pus/services/service1/tc_acceptance.fin"
    TCExecutionCtrl exec_ctrl;

    #line 28 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (type == 2U || type == 9U || type == 17U || type == 128U) {
        
        #line 30 "src/obdh/pus/services/service1/tc_acceptance.fin"
        exec_ctrl._variant = TCExecutionCtrl__ExecCtrlPrioTC;

    } else
    #line 32 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (type == 3U || type == 5U || type == 12U || type == 19U) {
        
        #line 34 "src/obdh/pus/services/service1/tc_acceptance.fin"
        exec_ctrl._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

    } else
    #line 36 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (type == 6U || type == 20U) {
        
        #line 38 "src/obdh/pus/services/service1/tc_acceptance.fin"
        exec_ctrl._variant = TCExecutionCtrl__ExecCtrlBKGTC;

    } else
    {
        
        #line 43 "src/obdh/pus/services/service1/tc_acceptance.fin"
        exec_ctrl._variant = TCExecutionCtrl__Undefined;

    }

    #line 46 "src/obdh/pus/services/service1/tc_acceptance.fin"
    return exec_ctrl;

}

TCStatus try_tc_acceptation(const TCDescriptor * const tc_descriptor) {
    
    #line 67 "src/obdh/pus/services/service1/tc_acceptance.fin"
    TCStatus tc_status = { .acceptation_status = { ._variant = TCAcceptationStatus__Rejected }, .error_code = { ._variant = TCErrorType__Undefined }, .execution_status = { ._variant = TCExecutionCtrl__Undefined } };

    #line 71 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (false == is_crc_valid(tc_descriptor)) {
        
        #line 73 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

        #line 74 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.error_code._variant = TCErrorType__CRCError;

    } else
    #line 76 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (false == is_apid_valid(tc_descriptor)) {
        
        #line 78 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

        #line 79 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.error_code._variant = TCErrorType__APIDError;

    } else
    #line 81 "src/obdh/pus/services/service1/tc_acceptance.fin"
    if (false == is_sourceID_valid(tc_descriptor)) {
        
        #line 83 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

        #line 84 "src/obdh/pus/services/service1/tc_acceptance.fin"
        tc_status.error_code._variant = TCErrorType__SourceIDError;

    } else
    {
        
        #line 88 "src/obdh/pus/services/service1/tc_acceptance.fin"
        uint8_t type = get_type(tc_descriptor->tc_bytes);

        #line 89 "src/obdh/pus/services/service1/tc_acceptance.fin"
        uint8_t subtype = get_subtype(tc_descriptor->tc_bytes);

        #line 91 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (9U == type) {
            
            #line 93 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (129U == subtype) {
                
                #line 95 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 96 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlPrioTC;

            } else
            {
                
                #line 99 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 100 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 103 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (17U == type) {
            
            #line 105 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype) {
                
                #line 107 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 108 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlPrioTC;

            } else
            {
                
                #line 111 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 112 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 114 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (4U == type) {
            
            #line 116 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype || 6U == subtype || 7U == subtype) {
                
                #line 118 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 119 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

            } else
            {
                
                #line 123 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 124 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 126 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (2U == type) {
            
            #line 128 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype) {
                
                #line 130 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 131 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlPrioTC;

            } else
            {
                
                #line 134 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 135 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 138 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (3U == type) {
            
            #line 140 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (5U == subtype || 6U == subtype || 31U == subtype) {
                
                #line 142 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 143 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

            } else
            {
                
                #line 148 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 149 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 152 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (20U == type) {
            
            #line 154 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype || 3U == subtype) {
                
                #line 156 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 157 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlBKGTC;

            } else
            {
                
                #line 162 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 163 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 166 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (5U == type) {
            
            #line 168 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (5U == subtype || 6U == subtype) {
                
                #line 170 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 171 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

            } else
            {
                
                #line 176 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 177 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 180 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (12U == type) {
            
            #line 182 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype || 2U == subtype || 5U == subtype || 6U == subtype) {
                
                #line 184 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 185 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

            } else
            {
                
                #line 190 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 191 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 194 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (19U == type) {
            
            #line 196 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype || 2U == subtype || 4U == subtype || 5U == subtype) {
                
                #line 198 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 199 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlHK_FDIRTC;

            } else
            {
                
                #line 204 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 205 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 207 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (128U == type) {
            
            #line 209 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (1U == subtype) {
                
                #line 211 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 212 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlPrioTC;

            } else
            {
                
                #line 216 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 217 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        #line 219 "src/obdh/pus/services/service1/tc_acceptance.fin"
        if (6U == type) {
            
            #line 221 "src/obdh/pus/services/service1/tc_acceptance.fin"
            if (2U == subtype || 5U == subtype || 9U == subtype) {
                
                #line 223 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Accepted;

                #line 224 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.execution_status._variant = TCExecutionCtrl__ExecCtrlBKGTC;

            } else
            {
                
                #line 229 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

                #line 230 "src/obdh/pus/services/service1/tc_acceptance.fin"
                tc_status.error_code._variant = TCErrorType__SubTypeError;

            }

        } else
        {
            
            #line 234 "src/obdh/pus/services/service1/tc_acceptance.fin"
            tc_status.acceptation_status._variant = TCAcceptationStatus__Rejected;

            #line 235 "src/obdh/pus/services/service1/tc_acceptance.fin"
            tc_status.error_code._variant = TCErrorType__TypeError;

        }

    }

    #line 241 "src/obdh/pus/services/service1/tc_acceptance.fin"
    return tc_status;

}
