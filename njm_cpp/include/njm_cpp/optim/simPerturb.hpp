#ifndef NJM_CPP_SIM_PERTURB_HPP
#define NJM_CPP_SIM_PERTURB_HPP

#include <njm_cpp/optim/optim.hpp>

namespace njm {
namespace optim {



class SimPerturb : public Optim<const std::vector<double> & > {
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
                    const std::vector<double> &)> & f,
            const std::vector<double> & par,
            const double & c,
            const double & t,
            const double & a,
            const double & b,
            const double & ell,
            const double & min_step_size);

    SimPerturb(const SimPerturb & other) = delete;

    ErrorCode step() override;

    double obj_fn() override;
};



} // namespace optim
} // namespace njm


#endif // NJM_CPP_SIM_PERTURB_HPP
