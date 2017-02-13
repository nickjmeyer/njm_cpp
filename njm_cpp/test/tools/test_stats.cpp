#include <gtest/gtest.h>
#include <glog/logging.h>
#include "tools/stats.hpp"

namespace njm {
namespace tools {



TEST(TestStats, TestMeanAndVar) {
    const std::vector<double> x = {-1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    const std::pair<double, double> stats = mean_and_var(x);
    EXPECT_NEAR(stats.first, 2.0, 1e-12);
    EXPECT_NEAR(stats.second, 4.666666666666, 1e-12);
}


} // namespace tools
} // namespace njm


int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
