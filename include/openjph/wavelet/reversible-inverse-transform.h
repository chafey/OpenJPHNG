#ifndef OPENJPH_WAVELET_REVERSIBLE_INVERSE_TRANSFORM_H
#define OPENJPH_WAVELET_REVERSIBLE_INVERSE_TRANSFORM_H

#include <openjph/common.h>
#include <cassert>
//#include <cstddef>
#include <cstdio>
#include <cstring>

#pragma once

namespace openjph {

    class line_buf;

    namespace wavelet {

        using namespace openjph;
        using namespace std;

        union lifting_step;
        class param_atk;

        namespace reversible {
            // TODO: See if we can use the same interface for both reversible and irreversible
            class InverseTransform {
                public:
                    virtual ~InverseTransform() {};
                    virtual void VerticalStep() = 0;
                    virtual void HorizonatlSyn() = 0;
            };
        }; // namespace reversible
    }; // namespace wavelet
}; // namespace openjph
#endif
