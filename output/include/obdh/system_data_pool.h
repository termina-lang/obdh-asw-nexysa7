#ifndef OBDH__SYSTEM_DATA_POOL_H__
#define OBDH__SYSTEM_DATA_POOL_H__

#include <termina.h>

#include "option.h"

typedef enum {
    DataPoolItem__U32Item,
    DataPoolItem__U8Item,
    DataPoolItem__NoValidPID
} termina__enum__DataPoolItem_t;

typedef struct {
    size_t _0;
} termina__enum__DataPoolItem__U32Item_params_t;

typedef struct {
    size_t _0;
} termina__enum__DataPoolItem__U8Item_params_t;

typedef struct {
    termina__enum__DataPoolItem_t _variant;
    union {
        termina__enum__DataPoolItem__U32Item_params_t U32Item;
        termina__enum__DataPoolItem__U8Item_params_t U8Item;
    };
} DataPoolItem;

DataPoolItem sys_data_pool_get_item(const uint16_t PID);

_Bool sys_data_pool_is_valid_PID(const uint16_t PID);

_Bool sys_data_pool_is_PID_update_via_TC_enabled(const uint16_t PID);

#endif
