#include "common.h"
#include <cstddef>

#pragma once

namespace openjph {

        /////////////////////////////////////////////////////////////////////////////
        class line_buf
        {
        public:
            enum : ui32 {
                LFT_UNDEFINED  = 0x00, // Type is undefined/uninitialized
                                        // These flags reflects data size in bytes
                LFT_BYTE       = 0x01, // Set when data is 1 byte  (not used)
                LFT_16BIT      = 0x02, // Set when data is 2 bytes (not used)
                LFT_32BIT      = 0x04, // Set when data is 4 bytes
                LFT_64BIT      = 0x08, // Set when data is 8 bytes
                LFT_INTEGER    = 0x10, // Set when data is an integer, in other words
                                        // 32bit integer, not 32bit float
                LFT_SIZE_MASK  = 0x0F, // To extract data size
            };

            line_buf() : size(0), pre_size(0), flags(LFT_UNDEFINED), i32(0) {}

            template<typename T>
                void wrap(T *buffer, size_t num_ele, ui32 pre_size);

            size_t size;
            ui32 pre_size;
            ui32 flags;
            union {
                si32* i32;  // 32bit integer type, used for lossless compression
                si64* i64;  // 64bit integer type, used for lossless compression
                float* f32; // float type, used for lossy compression
                void* p;    // no type is associated with the pointer
            };
        };
};
