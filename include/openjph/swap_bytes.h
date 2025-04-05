#pragma once

#include "common.h"

namespace openjph
{

//////////////////////////////////////////////////////////////////////////
static inline ui16 swap_byte(ui16 t)
{
    return (ui16)((t << 8) | (t >> 8));
}

//////////////////////////////////////////////////////////////////////////
static inline ui32 swap_byte(ui32 t)
{
    ui32 u = swap_byte((ui16)(t & 0xFFFFu));
    u <<= 16;
    u |= swap_byte((ui16)(t >> 16));
    return u;
}

//////////////////////////////////////////////////////////////////////////
static inline ui64 swap_byte(ui64 t)
{
    ui64 u = swap_byte((ui32)(t & 0xFFFFFFFFu));
    u <<= 32;
    u |= swap_byte((ui32)(t >> 32));
    return u;
}

} // namespace openjph