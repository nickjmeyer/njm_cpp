#ifndef NJM_CPP_RANDOM_HPP
#define NJM_CPP_RANDOM_HPP

#include <memory>
#include <cstdint>
#include <mutex>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace njm {
namespace tools {


class Rng {
private:
    boost::mt19937 gen_;
    boost::variate_generator<boost::mt19937 &,
                             boost::random::uniform_real_distribution<double> >
    dis_runif_01_;
    boost::variate_generator<boost::mt19937 &,
                             boost::random::normal_distribution<double> >
    dis_rnorm_01_;
    uint32_t seed_;

    mutable std::mutex gen_mutex_;

public:
    Rng();

    // set the random seed
    void seed(const uint32_t seed);

    // get the random seed
    uint32_t seed() const;

    // get the generator
    boost::mt19937 & gen();

    // set the generator
    void gen(const boost::mt19937 & gen);

    // generate random uniform between [0,1)
    double runif_01();

    // generate random normal
    double rnorm_01();

    // generate random normal N(mu, sigma^2)
    double rnorm(const double mu, const double sigma);

    // generate random uniform between [a,b)
    double runif(const double a, const double b);

    // generate random uniform integer between [a,b)
    int rint(const int a, const int b);

    // random sample from range without replacement
    std::vector<int> sample_range(const int a, const int b, const int n);

    // shuffle
    void shuffle(std::vector<uint32_t> & x);
};


class RngClass {
protected:
    std::shared_ptr<Rng> rng_;

    RngClass();

    RngClass(const RngClass & other);

public:
    virtual void rng(const std::shared_ptr<Rng> & rng) = 0;

    const std::shared_ptr<Rng> & rng() const;

    void seed(uint32_t seed);

    uint32_t seed() const;
};



} // namespace tools
} // namespace njm


#endif // NJM_CPP_RANDOM_HPP
