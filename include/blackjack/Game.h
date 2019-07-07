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
        static bool isAlwaysAllowed( const Hand& )
        {
            return true;
        }

        static bool isNeverAllowed( const Hand& )
        {
            return false;
        }

        using Rule = bool ( * )( const Hand& );

        Rule isSplittingAllowed = &isAlwaysAllowed;
        Rule isDoubleDownAllowed = &isAlwaysAllowed;
        Rule isInsuranceAllowed = &isNeverAllowed;
        double factorForNaturals = 1.5;
    };

    struct DiscardCardsAtEndOfGame
    {
        ~DiscardCardsAtEndOfGame();

        Player& player;
        Deck& deck;
    };

    std::ostream& operator<<( std::ostream& os, const Record& record );

    Record playDealerAfterStartingHand( Deck& deck, Player& player, Player& dealer );

    Record playAfterStartingHand( Deck& deck, Player& player, Player& dealer, const Rules& rules,
                                  bool wasSplit = false, bool splitAces = false );

    Record playAgainstDealer( Player& player, Player& dealer, Deck& deck, const Rules& rules );

    Record playAgainstDealer( Player& player, Player& dealer, Deck& deck, const Rules& rules,
                              int numberOfGames );
}
