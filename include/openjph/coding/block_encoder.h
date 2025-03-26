#ifndef OPENJPH_CODING_BLOCK_ENCODER_H
#define OPENJPH_CODING_BLOCK_ENCODER_H

#pragma once

#include <openjph/common.h>

namespace openjph {
    
    class mem_elastic_allocator;
    struct coded_lists;

    namespace coding {
        class BlockEncoder {
            public:
                virtual ~BlockEncoder() {};
                // TODO: reduce the number of parameters here by grouping related items into a struct or make them data members of this class
                virtual void Encode(
                    ui64* buf, 
                    ui32 missing_msbs, 
                    ui32 num_passes,
                    ui32 width, 
                    ui32 height, 
                    ui32 stride,
                    ui32* lengths,
                    mem_elastic_allocator *elastic,
                    coded_lists *& coded);
        };
    }
}
#endif