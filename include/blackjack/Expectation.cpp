#include "Expectation.h"

namespace blackjack
{
    Expectation::Expectation( double win, double tie, double loss, double expectedPayout )
        : win( win ), tie( tie ), loss( loss ), payout( expectedPayout )
    {
    }

    Expectation& Expectation::axpy( double a, const Expectation& other )
    {
        win += a * other.win;
        tie += a * other.tie;
        loss += a * other.loss;
        payout += a * other.payout;
        return *this;
    }

    std::ostream& operator<<( std::ostream& os, const Expectation& probability )
    {
        return os << "win: " << probability.win << ", tie: " << probability.tie
                  << ", loss: " << probability.loss << ", payout: " << probability.payout;
    }
}
