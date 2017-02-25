#include <njm_cpp/thread/pool.hpp>

#include <thread>

namespace njm {
namespace thread {


Pool::Pool()
    : Pool(std::max(std::thread::hardware_concurrency(), 1u)) {
}

Pool::Pool(const uint32_t & num_threads)
    : num_threads_(num_threads), service_(), work_(this->service_),
      workers_(), joined_(false) {

    for (uint32_t i = 0; i < num_threads_; ++i) {
        this->workers_.create_thread(
                boost::bind(&boost::asio::io_service::run, &this->service_));
    }
}


Pool::Pool(const Pool & other)
    : Pool(other.num_threads_) {
}


Pool::~Pool() {
    if (!this->joined_) {
        this->join();
    }
}


boost::asio::io_service & Pool::service() {
    return this->service_;
}


void Pool::join() {
    this->joined_ = true;
    this->work_.reset();
    this->workers_.join_all();
}


} // namespace thread
} // namespace njm
