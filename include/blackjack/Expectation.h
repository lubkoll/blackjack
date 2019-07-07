#pragma once

#include <ostream>

namespace blackjack
{
    struct Expectation
    {
        explicit Expectation( double win = 0, double tie = 0, double loss = 0, double payout = 0 );

        double win;
        double tie;
        double loss;
        double payout;

        Expectation& axpy( double a, const Expectation& other );
    };

    std::ostream& operator<<( std::ostream& os, const Expectation& probability );
}
