#pragma once

#include "common.h"
#include <cstddef>

namespace openjph {
    struct coded_lists
    {
      coded_lists(ui32 size)
      {
        next_list = NULL;
        avail_size = buf_size = size;
        this->buf = (ui8*)this + sizeof(coded_lists);
      }
  
      coded_lists* next_list;
      ui32 buf_size;
      ui32 avail_size;
      ui8* buf;
    };

}