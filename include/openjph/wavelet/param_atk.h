#pragma once
#include <openjph/common.h>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include "lifting_step.h"

namespace openjph {

    class infile_base;

    namespace wavelet {

        using namespace openjph;

        // TODO: make this a class
        // TODO: move the method implementations into a .cc file to hide it and reduce the #includes needed above
        struct param_atk
        {
          // Limitations:
          // Arbitrary filters (ARB) are not supported
          // Up to 6 steps are supported -- more than 6 are not supported
          // Only one coefficient per step -- first order filter
          // Only even-indexed subsequence in first reconstruction step,
          //   m_init = 0 is supported

        public: // member functions
          param_atk() { init(); }
          ~param_atk() {
            if (next && alloced_next) {
              delete next;
              next = NULL;
            }
            if (d != NULL && d != d_store) {
              delete[] d;
              init(false);
            }
          }
          bool read(infile_base *file);
          bool read_coefficient(infile_base *file, float &K);
          bool read_coefficient(infile_base *file, si16 &K);
          void init(bool clear_all = true) {
            if (clear_all)
            {
              Latk = Satk = 0;
              Katk = 0.0f;
              Natk = 0;
              d = NULL;
              max_steps = 0;
              memset(d_store, 0, sizeof(d_store));
              next = NULL;
              alloced_next = false;
            }
            d = d_store; max_steps = sizeof(d_store) / sizeof(lifting_step);
          }
          void init_irv97();
          void init_rev53();
          void link(param_atk* next)
          { assert(this->next == NULL); this->next = next; alloced_next = false; }

          ui8 get_index() const { return (ui8)(Satk & 0xFF); }
          int get_coeff_type() const { return (Satk >> 8) & 0x7; }
          bool is_whole_sample() const { return (Satk & 0x800) != 0; }
          bool is_reversible() const { return (Satk & 0x1000) != 0; }
          bool is_m_init0() const { return (Satk & 0x2000) == 0; }
          bool is_using_ws_extension() const { return (Satk & 0x4000) != 0; }
          const param_atk* get_atk(int index) const;
          const lifting_step* get_step(ui32 s) const
          { assert(s < Natk); return d + s; }
          ui32 get_num_steps() const { return Natk; }
          float get_K() const { return Katk; }

        private: // member variables
          ui16 Latk;         // structure length
          ui16 Satk;         // carries a variety of information
          float Katk;        // only for irreversible scaling factor K
          ui8 Natk;          // number of lifting steps
          lifting_step* d;   // pointer to data, initialized to d_store
          int max_steps;     // maximum number of steps without memory allocation
          lifting_step d_store[6];   // lifting step coefficient
          param_atk* next;   // used for chaining if more than one atk segment
                             // exist in the codestream
          bool alloced_next; // true if next was allocated, not just set to an
                             // existing object
        };
    };
};
