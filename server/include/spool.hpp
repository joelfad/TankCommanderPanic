/*
Project:  Tank Commander Panic
File:  spool.hpp
Author:  Leonardo Banderali
Description:  A generic spool for thread messageing with synchronization.
*/

#ifndef SPOOL_HPP
#define SPOOL_HPP



// c++ standard libraries
#include <deque>
#include <mutex>
#include <utility>

// boost libraries
#include <boost/optional.hpp>



//~template declaration~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
class spool {
    public:
        using item_type = T;
        using maybe_item = boost::optional<item_type>;

        template <typename G>
        auto add(G&& msg) -> void;
        /*  adds an item to the spool */

        auto get() -> maybe_item;
        /*  if available, returns the first item on the spool, otherwise returns empty item */

        auto pop() -> void;
        /*  pops the first item on the spool */

    private:
        std::deque<item_type> queue;    // queue to spool messages
        std::mutex mutex;               // synchronization lock
};



//~template definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
adds an item to the spool
*/
template <typename T>
template <typename G>
auto spool<T>::add(G&& msg) -> void{
    mutex.lock();
    queue.push_back(std::forward<T>(msg));
    mutex.unlock();
}

/*
returns the first item on the spool
*/
template <typename T>
auto spool<T>::get() -> maybe_item {
    mutex.lock();
    auto item = maybe_item{};
    if (!queue.empty())
        item = maybe_item{queue.front()};
    mutex.unlock();
    return item;
}

/*
pops the first item on the spool
*/
template <typename T>
auto spool<T>::pop() -> void {
    mutex.lock();
    queue.pop_front();
    mutex.unlock();
}

#endif // SPOOL_HPP
