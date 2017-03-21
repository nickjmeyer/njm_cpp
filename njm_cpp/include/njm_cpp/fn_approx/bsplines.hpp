#ifndef NJM_CPP_B_SPLINES_HPP
#define NJM_CPP_B_SPLINES_HPP

#include <cstdint>
#include <vector>


namespace njm {
namespace fn_approx {


class Bspline {
protected:
    const uint32_t degree_;
    const uint32_t num_knots_;
    const std::vector<double> knots_;

    /**
     * Evaluate one of the basis functions
     *
     * @param x value to evaluate at
     *
     * @param i index of basis function
     *
     * @param k degree of basis function
     */
    double eval_one_basis(const double & x, const double & i,
            const double & k);

    /**
     * Evaluate the derivative to a specified degree
     *
     * @param x value to evaluate at
     *
     * @param deriv_degree degree of the derivative to evaluate
     */
    double deriv(const double & x, const uint32_t & deriv_degree,
            const uint32_t & i, const uint32_t & k);

    /**
     * Helper function for computing integration
     *
     * @param x value to evaluate at
     *
     * @param i basis function index
     *
     * @param k degree of the basis function
     */
    double integ_helper(const double & x, const uint32_t & i,
            const uint32_t & k);

public:
    Bspline(const uint32_t & degree,
            const std::vector<double> & knots);

    virtual ~Bspline() = default;

    /**
     * Evaluate the spline at value x and add basis functions
     *
     * @param x value to evaluate at
     */
    double eval(const double & x);

    /**
     * Evaluate the spline at value x and keep basis functions
     * separate
     *
     * @param x value to evaluate at
     */
    std::vector<double> eval_basis(const double & x);

    /**
     * Evaluate the first derivative at x
     *
     * @param x value to evaluate at
     */
    double deriv(const double & x);

    /**
     * Evaluate the derivative to a specified degree
     *
     * @param x value to evaluate at
     *
     * @param deriv_degree degree of the derivative to evaluate
     */
    double deriv(const double & x, const uint32_t & deriv_degree);

    /**
     * Integrate over a range
     *
     * @param x_min lower integration bound
     *
     * @param x_max upper integration bound
     */
    double integ(const double & x_min, const double & x_max);
};


} // namespace fn_approx
} // namespace njm


#endif // NJM_CPP_B_SPLINES_HPP
