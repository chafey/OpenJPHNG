#pragma once

#include <openjph/common.h>

namespace openjph {

    namespace wavelet {

        using namespace openjph;
        using namespace std;

        // TODO: unions should rarely be used as they are confusing.  Get rid of this union or make it part of the private implementation
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
