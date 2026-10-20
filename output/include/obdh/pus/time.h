#ifndef OBDH__PUS__TIME_H__
#define OBDH__PUS__TIME_H__

#include <termina.h>

#include "option.h"

typedef struct {
    uint32_t seconds;
    uint16_t finetime;
} CUCTime;

#endif
