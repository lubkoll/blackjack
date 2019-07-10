#include <blackjack/Card.h>
#include <blackjack/ComputeProbability.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::ConstantBetSize;
using blackjack::Decision;
using blackjack::Deck;
using blackjack::Hand;
using blackjack::BasicStrategy;
using blackjack::create52CardDecks;
using blackjack::Player;
using blackjack::getDealer;
using blackjack::getPlayer;
using blackjack::Rules;
using blackjack::Expectation;
using blackjack::computeExpectationForFirstRound;

using testing::DoubleEq;
using testing::DoubleNear;
using testing::Eq;

struct TestProbabilityForFirstRound_BasicStrategy : testing::Test
{
    void SetUp() override
    {
        rules.isDoubleDownAllowed = &Rules::isAlwaysAllowed;
        rules.isSplittingAllowed = &Rules::isNeverAllowed;
        rules.isInsuranceAllowed = &Rules::isNeverAllowed;
    }

    void drawCard( Player& player, Card card, Deck& deck )
    {
        deck.draw( card );
        player.hands.front().push_back( card );
    }

    Player dealer = getDealer();
    const double betSize = 1;
    Player player = getPlayer( BasicStrategy( dealer.hands.front() ), ConstantBetSize{betSize} );
    Rules rules;
};

TEST( TestProbabilitiesForFirstRound, IF_DeckHasOnlyCardTypeNine_THEN_AllGamesAreTied )
{
    Deck deck( false );
    deck.add( Card::_9, 8 );

    const auto strategy = []( const std::vector< Hand >&, const Hand&, bool, bool, bool ) {
        return Decision::Stand;
    };
    auto player = getPlayer( strategy, ConstantBetSize{} );
    auto dealer = getDealer();
    Rules rules;
    const auto p = computeExpectationForFirstRound( player, dealer, deck, rules );
    EXPECT_THAT( p.win, DoubleEq( 0 ) );
    EXPECT_THAT( p.tie, DoubleEq( 1 ) );
    EXPECT_THAT( p.loss, DoubleEq( 0 ) );
    EXPECT_THAT( p.payout, DoubleEq( 0 ) );
}

TEST_F( TestProbabilityForFirstRound_BasicStrategy, IF_DeckHasOnlyFives_THEN_AllGamesAreTied )
{
    Deck deck( false );
    deck.add( Card::_5, 8 );
    const auto p = computeExpectationForFirstRound( player, dealer, deck, rules );
    EXPECT_THAT( p.win, DoubleEq( 0 ) );
    EXPECT_THAT( p.tie, DoubleEq( 0 ) );
    EXPECT_THAT( p.loss, DoubleEq( 1 ) );
    EXPECT_THAT( p.payout, DoubleEq( -2 ) );
}
