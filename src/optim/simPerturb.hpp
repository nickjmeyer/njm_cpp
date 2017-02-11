#ifndef SIM_PERTURB_HPP
#define SIM_PERTURB_HPP

#include "optim.hpp"

namespace njm::optim {


class SimPerturb : public Optim {
private:
    const double c_;
    const double t_;
    const double a_;
    const double b_;
    const double ell_;
    const double min_step_size_;

    double step_size() const;

public:
    SimPerturb(const std::function<double(const std::vector<double> & ,
                    void * const)> & f,
            const std::vector<double> & par,
            void * const data,
            const double & c,
            const double & t,
            const double & a,
            const double & b,
            const double & ell,
            const double & min_step_size);

    SimPerturb(const SimPerturb & other) = delete;

    Optim::ErrorCode step();
};


} // namespace njm::optim


#endif // SIM_PERTURB_HPP
