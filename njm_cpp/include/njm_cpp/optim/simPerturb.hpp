#ifndef NJM_CPP_SIM_PERTURB_HPP
#define NJM_CPP_SIM_PERTURB_HPP

#include <njm_cpp/optim/optim.hpp>

namespace njm {
namespace optim {



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

    ErrorCode step();
};



} // namespace optim
} // namespace njm


#endif // NJM_CPP_SIM_PERTURB_HPP
