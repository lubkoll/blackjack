#pragma once

#include <blackjack/Card.h>

#include <functional>
#include <ostream>

namespace blackjack
{
    class Player;

    struct Record
    {
        Record& operator+=( const Record& other );

        int wins{0};
        int ties{0};
        int losses{0};
    };

    struct Rules
    {
        std::function< bool( const Hand& ) > isSplittingAllowed = []( const Hand& ) {
            return true;
        };
        std::function< bool( const Hand& ) > isDoubleDownAllowed = []( const Hand& ) {
            return true;
        };
        std::function< bool( const Hand& ) > isInsuranceAllowed = []( const Hand& ) {
            return false;
        };
    };

    struct DiscardCardsAtEndOfGame
    {
        ~DiscardCardsAtEndOfGame();

        Player& player;
        Deck& deck;
    };

    std::ostream& operator<<( std::ostream& os, const Record& record );

    Record playDealerAfterStartingHand( Deck& deck, Player& player, Player& dealer );

    Record playAfterStartingHand( Deck& deck, Player& player, Player& dealer,
                                  bool allowSplitting = true, bool splitAces = false );

    Record playAgainstDealer( Player& player, Player& dealer, Deck& deck );

    Record playAgainstDealer( Player& player, Player& dealer, Deck& deck, int numberOfGames );
}
