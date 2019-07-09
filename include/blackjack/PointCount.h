#pragma once

#include <blackjack/Card.h>
#include <blackjack/Decision.h>

namespace blackjack
{
    namespace point_count
    {
        bool do_split( const Hand& hand, int openDealerValue, double pointRatio,
                       bool doubleDownOnEightAllowed = true );

        bool do_double_down( const Hand& hand, int openDealerValue, double pointRatio );

        bool do_stand( const Hand& hand, int openDealerValue, double pointRatio );
    }

    struct PointCountStrategy
    {
        PointCountStrategy( Deck& deck, Hand& dealerHand );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand, bool splitAllowed,
                             bool doubleDownAllowed, bool insuranceAllowed ) const;

        double computePointCountRatio( const std::vector< Hand >& hands ) const;

        Deck& deck;
        Hand& dealerHand;
        mutable double minRatio = std::numeric_limits< double >::max();
    };

    namespace simplified_point_count
    {
        bool do_split( const Hand& hand, int openDealerValue, double pointRatio,
                       bool doubleDownOnEightAllowed = true );

        bool do_double_down( const Hand& hand, int openDealerValue, double pointRatio );

        bool do_stand( const Hand& hand, int openDealerValue, double pointRatio );
    }

    struct SimplifiedPointCountStrategy
    {
        SimplifiedPointCountStrategy( Deck& deck, Hand& dealerHand );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand, bool splitAllowed,
                             bool doubleDownAllowed, bool insuranceAllowed ) const;

        double computePointCountRatio( const std::vector< Hand >& hands ) const;

        Deck& deck;
        Hand& dealerHand;
        mutable double minRatio = std::numeric_limits< double >::max();
    };

    struct PointCountBettingStrategy
    {
    public:
        explicit PointCountBettingStrategy( double minBet ) noexcept;

        double operator()( const Deck& deck ) const noexcept;

    private:
        double minBet;
    };

    int getPoints( Card card );

    int computePoints( const Hand& hand );

    int computePointsInPlay( const std::vector< Hand >& hands, Card openDealerCard );

    double computePointRatio( int pointsInPlay, const Deck& deck );
}
