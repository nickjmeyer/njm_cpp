#ifndef NJM_CPP_RESULT_HPP
#define NJM_CPP_RESULT_HPP

#include <glog/logging.h>

#include <algorithm>

namespace njm {
namespace data {




template<class T>
class Result {
protected:
    T value_;
    bool has_value_;

public:
    Result() : has_value_(false) {};

    void set(const T & value) { this->value_ = value; this->has_value_ = true;};

    const T & get() const {CHECK(this->has_value_); return this->value_;};

    bool has_value() const {return this->has_value_;};
};

template<class T>
std::vector<T> result_to_vec(const std::vector<Result<T> > & result) {
    std::vector<T> vec;
    std::for_each(result.begin(), result.end(),
            [&](const Result<T> & r){
                vec.push_back(r.get());
            });
    return vec;
}

template<class T>
std::vector<T> result_to_vec(
        const std::vector<std::shared_ptr<Result<T> > > & result) {
    std::vector<T> vec;
    std::for_each(result.begin(), result.end(),
            [&](const std::shared_ptr<Result<T> > & r){
                vec.push_back(r->get());
            });
    return vec;
}


} // namespace data
} // namespace njm


#endif // NJM_CPP_RESULT_HPP
