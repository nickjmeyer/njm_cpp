#include <njm_cpp/tools/random.hpp>
#include <glog/logging.h>
#include <algorithm>
#include <iostream>

namespace njm {
namespace tools {



Rng::Rng()
    : gen_(0), seed_(0), dis_runif_01_(0., 1.),
      has_next_rnorm_(false), next_rnorm_01_(0.0),
      runif_count_(0), rnorm_count_(0) {
}

void Rng::seed(const uint32_t seed) {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    this->seed_ = seed;
    this->gen_.seed(seed);
    this->dis_runif_01_.reset();
    this->has_next_rnorm_ = false;
}


uint32_t Rng::seed() const {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    return this->seed_;
}

const std::mt19937 & Rng::gen() const {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    return this->gen_;
}

void Rng::gen(const std::mt19937 & gen) {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    this->gen_ = gen;
}

double Rng::runif_01() {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    ++this->runif_count_;
    const double draw(this->dis_runif_01_(this->gen_));
    return draw;
}


double Rng::rnorm_01() {
    std::lock_guard<std::mutex> lock(this->gen_mutex_);
    ++this->rnorm_count_;
    if (this->has_next_rnorm_) {
        this->has_next_rnorm_ = false;
        return this->next_rnorm_01_;
    } else {
        const double u1(this->dis_runif_01_(this->gen_));
        const double u2(this->dis_runif_01_(this->gen_));
        const double a(std::sqrt(-2.0 * std::log(u1)));
        this->has_next_rnorm_ = true;
        this->next_rnorm_01_ = a * std::cos(6.28318530718 * u2);
        const double draw(a * std::sin(6.28318530718 * u2));
        return draw;
    }
}

double Rng::rnorm(const double mu, const double sigma) {
    return this->rnorm_01() * sigma + mu;
}

double Rng::runif(const double a, const double b) {
    CHECK_LT(a, b);
    return this->runif_01() * (b - a) + a;
}


int Rng::rint(const int a, const int b) {
    CHECK_LT(a, b);
    return static_cast<int>(this->runif_01() * (b - a)) + a;
}


std::vector<int> Rng::sample_range(const int a, const int b, const int n) {
    CHECK_LT(a, b) << "a = " << a << ", b = " << b;
    const uint32_t num_vals = b - a;
    CHECK_LT(n, num_vals); // can't sample more than what's there
    std::vector<int> choices;
    for (int i = a; i < b; ++i) {
        choices.push_back(i);
    }

    std::vector<int> values;
    for (uint32_t i = 0; i < n; ++i) {
        // sample an index
        const uint32_t ind = this->rint(0, num_vals - i);

        // record the value
        values.push_back(choices.at(ind));

        // swap values
        choices.at(ind) = choices.at(num_vals - i - 1);
    }

    return values;
}

void Rng::shuffle(std::vector<uint32_t> & x) {
    const uint32_t x_size(x.size());
    for (uint32_t i = 0; i < (x_size - 1); ++i) {
        const uint32_t draw_index(static_cast<uint32_t>(this->rint(i, x_size)));
        if (draw_index != i) {
            const double i_val(x.at(i));
            x.at(i) = x.at(draw_index);
            x.at(draw_index) = i_val;
        }
    }
}


RngClass::RngClass()
    : rng_(new Rng()) {
}

RngClass::RngClass(const RngClass & other)
    : RngClass() {
    this->seed(other.seed());
}

void RngClass::rng(const std::shared_ptr<Rng> & rng) {
    this->rng_ = rng;
}

const std::shared_ptr<Rng> & RngClass::rng() const {
    return this->rng_;
}

void RngClass::seed(const uint32_t seed) {
    this->rng_->seed(seed);
}

uint32_t RngClass::seed() const {
    return this->rng_->seed();
}


} // namespace tools
} // namespace njm
