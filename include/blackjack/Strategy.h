#pragma once

#include <blackjack/Card.h>
#include <blackjack/Decision.h>

#include <limits>
#include <vector>
#include <functional>
#include <ostream>

namespace blackjack
{
    using Strategy =
        std::function< Decision( const std::vector< Hand >&, const Hand&, bool, bool, bool ) >;

    Decision defaultDealerStrategy( const std::vector< Hand >&, const Hand& hand, bool, bool,
                                    bool );

    Decision alwaysStandStrategy( const std::vector< Hand >&, const Hand&, bool, bool, bool );

    namespace basic
    {
        bool do_split( const Hand& hand, int openDealerValue );
        bool do_double_down( const Hand& hand, int openDealerValue );
        bool do_stand( const Hand& hand, int openDealerValue );
    }

    struct BasicStrategy
    {
        explicit BasicStrategy( Hand& dealerHand );

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand, bool splitAllowed,
                             bool doubleDownAllowed, bool insuranceAllowed );

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

        Decision operator()( const std::vector< Hand >& hands, const Hand& hand, bool splitAllowed,
                             bool doubleDownAllowed, bool insuranceAllowed ) const;

        double computeTenCount( const std::vector< Hand >& hands ) const;

        Deck& deck;
        Hand& dealerHand;
        mutable double minRatio = std::numeric_limits< double >::max();
    };
}
