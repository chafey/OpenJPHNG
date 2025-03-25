#pragma once

#include "common.h"
#include <cstddef>

namespace openjph {
    // TODO: Make this a class as the data members have dependencies on each other.    
    // TODO: rename to CodedLists to comply with google c++ style guide
    struct coded_lists
    {
      coded_lists(ui32 size)
      {
        next_list = NULL;
        avail_size = buf_size = size;
        // TODO: this is dangerous - make it safer 
        this->buf = (ui8*)this + sizeof(coded_lists);
      }
  
      // TODO: Make these private and add public access/mutators to avoid inconsistent state
      coded_lists* next_list;
      ui32 buf_size;
      ui32 avail_size;
      ui8* buf;
    };

}