#pragma once
#include "common.h"
#include <__stddef_size_t.h>
#include <stdlib.h>
#include <assert.h>
#include "ojph_arch.h"

namespace openjph {

    /////////////////////////////////////////////////////////////////////////////
    class mem_fixed_allocator
    {
    public:
      mem_fixed_allocator()
      {
        avail_obj = avail_data = store = NULL;
        avail_size_obj = avail_size_data = size_obj = size_data = 0;
      }
      ~mem_fixed_allocator()
      {
        if (store) free(store);
      }
  
      template<typename T>
      void pre_alloc_data(size_t num_ele, ui32 pre_size)
      {
        pre_alloc_local<T, byte_alignment>(num_ele, pre_size, size_data);
      }
  
      template<typename T>
      void pre_alloc_obj(size_t num_ele)
      {
        pre_alloc_local<T, object_alignment>(num_ele, 0, size_obj);
      }
  
      void alloc()
      {
        assert(store == NULL);
        avail_obj = store = malloc(size_data + size_obj);
        avail_data = (ui8*)store + size_obj;
        if (store == NULL)
          throw "malloc failed";
        avail_size_obj = size_obj;
        avail_size_data = size_data;
      }
  
      template<typename T>
      T* post_alloc_data(size_t num_ele, ui32 pre_size)
      {
        return post_alloc_local<T, byte_alignment>
          (num_ele, pre_size, avail_size_data, avail_data);
      }
  
      template<typename T>
      T* post_alloc_obj(size_t num_ele)
      {
        return post_alloc_local<T, object_alignment>
          (num_ele, 0, avail_size_obj, avail_obj);
      }
  
    private:
      template<typename T, int N>
      void pre_alloc_local(size_t num_ele, ui32 pre_size, size_t& sz)
      {
        assert(store == NULL);
        num_ele = calc_aligned_size<T, N>(num_ele);
        size_t total = (num_ele + pre_size) * sizeof(T);
        total += 2*N - 1;
  
        sz += total;
      }
  
      template<typename T, int N>
      T* post_alloc_local(size_t num_ele, ui32 pre_size,
                          size_t& avail_sz, void*& avail_p)
      {
        assert(store != NULL);
        num_ele = calc_aligned_size<T, N>(num_ele);
        size_t total = (num_ele + pre_size) * sizeof(T);
        total += 2*N - 1;
  
        T* p = align_ptr<T, N>((T*)avail_p + pre_size);
        avail_p = (ui8*)avail_p + total;
        avail_sz -= total;
        assert((avail_sz & 0x8000000000000000llu) == 0);
        return p;
      }
  
      void *store, *avail_data, *avail_obj;
      size_t size_data, size_obj, avail_size_obj, avail_size_data;
    };

}