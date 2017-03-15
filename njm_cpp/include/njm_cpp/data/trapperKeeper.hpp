#ifndef NJM_CPP_TRAPPER_KEEPER_HPP
#define NJM_CPP_TRAPPER_KEEPER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <boost/filesystem.hpp>
#include <mutex>


namespace njm {
namespace data {



std::string time_stamp();


class TrapperKeeper;

class Entry {
protected:
    friend class TrapperKeeper;

    boost::filesystem::path path_;

    std::stringstream content_;

    mutable std::mutex mutex_;

    friend std::ostream & operator<<(std::ostream & os, const Entry & r);

    void wipe();

    std::string retrieve_and_wipe();

public:
    Entry(const boost::filesystem::path & path);
    Entry(const Entry & other) = delete;

    boost::filesystem::path path();

    template<class T>
    Entry& operator<<(const T & new_content) {
        std::lock_guard<std::mutex> lock(this->mutex_);
        this->content_ << new_content;
        return *this;
    }
};


class TrapperKeeper {
protected:
    std::list<Entry> entries_;
    const boost::filesystem::path root_;
    const boost::filesystem::path temp_;
    const boost::filesystem::path date_;

    bool wiped_;
    bool finished_;

    std::mutex mutex_;

    void flush_no_lock();

    void wipe_no_lock();

    void copy_contents(const boost::filesystem::path & source,
            const boost::filesystem::path & dest);

public:
    TrapperKeeper(const std::string & name,
            const boost::filesystem::path & root);
    TrapperKeeper(const TrapperKeeper & other) = delete;
    ~TrapperKeeper();

    void finished();

    const boost::filesystem::path & root() const;

    const boost::filesystem::path & temp() const;

    const boost::filesystem::path & date() const;

    void wipe();

    Entry * entry(const boost::filesystem::path & entry_path);

    void flush();
};




} // namespace data
} // namespace njm


#endif // NJM_CPP_TRAPPER_KEEPER_HPP
