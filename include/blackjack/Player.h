#pragma once

#include <blackjack/BettingStrategy.h>
#include <blackjack/Card.h>
#include <blackjack/Strategy.h>

#include <vector>
#include <functional>

#define RESULTS                                                                                    \
    X( Win )                                                                                       \
    X( Tie )                                                                                       \
    X( Loss )

namespace blackjack
{
#define X( a ) a,
    enum class Result
    {
        RESULTS
    };
#undef X

    std::ostream& operator<<( std::ostream& os, Result result );

    class Decider
    {
    public:
        explicit Decider( Strategy strategy,
                          BettingStrategy bettingStrategy = []( const Deck& ) { return 1; } );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand,
                             bool allowSplitting = true );

        double getCash() const;

        double getMinCash() const;

        void addCash( double payout );

        void removeCash( double payout );

        double chooseBet( Deck& deck );

    private:
        Strategy strategy;
        BettingStrategy bettingStrategy;
        double cash{1000};
        double minCash{cash};
    };

    struct Player
    {
        Decider decider;
        std::vector< Hand > hands;
        std::vector< double > bets;
    };

    Player getDealer();

    Player getPlayer( Strategy strategy, BettingStrategy bettingStrategy );
}
