#ifndef NJM_CPP_OPTIM_HPP
#define NJM_CPP_OPTIM_HPP

#include <functional>
#include <cstdint>
#include <njm_cpp/tools/random.hpp>

namespace njm {
namespace optim {

enum ErrorCode {SUCCESS, CONTINUE, ERROR, NON_FINITE_PARAMETER};

class Optim : public tools::RngClass {
protected:
    const std::function<double(const std::vector<double> & , void * const)> f_;

    std::vector<double> par_;

    const uint32_t par_size_;

    void * const data_;

    uint32_t completed_steps_;

    bool verbose_;


public:
    Optim(const std::function<double(const std::vector<double> & ,
                    void * const)> & f,
            const std::vector<double> & par,
            void * const data);

    Optim(const Optim & other) = delete;

    void verbose(const bool & verbose);

    std::vector<double> par() const;

    uint32_t completed_steps() const;


    virtual ErrorCode step() = 0;

    virtual void rng(const std::shared_ptr<tools::Rng> & rng) override;
};


} // namespace optim
} // namespace njm


#endif // NJM_CPP_OPTIM_HPP
