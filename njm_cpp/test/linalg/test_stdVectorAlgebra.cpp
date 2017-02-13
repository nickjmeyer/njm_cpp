#include <gtest/gtest.h>
#include <glog/logging.h>
#include "linalg/stdVectorAlgebra.hpp"
#include "tools/random.hpp"

namespace njm {
namespace linalg {



TEST(TestStdVectorAlgebra, VectorAddAAndB) {
    const std::vector<double> a = {0.0, 1.0, 1.5, -1.0, -1.5};
    const std::vector<double> b = {0.1, 0.2, -0.1, 0.3, -0.2};

    const std::vector<double> c = {0.1, 1.2, 1.4, -0.7, -1.7};
    const std::vector<double> res = add_a_and_b(a,b);

    ASSERT_EQ(a.size(), b.size());
    ASSERT_EQ(a.size(), c.size());

    EXPECT_EQ(a.size(), res.size());
    for (uint32_t i = 0; i < a.size(); ++i) {
        EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
            << "Failed for index i, a = " << a.at(i) << " and b = " << b.at(i);
    }
}

TEST(TestStdVectorAlgebra, VectorAddBToA) {
    std::vector<double> a = {0.0, 1.0, 1.5, -1.0, -1.5};
    const std::vector<double> b = {0.1, 0.2, -0.1, 0.3, -0.2};

    const std::vector<double> c = {0.1, 1.2, 1.4, -0.7, -1.7};
    add_b_to_a(a,b);

    ASSERT_EQ(a.size(), b.size());
    ASSERT_EQ(a.size(), c.size());
    for (uint32_t i = 0; i < a.size(); ++i) {
        EXPECT_NEAR(a.at(i), c.at(i), 1e-14)
            << "Failed for index i, a = " << a.at(i) << " and b = " << b.at(i);
    }
}

TEST(TestStdVectorAlgebra, ScalarAddAAndB) {
    const std::vector<double> a = {0.0, 1.0, 1.5, -1.0, -1.5};
    const std::vector<double> b = {0.1, 0.2, -0.1, 0.3, -0.2};

    uint32_t index = 0;
    {
        const std::vector<double> c = {0.1, 1.1, 1.6, -0.9, -1.4};
        const std::vector<double> res = add_a_and_b(a,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {0.2, 1.2, 1.7, -0.8, -1.3};
        const std::vector<double> res = add_a_and_b(a,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {-0.1, 0.9, 1.4, -1.1, -1.6};
        const std::vector<double> res = add_a_and_b(a,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {0.3, 1.3, 1.8, -0.7, -1.2};
        const std::vector<double> res = add_a_and_b(a,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {-0.2, 0.8, 1.3, -1.2, -1.7};
        const std::vector<double> res = add_a_and_b(a,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;
}

TEST(TestStdVectorAlgebra, ScalarAddBToA) {
    const std::vector<double> a = {0.0, 1.0, 1.5, -1.0, -1.5};
    const std::vector<double> b = {0.1, 0.2, -0.1, 0.3, -0.2};

    uint32_t index = 0;
    {
        const std::vector<double> c = {0.1, 1.1, 1.6, -0.9, -1.4};
        std::vector<double> res = a;
        add_b_to_a(res,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {0.2, 1.2, 1.7, -0.8, -1.3};
        std::vector<double> res = a;
        add_b_to_a(res,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {-0.1, 0.9, 1.4, -1.1, -1.6};
        std::vector<double> res = a;
        add_b_to_a(res,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {0.3, 1.3, 1.8, -0.7, -1.2};
        std::vector<double> res = a;
        add_b_to_a(res,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;

    {
        const std::vector<double> c = {-0.2, 0.8, 1.3, -1.2, -1.7};
        std::vector<double> res = a;
        add_b_to_a(res,b.at(index));

        ASSERT_EQ(a.size(), b.size());
        ASSERT_EQ(a.size(), c.size());

        EXPECT_EQ(a.size(), res.size());
        for (uint32_t i = 0; i < a.size(); ++i) {
            EXPECT_NEAR(res.at(i), c.at(i), 1e-14)
                << "Failed for element i = " << i << " with a = " << a.at(i)
                << " and b = " << b.at(index);
        }
    }
    ++index;
}


TEST(TestStdVectorAlgebra, TestDotAAndB) {
    const std::vector<double> x({1, 2, 3, 4, 5});
    const std::vector<double> y({1, -2, 3, -4, 5});
    EXPECT_NEAR(dot_a_and_b(x, y), 15.0, 1e-12);
}



} // namespace linalg
} // namespace njm


int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
