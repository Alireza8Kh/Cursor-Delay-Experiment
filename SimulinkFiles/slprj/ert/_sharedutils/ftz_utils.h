/*
* Copyright 2023 The MathWorks, Inc.
*
* Abstract
*   Utilities for controlling subnormal behavior.
*/

#ifndef _FTZ_UTILS_H_
#define _FTZ_UTILS_H_

#if defined(__aarch64__)
#include "stdint.h"

#define _MM_FLUSH_ZERO_MASK (0x8000U)
#define _MM_FLUSH_ZERO_ON (0x8000U)
#define _MM_FLUSH_ZERO_OFF (0x0000U)

/**
 * @struct fcpr_bitfield
 * @var res0 bits 0-15 reserved
 * @var res1 bits 16-21 reserved
 * @var bit22 bit22
 * @var bit23 bit23
 * @var bit24 bit24 Controls Flush-to-Zero (FTZ) behavior
 * @var res2 bits 24-31 reserved
 * @var res3 bits32-63
 */

typedef struct {
    uint16_t res0;
    uint8_t res1 : 6;
    uint8_t bit22 : 1;
    uint8_t bit23 : 1;
    uint8_t bit24 : 1;
    uint8_t res2 : 7;
    uint32_t res3;
} fpcr_bitfield;

static union {
    fpcr_bitfield field;
    uint64_t value;
} r;

static inline void _setFlushZeroMode( int flag) {
    __asm__ __volatile__("mrs %0, FPCR" : "=r"(r.value)); /* read fpcr contents to r */
    /* Set the bitfield in r from flag*/
    r.field.bit24 = (flag & _MM_FLUSH_ZERO_MASK) == _MM_FLUSH_ZERO_ON;
    __asm__ __volatile__("msr FPCR, %0" :: "r"(r)); /* write contents of r to fpcr*/
}

static inline uint32_t _getFlushZeroMode(void) {
    /*Read fpcr contents to r*/
    __asm__ __volatile__("mrs %0, FPCR" : "=r"(r.value));
    return r.value ? _MM_FLUSH_ZERO_ON : _MM_FLUSH_ZERO_OFF;
}

#define _MM_SET_FLUSH_ZERO_MODE(ST) _setFlushZeroMode(ST)
#define _MM_GET_FLUSH_ZERO_MODE() _getFlushZeroMode()
/* END ARM MAPPINGS */
#else
/* SSE Mappings */
#include "xmmintrin.h"
#endif

#endif /* _FTZ_UTILS_H_*/
