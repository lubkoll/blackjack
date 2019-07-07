#pragma once

#include <deque>
#include <experimental/optional>
#include <mutex>

namespace blackjack
{
    template < class T >
    class Queue
    {
    public:
        void push( T t )
        {
            std::lock_guard guard( mutex );
            queue.push_back( t );
        }

        std::experimental::optional< T > pop()
        {
            std::lock_guard guard( mutex );
            if ( queue.empty() )
                return {};
            auto t = queue.front();
            queue.pop_front();
            return t;
        }

    private:
        std::mutex mutex;
        std::deque< T > queue;
    };
}
