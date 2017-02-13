#include <gtest/gtest.h>
#include <glog/logging.h>
#include <cstdint>
#include <thread>
#include <njm_cpp/thread/pool.hpp>
#include <njm_cpp/data/result.hpp>

namespace njm {
namespace thread {


TEST(TestPool, Counting) {
    const uint32_t num_threads = std::thread::hardware_concurrency();

    Pool p(num_threads);

    const int32_t N = 1000 * num_threads;

    std::vector<std::shared_ptr<data::Result<uint32_t> > > results;
    for (uint32_t i = 0; i < N; ++i) {
        const std::shared_ptr<data::Result<uint32_t> > ptr(
                new data::Result<uint32_t>);
        results.push_back(ptr);
        p.service()->post(std::bind(
                        [](const std::shared_ptr<data::Result<uint32_t> > & r,
                                const uint32_t & i) {
                            r->set(i);
                        }, ptr, i));
    }

    p.join();

    for (uint32_t i = 0; i < N; ++i) {
        EXPECT_EQ(results.at(i)->get(), i);
    }
}


} // namespace thread
} // namespace njm


int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
