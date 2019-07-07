#include <blackjack/Card.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>
#include <blackjack/Strategy.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::ConstantBetSize;
using blackjack::create52CardDeck;
using blackjack::Decision;
using blackjack::Deck;
using blackjack::getDealer;
using blackjack::getPlayer;
using blackjack::TenCountStrategy;

using testing::Eq;

namespace
{
    Deck createDeckForScenario_1()
    {
        auto deck = create52CardDeck();
        deck.burn( Card::_4 );
        deck.burn( Card::_5 );
        deck.burn( Card::_9 );
        deck.burn( Card::_6 );
        deck.burn( Card::_7 );
        deck.burn( Card::_8 );
        deck.burn( Card::_A );
        deck.burn( Card::_K );
        deck.burn( Card::_8 );
        deck.burn( Card::_J );
        deck.burn( Card::_9 );
        deck.burn( Card::_K );
        return deck;
    }
}

TEST( TestTenCountScenarios, _1 )
{
    auto deck = createDeckForScenario_1();
    auto dealer = getDealer();
    auto player = getPlayer( TenCountStrategy{deck, dealer.hands.front()}, ConstantBetSize{} );
    player.hands.front().push_back( deck.draw( Card::_2 ) );
    player.hands.front().push_back( deck.draw( Card::_6 ) );
    dealer.hands.front().push_back( deck.draw( Card::_Q ) );
    dealer.hands.front().push_back( deck.draw( Card::_2 ) );

    auto decision = player.decider( player.hands, player.hands.front() );
    EXPECT_THAT( decision, Eq( Decision::Draw ) );
    player.hands.front().push_back( deck.draw( Card::_3 ) );

    decision = player.decider( player.hands, player.hands.front() );
    EXPECT_THAT( decision, Eq( Decision::DoubleDown ) );
}
