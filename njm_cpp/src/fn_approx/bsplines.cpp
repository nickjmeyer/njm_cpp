#include <njm_cpp/fn_approx/bsplines.hpp>

#include <glog/logging.h>


namespace njm {
namespace fn_approx {

Bspline::Bspline(const uint32_t & degree,
        const std::vector<double> & knots)
    : degree_(degree), num_knots_(knots.size()), knots_(knots) {
}


double Bspline::eval_one_basis(const double & x, const double & i,
        const double & k) {
    if (i < 0) {
        return 0.0;
    } else if (i + k + 1 >= this->num_knots_) {
        return 0.0;
    } else if (k == 0) {
        if (this->knots_.at(i) <= x && x < this->knots_.at(i + 1)) {
            return 1.0;
        } else {
            return 0.0;
        }
    } else {
        // evaluate first term
        const double first_numer = x - this->knots_.at(i);
        const double first_denom = this->knots_.at(i + k) - this->knots_.at(i);
        double first = this->eval_one_basis(x, i, k - 1);

        if (first > 0.0) {
            first *= first_numer / first_denom;
        }

        // evaluate second term
        const double second_numer = this->knots_.at(i + k + 1) - x;
        const double second_denom = this->knots_.at(i + k + 1)
            - this->knots_.at(i + 1);
        double second = this->eval_one_basis(x, i + 1, k - 1);

        if (second > 0.0) {
            second *= second_numer / second_denom;
        }

        return first + second;
    }
}


std::vector<double> Bspline::eval_basis(const double & x) {
    const uint32_t num_fns = this->num_knots_ - this->degree_ - 1;

    std::vector<double> basis;
    basis.reserve(num_fns);

    for (uint32_t i = 0; i < num_fns; ++i) {
        basis.push_back(this->eval_one_basis(x, i, this->degree_));
    }

    return basis;
}


double Bspline::deriv(const double & x, const uint32_t & deriv_degree,
        const uint32_t & i, const uint32_t & k) {
    if (deriv_degree == 0) {
        return this->eval_one_basis(x, i, k);
    } else if (k < 2) {
        return 0.0;
    } else {
        const double first_denom = this->knots_.at(i + k)
            - this->knots_.at(i + 1);
        const double first = this->deriv(x, deriv_degree - 1,
                i + 1, k - 1);

        const double second_denom = this->knots_.at(i + k - 1)
            - this->knots_.at(i);
        const double second = this->deriv(x, deriv_degree - 1,
                i, k - 1);

        return (k - 1) * (first / first_denom + second / second_denom);
    }
}


double Bspline::deriv(const double & x) {
    return this->deriv(x, 1);
}


double Bspline::deriv(const double & x, const uint32_t & deriv_degree) {
    CHECK_GT(deriv_degree, 0)
        << "For derivative degree 0, just use Bspline::eval";

    const uint32_t num_fns = this->num_knots_ - this->degree_ - 1;

    double value = 0.0;
    for (uint32_t i = 0; i < num_fns; ++i) {
        value += this->deriv(x, deriv_degree, i, this->degree_);
    }

    return value;
}

double Bspline::integ(const double & x, const uint32_t & i,
        const uint32_t & k) {
    const double knot_a = this->knot_.at(i + k + 1);
    // TODO: finish integration function
}


double Bspline::integ(const double & x_min, const double & x_max) {
    const uint32_t num_fns = this->num_knots_ - this->degree_ - 1;

    double value = 0.0;
    for (uint32_t i = 0; i < num_fns; ++i) {
        value += this->integ_helper(x_max, i, this->degree - 1);
        value -= this->integ_helper(x_min, i, this->degree - 1);

        value += this->integ_helper(x_max, i + 1, this->degree - 1);
        value -= this->integ_helper(x_min, i + 1, this->degree - 1);
    }
}


} // namespace fn_approx
} // namespace njm
