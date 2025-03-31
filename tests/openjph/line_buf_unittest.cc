#include <gtest/gtest.h>
#include <openjph/line_buf.h>

namespace
{

using namespace openjph;

TEST(OPENJPH_line_buf, HappyPath_si32)
{
    line_buf lineBuf;
    si32 buffer[32];
    lineBuf.wrap<si32>(buffer, 32, 0);
    ASSERT_EQ(lineBuf.i32, buffer);
    ASSERT_EQ(lineBuf.size, 32);
    ASSERT_EQ(lineBuf.pre_size, 0);
    ASSERT_EQ(lineBuf.flags, line_buf::LFT_32BIT | line_buf::LFT_INTEGER);
}
TEST(OPENJPH_line_buf, HappyPath_si64)
{
    line_buf lineBuf;
    si64 buffer[32];
    lineBuf.wrap<si64>(buffer, 32, 0);
    ASSERT_EQ(lineBuf.i64, buffer);
    ASSERT_EQ(lineBuf.size, 32);
    ASSERT_EQ(lineBuf.pre_size, 0);
    ASSERT_EQ(lineBuf.flags, line_buf::LFT_64BIT | line_buf::LFT_INTEGER);
}
TEST(OPENJPH_line_buf, HappyPath_float)
{
    line_buf lineBuf;
    float buffer[32];
    lineBuf.wrap<float>(buffer, 32, 0);
    ASSERT_EQ(lineBuf.f32, buffer);
    ASSERT_EQ(lineBuf.size, 32);
    ASSERT_EQ(lineBuf.pre_size, 0);
    ASSERT_EQ(lineBuf.flags, line_buf::LFT_32BIT);
}
} // namespace