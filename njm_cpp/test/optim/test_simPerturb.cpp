#include <gtest/gtest.h>
#include <glog/logging.h>

#include <njm_cpp/optim/simPerturb.hpp>
#include <njm_cpp/tools/random.hpp>

#include <chrono>
#include <thread>


namespace njm {
namespace optim {


TEST(TestSimPerturb, IndependentQuadratic) {
    tools::Rng rng;
    const uint32_t n = 5;
    const std::vector<double> truth = {1., 2., 3., 4., 5.};
    auto f = [&n, &rng, &truth] (const std::vector<double> & par,
            const std::vector<double> & par_orig) -> double
        {
            double res = 0.0;
            for (uint32_t i = 0; i < n; ++i) {
                const double rand = rng.rnorm(truth.at(i), 1);
                res += (rand - par.at(i))*(rand - par.at(i));
            }
            return res;
        };

    std::vector<double> start;
    for (uint32_t i = 0; i < n; ++i) {
        start.push_back(rng.rnorm(-10, 1));
    }

    SimPerturb sp(f, start, 2.0, 0.15, 1.0, 1, 0.8, 0.0001);

    ErrorCode ec;
    do {
        ec = sp.step();
    } while(ec == ErrorCode::CONTINUE);
    CHECK_EQ(ec, ErrorCode::SUCCESS);

    const std::vector<double> par = sp.par();
    for (uint32_t i = 0; i < n; ++i) {
        EXPECT_LT(std::abs((par.at(i) - truth.at(i)) / truth.at(i)) , 0.1);
    }
}



} // namespace optim
} // namespace njm

int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
