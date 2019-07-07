#pragma once

#include <blackjack/Card.h>
#include <blackjack/Expectation.h>

#include <future>
#include <ostream>

namespace blackjack
{
    class Player;
    class Deck;
    struct Rules;

    Expectation computeExpectationAfterPlayer( Player& player, Player& dealer, Deck& deck,
                                               bool firstCall = true );

    Expectation computeExpectationAfterStartingHand( Player& player, Player& dealer, Deck& deck,
                                                     const Rules& rules );

    std::future< Expectation > computeExpectationAfterStartingHandAsync( Player& player,
                                                                         Player& dealer, Deck& deck,
                                                                         const Rules& rules );

    Expectation computeExpectationAfterOpenCards( Player& player, Player& dealer, Deck& deck,
                                                  const Rules& rules );

    void allProbabilites( Player& player, Player& dealer, Deck& deck, const Rules& rules,
                          std::ostream& os );

    Expectation computeExpectationForFirstRound( Player& player, Player& dealer, Deck& deck,
                                                 const Rules& rules );
}
