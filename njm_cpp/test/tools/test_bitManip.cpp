#include <gtest/gtest.h>
#include <glog/logging.h>
#include "tools/bitManip.hpp"
#include "tools/random.hpp"

namespace njm {
namespace tools{


TEST(TestBitManip, ActiveSet) {
    boost::dynamic_bitset<> bs(4);

    bs.set(1);
    bs.set(3);

    std::vector<uint32_t> active = active_set(bs);
    EXPECT_EQ(active.size(), 2);
    EXPECT_EQ(active.at(0), 1);
    EXPECT_EQ(active.at(1), 3);

    bs.reset();
    bs.set(0);
    bs.set(3);

    active = active_set(bs);
    EXPECT_EQ(active.size(), 2);
    EXPECT_EQ(active.at(0), 0);
    EXPECT_EQ(active.at(1), 3);

    bs.set();

    active = active_set(bs);
    EXPECT_EQ(active.size(), 4);
    EXPECT_EQ(active.at(0), 0);
    EXPECT_EQ(active.at(1), 1);
    EXPECT_EQ(active.at(2), 2);
    EXPECT_EQ(active.at(3), 3);


    bs.reset();

    active = active_set(bs);
    EXPECT_EQ(active.size(), 0);
}

TEST(TestBitManip, InactiveSet) {
    boost::dynamic_bitset<> bs(4);

    bs.set(1);
    bs.set(3);

    std::vector<uint32_t> inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 2);
    EXPECT_EQ(inactive.at(0), 0);
    EXPECT_EQ(inactive.at(1), 2);

    bs.reset();
    bs.set(0);
    bs.set(3);

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 2);
    EXPECT_EQ(inactive.at(0), 1);
    EXPECT_EQ(inactive.at(1), 2);

    bs.set();

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 0);

    bs.reset();

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 4);
    EXPECT_EQ(inactive.at(0), 0);
    EXPECT_EQ(inactive.at(1), 1);
    EXPECT_EQ(inactive.at(2), 2);
    EXPECT_EQ(inactive.at(3), 3);
}

TEST(TestBitManip, BothSets) {
    boost::dynamic_bitset<> bs(4);

    bs.set(1);
    bs.set(3);

    std::vector<uint32_t> active = active_set(bs);
    EXPECT_EQ(active.size(), 2);
    EXPECT_EQ(active.at(0), 1);
    EXPECT_EQ(active.at(1), 3);
    std::vector<uint32_t> inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 2);
    EXPECT_EQ(inactive.at(0), 0);
    EXPECT_EQ(inactive.at(1), 2);

    bs.reset();
    bs.set(0);
    bs.set(3);

    active = active_set(bs);
    EXPECT_EQ(active.size(), 2);
    EXPECT_EQ(active.at(0), 0);
    EXPECT_EQ(active.at(1), 3);

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 2);
    EXPECT_EQ(inactive.at(0), 1);
    EXPECT_EQ(inactive.at(1), 2);

    bs.set();

    active = active_set(bs);
    EXPECT_EQ(active.size(), 4);
    EXPECT_EQ(active.at(0), 0);
    EXPECT_EQ(active.at(1), 1);
    EXPECT_EQ(active.at(2), 2);
    EXPECT_EQ(active.at(3), 3);

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 0);

    bs.reset();

    active = active_set(bs);
    EXPECT_EQ(active.size(), 0);

    inactive = inactive_set(bs);
    EXPECT_EQ(inactive.size(), 4);
    EXPECT_EQ(inactive.at(0), 0);
    EXPECT_EQ(inactive.at(1), 1);
    EXPECT_EQ(inactive.at(2), 2);
    EXPECT_EQ(inactive.at(3), 3);
}

TEST(TestBitManip, CombineSets) {
    boost::dynamic_bitset<> one(4);
    boost::dynamic_bitset<> two(4);

    one.set(2);
    one.set(3);

    two.set(1);
    two.set(3);

    std::vector<uint32_t> combined = combine_sets(one, two);
    EXPECT_EQ(combined.size(), 4);
    EXPECT_EQ(combined.at(0), 0);
    EXPECT_EQ(combined.at(1), 1);
    EXPECT_EQ(combined.at(2), 2);
    EXPECT_EQ(combined.at(3), 3);

    combined = combine_sets(two, one);
    EXPECT_EQ(combined.size(), 4);
    EXPECT_EQ(combined.at(0), 0);
    EXPECT_EQ(combined.at(1), 2);
    EXPECT_EQ(combined.at(2), 1);
    EXPECT_EQ(combined.at(3), 3);
}

TEST(TestBitManip, TestReverseBits) {
    uint32_t i = 0;

    Rng rng;
    for (uint32_t i = 0; i < 1e6; ++i) {
        uint32_t num = rng.rint(0, 1 << 16);
        uint32_t num_rev = reverse_bits(num);

        boost::dynamic_bitset<> num_bs(32,num);
        boost::dynamic_bitset<> num_rev_bs(32,num_rev);

        std::string num_str;
        boost::to_string(num_bs, num_str);
        std::string num_rev_str;
        boost::to_string(num_rev_bs, num_rev_str);
        std::reverse(num_rev_str.begin(), num_rev_str.end());

        EXPECT_EQ(num_str, num_rev_str);
    }
}


} // namespace tools
} // namespace njm


int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
