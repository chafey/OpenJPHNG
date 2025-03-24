#include "common.h"
#include <cstddef>
#include <cstdio>

#pragma once

namespace openjph {

        using namespace openjph;

        ////////////////////////////////////////////////////////////////////////////
        class OJPH_EXPORT infile_base
        {
        public:
        enum seek : int {
            OJPH_SEEK_SET = SEEK_SET,
            OJPH_SEEK_CUR = SEEK_CUR,
            OJPH_SEEK_END = SEEK_END
        };

        virtual ~infile_base() {}

        //read reads size bytes, returns the number of bytes read
        virtual size_t read(void *ptr, size_t size) = 0;
        //seek returns 0 on success
        virtual int seek(si64 offset, enum infile_base::seek origin) = 0;
        virtual si64 tell() = 0;
        virtual bool eof() = 0;
        virtual void close() {}
        };
};
