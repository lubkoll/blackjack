#include "BettingStrategy.h"

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
}
