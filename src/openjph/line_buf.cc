#include <openjph/line_buf.h>

namespace openjph {



  ////////////////////////////////////////////////////////////////////////////
  template<>
  void line_buf::wrap(si32 *buffer, size_t num_ele, ui32 pre_size)
  {
    this->i32 = buffer;
    this->size = num_ele;
    this->pre_size = pre_size;
    this->flags = LFT_32BIT | LFT_INTEGER;
  }

  ////////////////////////////////////////////////////////////////////////////
  template<>
  void line_buf::wrap(float *buffer, size_t num_ele, ui32 pre_size)
  {
    this->f32 = buffer;
    this->size = num_ele;
    this->pre_size = pre_size;
    this->flags = LFT_32BIT;
  }

  ////////////////////////////////////////////////////////////////////////////
  template<>
  void line_buf::wrap(si64 *buffer, size_t num_ele, ui32 pre_size)
  {
    this->i64 = buffer;
    this->size = num_ele;
    this->pre_size = pre_size;
    this->flags = LFT_64BIT | LFT_INTEGER;
  }

}