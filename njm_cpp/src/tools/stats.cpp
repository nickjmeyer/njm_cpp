#include "tools/stats.hpp"


namespace njm {
namespace tools {


std::pair<double, double> mean_and_var(const std::vector<double> & vec) {
    const uint32_t size = vec.size();
    std::pair<double, double> stats(0., 0.);
    for (uint32_t i = 0; i < size; ++i) {
        const double temp_mean = stats.first;
        stats.first += (vec.at(i) - temp_mean) / (i + 1);
        stats.second += (vec.at(i) - temp_mean) * (vec.at(i) - stats.first);
    }

    if (size > 1) {
        stats.second = stats.second / (size - 1);
    }

    return stats;
}


} // namespace tools
} // namespace njm
