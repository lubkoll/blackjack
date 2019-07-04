#include "Card.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

using blackjack::Decision;
using blackjack::Decider;
using blackjack::Deck;
using blackjack::Hand;
using blackjack::Result;
using blackjack::Player;

struct BustStats
{
    double bust{0};
    double nonbust{0};
};

struct Stats
{
    int wins{0};
    int ties{0};
    int losses{0};
    double payoff{0};
};

struct PlayerStrategy
{
    Decision operator()( const blackjack::Hand& )
    {
        if ( firstDecision )
        {
            firstDecision = false;
            return Decision::Draw;
        }
        return Decision::Stand;
    }

    bool firstDecision{true};
};

struct PlayerStrategy2
{
    Decision operator()( const blackjack::Hand& hand )
    {
        if ( firstDecision )
        {
            firstDecision = false;
            return Decision::Draw;
        }
        return Decision::Stand;
    }

    bool firstDecision{true};
};

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
        return 1;
    const int N = std::atoi( argv[ 1 ] );
    std::cout << "Games: " << N << std::endl;

    auto deck = blackjack::create52CardDeck();
    std::cout << deck << std::endl;
    std::cout << deck.size() << std::endl;
    auto dealer = blackjack::getDealer();
    Player player =
        blackjack::getPlayer( /*blackjack::BasicStrategy{dealer.hands.front().hand},*/
                              blackjack::TenCountStrategy{deck, dealer.hands.front()},
                              blackjack::TenCountBettingStrategy{1, 1, 12.5, 12.5, 12.5} );
    const auto record = blackjack::playAgainstDealer( player, dealer, deck, N );
    std::cout << record << std::endl;
    const auto payoff =
        double( record.wins - record.losses ) / ( record.wins + record.ties + record.losses );
    std::cout << "payoff: " << payoff << std::endl;
    std::cout << "final cash: " << player.decider.getCash() << std::endl;
    std::cout << "min cash: " << player.decider.getMinCash() << std::endl;

    return 0;
}
