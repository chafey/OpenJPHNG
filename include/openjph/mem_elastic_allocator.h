#pragma once

#include "common.h"
#include "coded_lists.h"
#include <stdlib.h> // for free()

namespace openjph {

  class mem_elastic_allocator
    {
      /*
        advantage: allocate large chunks of memory
      */

    public:
      mem_elastic_allocator(ui32 chunk_size)
      : chunk_size(chunk_size)
      { cur_store = store = NULL; total_allocated = 0; }

      ~mem_elastic_allocator()
      {
        while (store) {
          stores_list* t = store->next_store;
          free(store);
          store = t;
        }
      }

      void get_buffer(ui32 needed_bytes, coded_lists*& p);

    private:
      struct stores_list
      {
        stores_list(ui32 available_bytes)
        {
          this->next_store = NULL;
          this->available = available_bytes;
          this->data = (ui8*)this + sizeof(stores_list);
        }
        static ui32 eval_store_bytes(ui32 available_bytes) 
        { // calculates how many bytes need to be allocated
          return available_bytes + (ui32)sizeof(stores_list);
        }
        stores_list *next_store;
        ui32 available;
        ui8* data;
      };

      stores_list *store, *cur_store;
      size_t total_allocated;
      const ui32 chunk_size;
    };

} 