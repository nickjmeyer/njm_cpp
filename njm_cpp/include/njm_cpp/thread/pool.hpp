#ifndef NJM_CPP_POOL_HPP
#define NJM_CPP_POOL_HPP

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>

namespace njm {
namespace thread {


class Pool {
protected:
    const uint32_t & num_threads_;

    boost::asio::io_service service_;
    boost::optional<boost::asio::io_service::work> work_;

    boost::thread_group workers_;

    bool joined_;

public:
    Pool();

    Pool(const uint32_t & num_threads);

    Pool(const Pool & other);

    ~Pool();

    boost::asio::io_service & service();

    void join();
};


} // namespace thread
} // namespace njm


#endif // NJM_CPP_POOL_HPP
