#include <Card.h>
#include <ComputeProbability.h>
#include <Game.h>
#include <Player.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

using blackjack::Card;
using blackjack::ConstantBetSize;
using blackjack::Deck;
using blackjack::Hand;
using blackjack::BasicStrategy;
using blackjack::create52CardDeck;
using blackjack::Player;
using blackjack::getDealer;
using blackjack::getPlayer;
using blackjack::Rules;
using blackjack::Probability;
using blackjack::computeProbabilityAfterPlayer;
using blackjack::computeProbabilityAfterStartingHand;
using blackjack::computeProbabilityAfterOpenCards;

using testing::DoubleEq;
using testing::DoubleNear;
using testing::Eq;

namespace
{
    Probability probabilityForFourSixAgainstNineSeven()
    {
        Probability probability;
        probability.axpy( 4.0 / 48, Probability{29.0 / 47, 0, 18.0 / 47, 11.0 / 47} );        // 2
        probability.axpy( 4.0 / 48, Probability{29.0 / 47, 0, 18.0 / 47, 11.0 / 47} );        // 3
        probability.axpy( 3.0 / 48, Probability{29.0 / 47, 0, 18.0 / 47, 11.0 / 47} );        // 4
        probability.axpy( 4.0 / 48, Probability{29.0 / 47, 0, 18.0 / 47, 11.0 / 47} );        // 5
        probability.axpy( 3.0 / 48, Probability{28.0 / 47, 0, 19.0 / 47, 9.0 / 47} );         // 6
        probability.axpy( 3.0 / 48, Probability{28.0 / 47, 4.0 / 47, 15.0 / 47, 13.0 / 47} ); // 7
        probability.axpy( 4.0 / 48, Probability{32.0 / 47, 4.0 / 47, 11.0 / 47, 21.0 / 47} ); // 8
        probability.axpy( 3.0 / 48, Probability{36.0 / 47, 4.0 / 47, 7.0 / 47, 29.0 / 47} );  // 9
        probability.axpy( 16.0 / 48, Probability{40.0 / 47, 3.0 / 47, 4.0 / 47, 36.0 / 47} ); // 10
        probability.axpy( 4.0 / 48, Probability{43.0 / 47, 4.0 / 47, 0.0, 43.0 / 47} );       // A
        probability.expectedPayout *= 2; // double down
        std::cout << probability << std::endl;
        return probability;
    }

    std::map< std::pair< Hand, Hand >, Probability > expectedProbability{
        {{{Card::_4, Card::_6}, {Card::_9, Card::_A}},
         Probability{3.0 / 48, 16.0 / 48, 29.0 / 48, -26.0 / 24}},
        {{{Card::_4, Card::_6}, {Card::_9, Card::_10}},
         Probability{19.0 / 48, 3.0 / 48, 26.0 / 48, -7.0 / 24}},
        {{{Card::_4, Card::_6}, {Card::_9, Card::_9}},
         Probability{22.0 / 48, 4.0 / 48, 22.0 / 48, 0.0}},
        {{{Card::_4, Card::_6}, {Card::_9, Card::_8}},
         Probability{26.0 / 48, 4.0 / 48, 18.0 / 48, 8.0 / 24}},
        {{{Card::_4, Card::_6}, {Card::_9, Card::_7}}, probabilityForFourSixAgainstNineSeven()},
    };

    struct TestProbabilities : testing::Test
    {
        void SetUp() override
        {
            const auto notAllowed = []( const Hand& ) { return false; };
            rules.isDoubleDownAllowed = notAllowed;
            rules.isSplittingAllowed = notAllowed;
            rules.isInsuranceAllowed = notAllowed;
        }

        void drawCard( Player& player, Card card )
        {
            deck.draw( card );
            player.hands.front().push_back( card );
        }

        Deck deck = create52CardDeck();
        Player dealer = getDealer();
        const double betSize = 1;
        Player player =
            getPlayer( BasicStrategy( dealer.hands.front() ), ConstantBetSize{betSize} );
        Rules rules;
    };

    using TestDealerProbabilities = TestProbabilities;
}

TEST_F( TestDealerProbabilities, PlayerHasSixAndTen_DealerHasSixAndTen_BustProbability )
{
    drawCard( player, Card::_6 );
    drawCard( player, Card::_10 );
    drawCard( dealer, Card::_6 );
    drawCard( dealer, Card::_10 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    EXPECT_THAT( probability.win, DoubleEq( 7.0 / 12 ) );
    EXPECT_THAT( probability.tie, DoubleEq( 0 ) );
    EXPECT_THAT( probability.loss, DoubleEq( 5.0 / 12 ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( 2.0 / 12 * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasSixAndTen_DealerHasFiveAndTen_BustProbability )
{
    drawCard( player, Card::_6 );
    drawCard( player, Card::_10 );
    drawCard( dealer, Card::_5 );
    drawCard( dealer, Card::_10 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    EXPECT_THAT( probability.win, DoubleEq( 13.0 / 24 + 29.0 / ( 12 * 47 ) ) );
    EXPECT_THAT( probability.tie, DoubleEq( 0 ) );
    EXPECT_THAT( probability.loss, DoubleEq( 3.0 / 8 + 3.0 / ( 2 * 47 ) ) );
    EXPECT_THAT( probability.expectedPayout,
                 DoubleEq( ( 1.0 / 6 + 11.0 / ( 12 * 47 ) ) * betSize ) );
}

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndAce_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_A );

    const auto betSize = player.bets.front();
    const auto probability = computeProbabilityAfterStartingHand( player, dealer, deck, rules );
    EXPECT_THAT( player.bets.front(), Eq( 2 * betSize ) );
    const auto expectation =
        expectedProbability[ std::make_pair( player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestProbabilities, PlayerHasFourAndTen_DealerHasNineAndTen_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_10 );

    const auto betSize = player.bets.front();
    const auto probability = computeProbabilityAfterStartingHand( player, dealer, deck, rules );
    EXPECT_THAT( player.bets.front(), Eq( 2 * betSize ) );
    const auto expectation =
        expectedProbability[ std::make_pair( player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestProbabilities, PlayerHasFourAndTen_DealerHasNineAndNine_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_9 );

    const auto betSize = player.bets.front();
    const auto probability = computeProbabilityAfterStartingHand( player, dealer, deck, rules );
    EXPECT_THAT( player.bets.front(), Eq( 2 * betSize ) );
    const auto expectation =
        expectedProbability[ std::make_pair( player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout,
                 DoubleNear( expectation.expectedPayout * betSize,
                             std::numeric_limits< double >::epsilon() ) );
}

TEST_F( TestProbabilities, PlayerHasFourAndTen_DealerHasNineAndEight_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_8 );

    const auto betSize = player.bets.front();
    const auto probability = computeProbabilityAfterStartingHand( player, dealer, deck, rules );
    EXPECT_THAT( player.bets.front(), Eq( 2 * betSize ) );
    const auto expectation =
        expectedProbability[ std::make_pair( player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestProbabilities, PlayerHasFourAndTen_DealerHasNineAndSeven_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_7 );

    const auto betSize = player.bets.front();
    const auto probability = computeProbabilityAfterStartingHand( player, dealer, deck, rules );
    EXPECT_THAT( player.bets.front(), Eq( 2 * betSize ) );
    const auto expectation =
        expectedProbability[ std::make_pair( player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

// TEST_F(TestProbabilities, PlayerHasTenAndDealerNineAndUnknown_DoubleDown)
//{
//    drawCard(player, Card::_4);
//    drawCard(player, Card::_6);
//    drawCard(dealer, Card::_9);

//    const auto betSize = player.bets.front();
//    const auto probability = computeProbabilityAfterOpenCards(player, dealer, deck, rules);
//    EXPECT_THAT(probability.win, DoubleEq(3.0/48));
//    EXPECT_THAT(probability.tie, Eq(16.0/48));
//    EXPECT_THAT(probability.loss, Eq(29.0/48));
//    EXPECT_THAT(probability.expectedPayout, Eq(-26.0/24*betSize));
//}
