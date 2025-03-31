#include <gtest/gtest.h>
#include <openjph/mem_fixed_allocator.h>

namespace
{

using namespace openjph;

TEST(OPENJPH_mem_fixed_allocator, HappyPath)
{
    printf("mem_fixed_allocator\n");
    mem_fixed_allocator allocator;
    size_t width = 32;
    size_t height = 32;
    allocator.pre_alloc_data<ui32>(width * height, 0);
    allocator.alloc();
    ui32 *pData = allocator.post_alloc_data<ui32>(width * height, 0);
    ASSERT_NE(pData, nullptr);
}
} // namespace