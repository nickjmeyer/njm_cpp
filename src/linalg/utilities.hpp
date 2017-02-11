#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <boost/dynamic_bitset.hpp>

namespace njm::linalg {

std::vector<uint32_t> active_set(const boost::dynamic_bitset<> & bs);

std::vector<uint32_t> inactive_set(const boost::dynamic_bitset<> & bs);

std::pair<std::vector<uint32_t>,
          std::vector<uint32_t>
          > both_sets(const boost::dynamic_bitset<> & bs);

std::vector<uint32_t> combine_sets(const boost::dynamic_bitset<> & one,
        const boost::dynamic_bitset<> & two);

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


std::pair<double, double> mean_and_var(const std::vector<double> & vec);

uint32_t reverse_bits(const uint32_t & x);

} // namespace njm::linalg


#endif // UTILITIES_HPP
