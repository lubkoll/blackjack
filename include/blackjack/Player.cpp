#include "Player.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

namespace blackjack
{

#define X( a )                                                                                     \
    if ( Result::a == result )                                                                     \
        return os << #a;
    std::ostream& operator<<( std::ostream& os, Result result )
    {
        RESULTS
        return os;
    }
#undef X

    Decider::Decider( Strategy strategy, BettingStrategy bettingStrategy )
        : strategy( std::move( strategy ) ), bettingStrategy( std::move( bettingStrategy ) )
    {
    }

    Decision Decider::operator()( const std::vector< Hand >& hands, const Hand& hand,
                                  bool allowSplitting )
    {
        assert( strategy );
        return strategy( hands, hand, allowSplitting );
    }

    double Decider::getCash() const
    {
        return cash;
    }

    double Decider::getMinCash() const
    {
        return minCash;
    }

    void Decider::addCash( double payout )
    {
        //            std::cout << "+" << payout;
        cash += payout;
        minCash = std::min( cash, minCash );
        //            std::cout << " -> " << cash << std::endl;
    }

    void Decider::removeCash( double payout )
    {
        //            std::cout << "-" << payout;
        cash -= payout;
        minCash = std::min( cash, minCash );
        //            std::cout << " -> " << cash << std::endl;
    }

    double Decider::chooseBet( Deck& deck )
    {
        return bettingStrategy( deck );
    }

    Player getDealer()
    {
        return Player{Decider{blackjack::defaultDealerStrategy}, {Hand{}}, {0}};
    }

    Player getPlayer( Strategy strategy, BettingStrategy bettingStrategy )
    {
        return Player{Decider{strategy, bettingStrategy}, {Hand{}}, {1}};
    }
}
