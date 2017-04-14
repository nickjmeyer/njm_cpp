#ifndef NJM_CPP_OPTIM_HPP
#define NJM_CPP_OPTIM_HPP

#include <functional>
#include <cstdint>
#include <njm_cpp/tools/random.hpp>

namespace njm {
namespace optim {

enum ErrorCode {SUCCESS, CONTINUE, ERROR,
                NON_FINITE_PARAMETER, NAN_PARAMETER,
                STARTING_NON_FINITE_PARAMETER, STARTING_NAN_PARAMETER,
                NON_FINITE_GRADIENT, NAN_GRADIENT};

template <typename... Args>
class Optim : public tools::RngClass {
protected:
    const std::function<double(const std::vector<double> &, Args...)> f_;

    std::vector<double> par_;

    const uint32_t par_size_;

    uint32_t completed_steps_;

    bool verbose_;


public:
    Optim(const std::function<double(const std::vector<double> &, Args...)> & f,
            const std::vector<double> & par)
        : f_(f), par_(par), par_size_(par.size()),
          completed_steps_(0), verbose_(false) {
    }


    Optim(const Optim & other) = delete;


    void verbose(const bool & verbose) {
        this->verbose_ = verbose;
    }


    std::vector<double> par() const {
        return this->par_;
    }


    virtual double obj_fn() = 0;


    uint32_t completed_steps() const {
        return this->completed_steps_;
    }


    virtual ErrorCode step() = 0;


    virtual void rng(const std::shared_ptr<tools::Rng> & rng) override {
        this->RngClass::rng(rng);
    }
};


} // namespace optim
} // namespace njm


#endif // NJM_CPP_OPTIM_HPP
