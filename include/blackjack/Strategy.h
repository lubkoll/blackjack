#pragma once

#include <blackjack/Card.h>

#include <limits>
#include <vector>
#include <functional>
#include <ostream>

#define DECISIONS                                                                                  \
    X( Draw )                                                                                      \
    X( Stand )                                                                                     \
    X( Split )                                                                                     \
    X( DoubleDown )

namespace blackjack
{
#define X( a ) a,
    enum class Decision
    {
        DECISIONS
    };
#undef X

    using Strategy = std::function< Decision( const std::vector< Hand >&, const Hand&, bool ) >;

    std::ostream& operator<<( std::ostream& os, Decision decision );

    Decision defaultDealerStrategy( const std::vector< Hand >&, const Hand& hand, bool );

    namespace basic
    {
        bool do_split( const Hand& hand, int openDealerValue );
        bool do_double_down( const Hand& hand, int openDealerValue );
        bool do_stand( const Hand& hand, int openDealerValue );
    }

    struct BasicStrategy
    {
        explicit BasicStrategy( Hand& dealerHand );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand,
                             bool splitAllowed );

        Hand& dealerHand;
    };

    namespace ten_count
    {
        bool do_split( const Hand& hand, int openDealerValue, double tenRatio,
                       bool doubleDownOnEightAllowed = true );

        bool do_double_down( const Hand& hand, int openDealerValue, double tenRatio );

        int findStandingNumber( const std::vector< std::vector< double > >& standingNumbers,
                                int openDealerValue, double tenRatio );

        bool do_stand( const Hand& hand, int openDealerValue, double tenRatio );
    }

    struct TenCountStrategy
    {
        TenCountStrategy( Deck& deck, Hand& dealerHand );

        ~TenCountStrategy();

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand,
                             bool splitAllowed ) const;

        double computeTenCount( const std::vector< Hand >& hands ) const;

        Deck& deck;
        Hand& dealerHand;
        mutable double minRatio = std::numeric_limits< double >::max();
    };
}
