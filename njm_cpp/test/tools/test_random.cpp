#include <gtest/gtest.h>
#include <glog/logging.h>

#include "njm_cpp/tools/random.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/skewness.hpp>

namespace njm {
namespace tools{

namespace ba = boost::accumulators;

TEST(TestRandom, TestRunif) {
    njm::tools::Rng rng;
    const uint32_t num_vals(10000000);
    std::vector<double> vals(num_vals);
    std::for_each(vals.begin(), vals.end(),
            [&rng] (double & x_) {
                x_ = rng.runif_01();
            });

    ba::accumulator_set<double,
                        ba::features< ba::tag::mean,
                                      ba::tag::variance,
                                      ba::tag::skewness,
                                      ba::tag::kurtosis> > acc;
    std::for_each(vals.begin(), vals.end(),
            [&acc] (const double & x_) {
                acc(x_);
            });

    EXPECT_NEAR(ba::mean(acc), 0.5, 1e-3);
    EXPECT_NEAR(ba::variance(acc), 1./12., 1e-3);
    EXPECT_NEAR(ba::skewness(acc), 0.0, 1e-3);
    EXPECT_NEAR(ba::kurtosis(acc), -6.0 / 5.0, 1e-2);
}


TEST(TestRandom, TestRnorm) {
    njm::tools::Rng rng;
    const uint32_t num_vals(10000000);
    std::vector<double> vals(num_vals);
    std::for_each(vals.begin(), vals.end(),
            [&rng] (double & x_) {
                x_ = rng.rnorm_01();
            });

    ba::accumulator_set<double,
                        ba::features< ba::tag::mean,
                                      ba::tag::variance,
                                      ba::tag::skewness,
                                      ba::tag::kurtosis> > acc;
    std::for_each(vals.begin(), vals.end(),
            [&acc] (const double & x_) {
                acc(x_);
            });

    EXPECT_NEAR(ba::mean(acc), 0.0, 1e-3);
    EXPECT_NEAR(ba::variance(acc), 1.0, 1e-3);
    EXPECT_NEAR(ba::skewness(acc), 0.0, 1e-3);
    EXPECT_NEAR(ba::kurtosis(acc), 0.0, 1e-2);
}


TEST(TestRandom, TestShuffle) {
    njm::tools::Rng rng;
    const uint32_t num_reps(100000);

    std::vector<uint32_t> vals({0, 1, 2, 3});
    ASSERT_EQ(vals.size(), 4);
    const uint32_t num_combos(4 * 3 * 2);

    std::map<std::string, uint32_t> counts;
    for (uint32_t i = 0; i < num_reps; ++i) {
        rng.shuffle(vals);
        std::stringstream ss;
        std::for_each(vals.begin(), vals.end(),
                [&ss] (const uint32_t & x) {
                    ss << x << ",";
                });
        if (counts.find(ss.str()) == counts.end()) {
            counts[ss.str()] = 0;
        }
        ++counts[ss.str()];
    }

    EXPECT_EQ(counts.size(), num_combos);

    std::for_each(counts.begin(), counts.end(),
            [num_reps, num_combos] (
                    const std::pair<std::string, uint32_t> & c) {
                EXPECT_NEAR(c.second / static_cast<double>(num_reps),
                        1.0 / num_combos, 1e-2);

            });
}


} // namespace tools
} // namespace njm


int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
