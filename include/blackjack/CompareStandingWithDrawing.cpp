#include "CompareStandingWithDrawing.h"

#include <blackjack/ComputeProbability.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

#include <iostream>

namespace blackjack
{
    StandingVsDrawing compareStandingWithDrawing( const Hand& playerHand, Card openDealerCard )
    {
        Rules rules;
        auto deck = create52CardDecks();
        for ( auto card : playerHand )
            deck.draw( card );
        deck.draw( openDealerCard );

        auto dealer = getDealer();
        dealer.hands.front().push_back( openDealerCard );
        const auto drawingStrategy = [value = getMaxValidValue( playerHand )](
            const std::vector< Hand >&, const Hand& hand, bool, bool, bool )
        {
            return getMaxValidValue( hand ) == value ? Decision::Draw : Decision::Stand;
        };

        StandingVsDrawing result;

        auto player = getPlayer( drawingStrategy, ConstantBetSize{} );
        player.hands.front() = playerHand;
        result.drawing = computeExpectationAfterOpenCards( player, dealer, deck, rules );

        player = getPlayer( alwaysStandStrategy, ConstantBetSize{} );
        player.hands.front() = playerHand;
        result.standing = computeExpectationAfterOpenCards( player, dealer, deck, rules );

        std::cout << "final dealer hand: " << dealer.hands.front() << std::endl;

        return result;
    }
}
