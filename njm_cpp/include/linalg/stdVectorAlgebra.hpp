#ifndef NJM_CPP_UTILITIES_HPP
#define NJM_CPP_UTILITIES_HPP

#include <vector>
#include <boost/dynamic_bitset.hpp>

namespace njm {
namespace linalg {


std::vector<double> add_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b);

std::vector<double> add_a_and_b(const std::vector<double> & a,
        const double & b);

void add_b_to_a(std::vector<double> & a, const std::vector<double> & b);

void add_b_to_a(std::vector<double> & a, const double & b);

std::vector<double> mult_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b);

std::vector<double> mult_a_and_b(const std::vector<double> & a,
        const double & b);

void mult_b_to_a(std::vector<double> & a, const std::vector<double> & b);

void mult_b_to_a(std::vector<double> & a, const double & b);

double dot_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b);

std::vector<double> outer_a_and_b(const std::vector<double> & a,
        const std::vector<double> & b);

double l2_norm_sq(const std::vector<double> & a);

double l2_norm(const std::vector<double> & a);

void recip(std::vector<double> & a);

std::vector<double> recip_of(const std::vector<double> & a);


} // namespace linalg
} // namespace njm


#endif // NJM_CPP_UTILITIES_HPP
