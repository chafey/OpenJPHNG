#ifndef OJPH_ARCH_H
#define OJPH_ARCH_H

#include <cstdio>
#include <cstdint>
#include <cmath>
#include "common.h"
//#include "ojph_defs.h"
 
namespace openjph {
    
    static inline ui32 population_count(ui32 val)
    {
    #if defined(OJPH_COMPILER_MSVC)  \
      && (defined(OJPH_ARCH_X86_64) || defined(OJPH_ARCH_I386))
      return (ui32)__popcnt(val);
    #elif (defined OJPH_COMPILER_GNUC)
      return (ui32)__builtin_popcount(val);
    #else
      val -= ((val >> 1) & 0x55555555);
      val = (((val >> 2) & 0x33333333) + (val & 0x33333333));
      val = (((val >> 4) + val) & 0x0f0f0f0f);
      val += (val >> 8);
      val += (val >> 16);
      return (int)(val & 0x0000003f);
    #endif
    }



    static inline ui32 count_leading_zeros(ui32 val)
    {
    #ifdef OJPH_COMPILER_MSVC
      unsigned long result = 0;
      _BitScanReverse(&result, val);
      return 31 ^ (ui32)result;
    #elif (defined OJPH_COMPILER_GNUC)
      return (ui32)__builtin_clz(val);
    #else
      val |= (val >> 1);
      val |= (val >> 2);
      val |= (val >> 4);
      val |= (val >> 8);
      val |= (val >> 16);
      return 32 - population_count(val);
    #endif
    }


  ////////////////////////////////////////////////////////////////////////////
  // constants
  ////////////////////////////////////////////////////////////////////////////
  #ifndef OJPH_EMSCRIPTEN
    const ui32 byte_alignment = 64; // 64 bytes == 512 bits
    const ui32 log_byte_alignment = 31 - count_leading_zeros(byte_alignment);
    const ui32 object_alignment = 8;
  #else
    const ui32 byte_alignment = 16; // 16 bytes == 128 bits
    const ui32 log_byte_alignment = 31 - count_leading_zeros(byte_alignment);
    const ui32 object_alignment = 8;
    #endif
 
 ////////////////////////////////////////////////////////////////////////////
  // templates for alignment
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  // finds the size such that it is a multiple of byte_alignment
  template <typename T, ui32 N>
  size_t calc_aligned_size(size_t size) {
    size = size * sizeof(T) + N - 1;
    size &= ~((1ULL << (31 - count_leading_zeros(N))) - 1);
    size >>= (63 - count_leading_zeros((ui64)sizeof(T)));
    return size;
  }

  ////////////////////////////////////////////////////////////////////////////
  // moves the pointer to first address that is a multiple of byte_alignment
  template <typename T, ui32 N>
  inline T *align_ptr(T *ptr) {
    intptr_t p = reinterpret_cast<intptr_t>(ptr);
    p += N - 1;
    p &= ~((1ULL << (31 - count_leading_zeros(N))) - 1);
    return reinterpret_cast<T *>(p);
  }

}
#endif