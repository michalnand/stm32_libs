#ifndef _SINE_TABLE_H_
#define _SINE_TABLE_H_

#include <stdint.h>

#define SINE_TABLE_SIZE ((uint32_t)256)
#define SINE_VALUE_MAX  ((uint32_t)255) 

extern const unsigned char sine_table[SINE_TABLE_SIZE];

#endif  