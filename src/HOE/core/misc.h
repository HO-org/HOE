#pragma once
#include <stdint.h>

#define HF_RED { 255, 0, 0, 255 }
#define HF_GREEN { 0, 255, 0, 255 }
#define HF_BLUE { 0, 0, 255, 255 }
#define HF_WHITE { 255, 255, 255, 255 }
#define HF_BLACK { 0, 0, 0, 255 }
#define HF_GRAY { 100, 100, 100, 255 }

struct HFColor
{
    uint8_t r, g, b, a;
};

