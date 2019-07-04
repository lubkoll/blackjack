#pragma once

#include <Card.h>

#include <functional>

namespace blackjack
{
    using BettingStrategy = std::function< double( const Deck& ) >;

    class ConstantBetSize
    {
    public:
        explicit ConstantBetSize( double betSize = 1 ) noexcept;

        double operator()( const Deck& ) const noexcept;

    private:
        double betSize;
    };

    struct TenCountBettingStrategy
    {
    public:
        /**
         * @param a betSize for 10-ratio >= 2
         * @param b betSize for 10-ratio < 2
         * @param c betSize for 10-ratio < 1.75
         * @param d betSize for 10-ratio < 1.65
         * @param e betSize for 10-ratio < 1.5
         */
        TenCountBettingStrategy( double a = 1, double b = 1, double c = 3, double d = 5,
                                 double e = 7 ) noexcept;

        double operator()( const Deck& deck ) const noexcept;

    private:
        double a, b, c, d, e;
    };
}
