#pragma once

#include <ostream>

namespace blackjack
{
    class Player;
    class Deck;
    struct Rules;

    struct Probability
    {
        explicit Probability( double win = 0, double tie = 0, double loss = 0,
                              double expectedPayout = 0 );

        double win;
        double tie;
        double loss;
        double expectedPayout;

        Probability& axpy( double a, const Probability& other );
    };

    std::ostream& operator<<( std::ostream& os, const Probability& probability );

    Probability computeProbabilityAfterPlayer( Player& player, Player& dealer, Deck& deck,
                                               bool firstCall = true );

    Probability computeProbabilityAfterStartingHand( Player& player, Player& dealer, Deck& deck,
                                                     const Rules& rules );

    Probability computeProbabilityAfterOpenCards( Player& player, Player& dealer, Deck& deck,
                                                  const Rules& rules );
}
