#pragma once

#include "common.h"

namespace openjph_algo {

    namespace wavelet {

        using namespace openjph;
        using namespace std;

        union lifting_step {
            struct irv_data {
            // si8 Oatk;     // only for arbitrary filter
            // ui8 LCatk;    // number of lifting coefficients in a step
            float Aatk;      // lifting coefficient
            };

            struct rev_data {
            // si8 Oatk;     // only for arbitrary filter, offset of filter
            ui8 Eatk;        // only for reversible, epsilon, the power of 2
            si16 Batk;       // only for reversible, beta, the additive residue
            // ui8 LCatk;    // number of lifting coefficients in a step
            si16 Aatk;       // lifting coefficient
            };

            irv_data irv;
            rev_data rev;
        };
    };
};
