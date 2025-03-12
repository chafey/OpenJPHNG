#pragma once

#include <cstdint>

/////////////////////////////////////////////////////////////////////////////
// defines for dll
/////////////////////////////////////////////////////////////////////////////
#if defined(OJPH_OS_WINDOWS) && defined(OJPH_BUILD_SHARED_LIBRARY)
#define OJPH_EXPORT __declspec(dllexport)
#else
#define OJPH_EXPORT
#endif

namespace openjph {
    class noncopyable {
        protected:
            noncopyable() = default;
            ~noncopyable() = default;
            noncopyable(const noncopyable&) = delete;
            noncopyable& operator=(const noncopyable&) = delete;
            noncopyable(noncopyable &&) = delete;
            noncopyable &operator=(noncopyable &&) = delete;
    };

/////////////////////////////////////////////////////////////////////////////
//                               types
/////////////////////////////////////////////////////////////////////////////
typedef uint8_t ui8;
typedef int8_t si8;
typedef uint16_t ui16;
typedef int16_t si16;
typedef uint32_t ui32;
typedef int32_t si32;
typedef uint64_t ui64;
typedef int64_t si64;




}
