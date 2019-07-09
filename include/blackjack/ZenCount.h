#pragma once

#include <blackjack/Card.h>
#include <blackjack/Decision.h>

namespace blackjack
{
    namespace zen_count
    {
        bool do_split( const Hand& hand, int openDealerValue, double pointRatio );

        bool do_double_down( const Hand& hand, int openDealerValue, double pointRatio );

        bool do_stand( const Hand& hand, int openDealerValue, double pointRatio );
    }

    struct ZenCountStrategy
    {
        ZenCountStrategy( Deck& deck, Hand& dealerHand );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand, bool splitAllowed,
                             bool doubleDownAllowed, bool insuranceAllowed ) const;

        double computeZenCountRatio( const std::vector< Hand >& hands ) const;

        Deck& deck;
        Hand& dealerHand;
        mutable double minRatio = std::numeric_limits< double >::max();
    };

    struct ZenCountBettingStrategy
    {
    public:
        explicit ZenCountBettingStrategy( double minBet ) noexcept;

        double operator()( const Deck& deck ) const noexcept;

    private:
        double minBet;
    };

    int getZenPoints( Card card );

    int computeZenPoints( const Hand& hand );

    int computeZenPointsInPlay( const std::vector< Hand >& hands, Card openDealerCard );

    double computeZenPointRatio( int pointsInPlay, const Deck& deck );
}
