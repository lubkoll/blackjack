#include "BettingStrategy.h"

#include <cmath>
#include <iostream>

namespace blackjack
{
    ConstantBetSize::ConstantBetSize( double betSize ) noexcept : betSize( betSize )
    {
    }

    double ConstantBetSize::operator()( const Deck& ) const noexcept
    {
        return betSize;
    }

    TenCountBettingStrategy::TenCountBettingStrategy( double a, double b, double c, double d,
                                                      double e ) noexcept
        : a( a ), b( b ), c( c ), d( d ), e( e )
    {
    }

    double TenCountBettingStrategy::operator()( const Deck& deck ) const noexcept
    {
        if ( deck.getCount( 10 ) == 0 )
            return a;
        //            std::cout << "tens: " << deck.getCount(10) << std::endl;
        //            std::cout << "not tens: " << deck.getCountExcept(10) << std::endl;
        const auto tenRatio = double( deck.getCountExcept( 10 ) ) / deck.getCount( 10 );
        //            std::cout << "ratio: " << tenRatio << std::endl;
        if ( tenRatio < 1.5 )
            return e;
        if ( tenRatio < 1.65 )
            return d;
        if ( tenRatio < 1.75 )
            return c;
        if ( tenRatio < 2.0 )
            return b;
        return a;
    }

    PointCountBettingStrategy::PointCountBettingStrategy( double minBet ) noexcept
        : minBet( minBet )
    {
    }

    double PointCountBettingStrategy::operator()( const Deck& deck ) const noexcept
    {
        const auto points = deck.getUsedCount( Card::_2 ) + deck.getUsedCount( Card::_3 ) +
                            deck.getUsedCount( Card::_4 ) + deck.getUsedCount( Card::_5 ) +
                            deck.getUsedCount( Card::_6 ) + deck.getUsedCount( Card::_7 ) -
                            deck.getUsedCount( Card::_9 ) - deck.getUsedCount( Card::_10 ) -
                            deck.getUsedCount( Card::_J ) - deck.getUsedCount( Card::_Q ) -
                            deck.getUsedCount( Card::_K ) - deck.getUsedCount( Card::_A );
        const auto pointRatio = 100 * points / deck.size();
        return std::min( std::max( std::floor( pointRatio / 2 ), 1.0 ), 5.0 ) * minBet;
    }
}
