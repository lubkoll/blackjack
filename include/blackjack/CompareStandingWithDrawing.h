#pragma once

#include <blackjack/Card.h>
#include <blackjack/Expectation.h>

namespace blackjack
{
    struct StandingVsDrawing
    {
        Expectation standing;
        Expectation drawing;
    };

    StandingVsDrawing compareStandingWithDrawing( const Hand& playerHand, Card openDealerCard );
}
