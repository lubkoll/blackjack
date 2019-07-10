#include <blackjack/Card.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>
#include <blackjack/PointCount.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::ConstantBetSize;
using blackjack::create52CardDecks;
using blackjack::Decision;
using blackjack::Deck;
using blackjack::getDealer;
using blackjack::getPlayer;
using blackjack::PointCountStrategy;

using testing::Eq;

namespace
{
    Deck createDeckForScenario_1()
    {
        auto deck = create52CardDecks();
        deck.burn( Card::_7 );
        deck.burn( Card::_3 );
        deck.burn( Card::_6 );
        deck.burn( Card::_8 );
        deck.burn( Card::_2 );
        deck.burn( Card::_10 );
        return deck;
    }
}

TEST( TestPointCountScenarios, _1 )
{
    auto deck = createDeckForScenario_1();
    auto dealer = getDealer();
    auto player = getPlayer( PointCountStrategy{deck, dealer.hands.front()}, ConstantBetSize{} );
    player.hands.front().push_back( deck.draw( Card::_10 ) );
    player.hands.front().push_back( deck.draw( Card::_3 ) );
    dealer.hands.front().push_back( deck.draw( Card::_4 ) );
    dealer.hands.front().push_back( deck.draw( Card::_2 ) );

    auto decision = player.decider( player.hands, player.hands.front() );
    EXPECT_THAT( decision, Eq( Decision::Stand ) );
}
