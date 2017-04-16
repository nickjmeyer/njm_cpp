#include <njm_cpp/linalg/stdVectorAlgebra.hpp>
#include <glog/logging.h>

#include <cmath>
#include <cblas.h>

namespace njm {
namespace linalg {



std::vector<double> add_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b) {
    const uint32_t a_size = a.size();
    CHECK_EQ(a_size, b.size());
    std::vector<double> res;
    res.reserve(a_size);
    for (uint32_t i = 0; i < a_size; ++i) {
        res.push_back(a.at(i) + b.at(i));
    }
    return res;
}

std::vector<double> add_a_and_b(const std::vector<double> & a,
        const double & b) {
    const uint32_t a_size = a.size();
    std::vector<double> res;
    res.reserve(a_size);
    for (uint32_t i = 0; i < a_size; ++i) {
        res.push_back(a.at(i) + b);
    }
    return res;
}

void add_b_to_a(std::vector<double> & a, const std::vector<double> & b) {
    const uint32_t a_size = a.size();
    CHECK_EQ(a_size, b.size());
    for (uint32_t i = 0; i < a_size; ++i) {
        a.at(i) += b.at(i);
    }
}

void add_b_to_a(std::vector<double> & a, const double & b) {
    const uint32_t a_size = a.size();
    for (uint32_t i = 0; i < a_size; ++i) {
        a.at(i) += b;
    }
}

std::vector<double> mult_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b) {
    const uint32_t a_size = a.size();
    CHECK_EQ(a_size, b.size());
    std::vector<double> res;
    res.reserve(a_size);
    for (uint32_t i = 0; i < a_size; ++i) {
        res.push_back(a.at(i) * b.at(i));
    }
    return res;
}

std::vector<double> mult_a_and_b(const std::vector<double> & a,
        const double & b) {
    const uint32_t a_size = a.size();
    std::vector<double> res;
    res.reserve(a_size);
    for (uint32_t i = 0; i < a_size; ++i) {
        res.push_back(a.at(i) * b);
    }
    return res;
}

void mult_b_to_a(std::vector<double> & a, const std::vector<double> & b) {
    const uint32_t a_size = a.size();
    CHECK_EQ(a_size, b.size());
    for (uint32_t i = 0; i < a_size; ++i) {
        a.at(i) *= b.at(i);
    }
}

void mult_b_to_a(std::vector<double> & a, const double & b) {
    const uint32_t a_size = a.size();
    for (uint32_t i = 0; i < a_size; ++i) {
        a.at(i) *= b;
    }
}

std::vector<double> outer_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b) {
    std::vector<double> outer;
    const uint32_t a_size = a.size();
    const uint32_t b_size = b.size();
    outer.reserve(a_size * b_size);
    for (uint32_t i = 0; i < a_size; ++i) {
        for (uint32_t j = 0; j < b_size; ++j) {
            outer.push_back(a.at(i) * b.at(j));
        }
    }
    return outer;
}

double l2_norm_sq(const std::vector<double> & a) {
    const uint32_t size = a.size();

    double norm = 0.0;
    for (uint32_t i = 0; i < size; ++i) {
        norm += a.at(i) * a.at(i);
    }

    return norm;
}

double l2_norm(const std::vector<double> & a) {
    return std::sqrt(l2_norm_sq(a));
}

void recip(std::vector<double> & a) {
    std::for_each(a.begin(), a.end(),
            [] (double & x) {
                x = 1.0 / x;
            });
}

std::vector<double> recip_of(const std::vector<double> & a) {
    std::vector<double> a_recip;
    const uint32_t size = a.size();
    a_recip.reserve(size);
    for (uint32_t i = 0; i < size; ++i) {
        a_recip.push_back(1.0 / a.at(i));
    }
    return a_recip;
}


} // namespace linalg
} // namespace njm
