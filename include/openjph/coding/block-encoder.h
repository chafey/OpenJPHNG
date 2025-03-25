#ifndef OPENJPH_CODING_BLOCK_ENCODER_H
#define OPENJPH_CODING_BLOCK_ENCODER_H

#include <openjph/common.h>

#pragma once

namespace openjph {
    
    class mem_elastic_allocator;
    struct coded_lists;

    namespace coding {
        class BlockEncoder {
            public:
                virtual ~BlockEncoder() {};
                virtual void Encode(ui64* buf, ui32 missing_msbs, ui32 num_passes,
                    ui32 width, ui32 height, ui32 stride,
                    ui32* lengths,
                    mem_elastic_allocator *elastic,
                    coded_lists *& coded);
        };
    }
}
#endif