#include <njm_cpp/optim/simPerturb.hpp>
#include <njm_cpp/linalg/stdVectorAlgebra.hpp>

#include <iostream>
#include <cmath>

namespace njm {
namespace optim {


SimPerturb::SimPerturb(
        const std::function<double(const std::vector<double> & ,
                const std::vector<double> &)> & f,
        const std::vector<double> & par,
        const double & c,
        const double & t,
        const double & a,
        const double & b,
        const double & ell,
        const double & min_step_size)
    : Optim<const std::vector<double> & >(f, par),
    c_(c), t_(t), a_(a), b_(b), ell_(ell), min_step_size_(min_step_size) {
}


ErrorCode SimPerturb::step() {
    if (std::any_of(this->par_.begin(), this->par_.end(),
                    [](const double & x) { return std::isnan(x);})) {
        return STARTING_NAN_PARAMETER;
    } else if (std::any_of(this->par_.begin(), this->par_.end(),
                    [](const double & x) { return !std::isfinite(x);})) {
        return STARTING_NON_FINITE_PARAMETER;
    }

    const double scale = this->c_ /
        std::pow(this->completed_steps_ + 1, this->t_);

    std::vector<double> perturb;
    perturb.reserve(this->par_size_);
    for (uint32_t i = 0; i < this->par_size_; ++i) {
        if (this->rng_->runif_01() < 0.5)
            perturb.push_back(-scale);
        else
            perturb.push_back(scale);
    }

    const std::vector<double> par_plus = linalg::add_a_and_b(this->par(),
            perturb);

    const std::vector<double> par_minus = linalg::add_a_and_b(this->par(),
            linalg::mult_a_and_b(perturb, -1.));

    const double val_plus = this->f_(par_plus, this->par());
    const double val_minus = this->f_(par_minus, this->par());

    // estimate gradient
    const std::vector<double> grad_est(linalg::mult_a_and_b(
                    linalg::recip_of(perturb), (val_plus - val_minus) / 2.0));
    if (std::any_of(grad_est.begin(), grad_est.end(),
                    [] (const double & x) {return std::isnan(x);})) {
        return NAN_GRADIENT;
    } else if (std::any_of(grad_est.begin(), grad_est.end(),
                    [] (const double & x) {return !std::isfinite(x);})) {
        return NON_FINITE_GRADIENT;
    }


    const double step_size = this->a_ /
        std::pow(this->b_ + this->completed_steps_, this->ell_);

    // negative step_size for minimization
    linalg::add_b_to_a(this->par_, linalg::mult_a_and_b(grad_est, - step_size));

    ++this->completed_steps_;

    if (this->verbose_) {
        // evaluate and print
        const double val = this->obj_fn();
        std::cout << "iter: " << this->completed_steps_ << std::endl;
        std::cout << "par:";
        for (uint32_t i = 0; i < this->par_.size(); ++i) {
            std::cout << " " << this->par_.at(i);
        }
        std::cout << std::endl;
        std::cout << "value: " << val << std::endl;
    }

    if (std::any_of(this->par_.begin(), this->par_.end(),
                    [](const double & x) { return std::isnan(x);})) {
        return NAN_PARAMETER;
    } else if (std::any_of(this->par_.begin(), this->par_.end(),
                    [](const double & x) { return !std::isfinite(x);})) {
        return NON_FINITE_PARAMETER;
    } else if (step_size < this->min_step_size_) {
        return SUCCESS;
    } else {
        return CONTINUE;
    }
}


double SimPerturb::obj_fn() {
    return this->f_(this->par_, this->par_);
}


} // namespace optim
} // namespace njm
