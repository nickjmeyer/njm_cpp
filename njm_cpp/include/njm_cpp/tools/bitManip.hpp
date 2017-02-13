#ifndef NJM_CPP_BIT_MANIP_HPP
#define NJM_CPP_BIT_MANIP_HPP

#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <cstdint>

namespace njm {
namespace tools {


std::vector<uint32_t> active_set(const boost::dynamic_bitset<> & bs);

std::vector<uint32_t> inactive_set(const boost::dynamic_bitset<> & bs);

std::pair<std::vector<uint32_t>,
          std::vector<uint32_t>
          > both_sets(const boost::dynamic_bitset<> & bs);

std::vector<uint32_t> combine_sets(const boost::dynamic_bitset<> & one,
        const boost::dynamic_bitset<> & two);

uint32_t reverse_bits(const uint32_t & x);


} // namespace tools
} // namespace njm


#endif // NJM_CPP_BIT_MANIP_HPP
