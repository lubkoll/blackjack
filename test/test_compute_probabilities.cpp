#include <blackjack/Card.h>
#include <blackjack/ComputeProbability.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

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

    Probability probabilityForFourSixAgainstNineSix()
    {
        // clang-format off
        Probability probability;
        probability.axpy(  4.0 / 48, Probability{27.0/47 + 4*29.0/(47*46),
                                                 0,
                                                 16.0/47 + 4*17.0/(47*46),
                                                 11.0/47 + 4*12.0/(47*46)} ); // 2
        probability.axpy(  4.0 / 48, Probability{27.0/47 + 4*29.0/(47*46),
                                                 0,
                                                 16.0/47 + 4*17.0/(47*46),
                                                 11.0/47 + 4*12.0/(47*46)} ); // 3
        probability.axpy(  3.0 / 48, Probability{27.0/47 + 4*29.0/(47*46),
                                                 0,
                                                 16.0/47 + 4*17.0/(47*46),
                                                 11.0/47 + 4*12.0/(47*46)} ); // 4
        probability.axpy(  4.0 / 48, Probability{27.0/47 + 4*29.0/(47*46),
                                                 0,
                                                 16.0/47 + 4*17.0/(47*46),
                                                 11.0/47 + 4*12.0/(47*46)} ); // 5
        probability.axpy(  2.0 / 48, Probability{27.0/47 + 4*28.0/(47*46),
                                                 0,
                                                 16.0/47 + 4*18.0/(47*46),
                                                 11.0/47 + 4*10.0/(47*46)} ); // 6
        probability.axpy(  4.0 / 48, Probability{26.0/47 + 4*28.0/(47*46),
                                                 4.0*49.0/(47*46),
                                                 13.0/47 + 4*15.0/(47*46),
                                                 13.0/47 + 4*13.0/(47*46)} ); // 7
        probability.axpy(  4.0 / 48, Probability{30.0/47 + 4*31.0/(47*46),
                                                 4.0*50.0/(47*46),
                                                  9.0/47 + 4*11.0/(47*46),
                                                 21.0/47 + 4*20.0/(47*46)} ); // 8
        probability.axpy(  3.0 / 48, Probability{34.0/47 + 4*35.0/(47*46),
                                                 (3.0*46 + 16.0)/(47*46),
                                                  6.0/47 +  4*7.0/(47*46),
                                                 28.0/47 + 4*28.0/(47*46)} ); // 9
        probability.axpy( 16.0 / 48, Probability{37.0/47 + 4*39.0/(47*46),
                                                 4.0*49.0/(47*46),
                                                  2.0/47 +   4*4.0/(47*46),
                                                 35.0/47 + 4*35.0/(47*46)} ); // 10
        probability.axpy(  4.0 / 48, Probability{42.0/47 + 3*42.0/(47*46),
                                                 2.0*52.0/(47*46),
                                                 0.0,
                                                 42.0/47 + 3*42.0/(47*46)} ); // A
        probability.expectedPayout *= 2; // double down
        // clang-format on
        std::cout << probability << std::endl;
        return probability;
    }

    // clang-format off
    std::map< std::pair< Hand, Hand >, Probability > expectedProbability{
        { {{Card::_4, Card::_6}, {Card::_9, Card::_A}},  Probability{ 3.0 / 48, 16.0 / 48, 29.0 / 48, -26.0 / 24} },
        { {{Card::_4, Card::_6}, {Card::_9, Card::_10}}, Probability{19.0 / 48,  3.0 / 48, 26.0 / 48, -7.0 / 24} },
        { {{Card::_4, Card::_6}, {Card::_9, Card::_9}},  Probability{22.0 / 48,  4.0 / 48, 22.0 / 48,  0.0} },
        { {{Card::_4, Card::_6}, {Card::_9, Card::_8}},  Probability{26.0 / 48,  4.0 / 48, 18.0 / 48,  8.0 / 24} },
        { {{Card::_4, Card::_6}, {Card::_9, Card::_7}},  probabilityForFourSixAgainstNineSeven() },
        { {{Card::_4, Card::_6}, {Card::_9, Card::_6}},  probabilityForFourSixAgainstNineSix() },
    };

    std::map< std::pair< Hand, Hand >, Probability > expectedProbabilityAfterPlayer{
        { {{Card::_6, Card::_10},          {Card::_6, Card::_10}}, Probability{7.0 / 12, 0, 5.0 / 12, 2.0 / 12} },
        { {{Card::_4, Card::_6, Card::_2}, {Card::_9, Card::_6}},  Probability{( 27.0*46 + 4*29 ) / (47*46),
                                                                               0,
                                                                               ( 16.0*46 + 4*17 ) / (47*46),
                                                                               (11.0*46 + 4*12) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_3}, {Card::_9, Card::_6}},  Probability{( 27.0*46 + 4*29 ) / (47*46),
                                                                               0,
                                                                               ( 16.0*46 + 4*17 ) / (47*46),
                                                                               (11.0*46 + 4*12) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_4}, {Card::_9, Card::_6}},  Probability{( 27.0*46 + 4*29 ) / (47*46),
                                                                               0,
                                                                               ( 16.0*46 + 4*17 ) / (47*46),
                                                                               (11.0*46 + 4*12) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_5}, {Card::_9, Card::_6}},  Probability{( 27.0*46 + 4*29 ) / (47*46),
                                                                               0,
                                                                               ( 16.0*46 + 4*17 ) / (47*46),
                                                                               (11.0*46 + 4*12) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_6}, {Card::_9, Card::_6}},  Probability{( 27.0*46 + 4*28 ) / (47*46),
                                                                               0,
                                                                               ( 16.0*46 + 4*18 ) / (47*46),
                                                                               (11.0*46 + 4*10) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_7}, {Card::_9, Card::_6}},  Probability{( 26.0*46 + 4*28 ) / (47*46),
                                                                               4*49.0/(47*46),
                                                                               ( 13.0*46 + 4*15 ) / (47*46),
                                                                               (13.0*46 + 4*13) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_8}, {Card::_9, Card::_6}},  Probability{( 30.0*46 + 4*31 ) / (47*46),
                                                                               4*50.0/(47*46),
                                                                               ( 9.0*46 + 4*11 ) / (47*46),
                                                                               (21.0*46 + 4*20) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_9}, {Card::_9, Card::_6}},  Probability{( 34.0*46 + 4*35 ) / (47*46),
                                                                               (3*46.0+16)/(47*46),
                                                                               ( 6.0*46 + 4*7 ) / (47*46),
                                                                               (28.0*46 + 4*28) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_10}, {Card::_9, Card::_6}},  Probability{( 37.0*46 + 4*39 ) / (47*46),
                                                                               4*49.0/(47*46),
                                                                               ( 2.0*46 + 4*4 ) / (47*46),
                                                                               (35.0*46 + 4*35) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_A}, {Card::_9, Card::_6}},  Probability{( 42.0*46 + 3*42 ) / (47*46),
                                                                               (2*46+12.0)/(47*46),
                                                                               0,
                                                                               ( 42.0*46 + 3*42 ) / (47*46)} },
        { {{Card::_4, Card::_6, Card::_2}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*27 + 3*30)*45 + 4*3*30 ) / (47*46*45),
                        0,
                        ( 17.0*46*45 + (4*16 + 3*16)*45 + 4*3*15 ) / (47*46*45),
                        ( 6.0*46*45 + (4*11 + 3*14)*45 + 4*3*15 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_3}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*27 + 4*30)*45 + 4*3*30 ) / (47*46*45),
                        0,
                        ( 16.0*46*45 + (4*16 + 4*16)*45 + 4*3*15 ) / (47*46*45),
                        ( 7.0*46*45 + (4*11 + 4*14)*45 + 4*3*15 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_4}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*27 + 4*30)*45 + 4*3*30 ) / (47*46*45),
                        0,
                        ( 16.0*46*45 + (4*16 + 4*16)*45 + 4*3*15 ) / (47*46*45),
                        ( 7.0*46*45 + (4*11 + 4*14)*45 + 4*3*15 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_5}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*27 + 4*30)*45 + 4*3*30 ) / (47*46*45),
                        0,
                        ( 16.0*46*45 + (4*16 + 4*16)*45 + 4*3*15 ) / (47*46*45),
                        ( 7.0*46*45 + (4*11 + 4*14)*45 + 4*3*15 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_6}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*27 + 4*29)*45 + 4*3*29 ) / (47*46*45),
                        0,
                        ( 16.0*46*45 + (4*16 + 4*17)*45 + 4*3*16 ) / (47*46*45),
                        ( 7.0*46*45 + (4*11 + 4*12)*45 + 4*3*13 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_7}, {Card::_9, Card::_5}},
            Probability{( 23.0*46*45 + (4*26 + 4*29)*45 + 4*3*29 ) / (47*46*45),
                        ( 4.0*46*45 + (4*4 + 4*4)*45 + 4*3*2 ) / (47*46*45),
                        ( 12.0*46*45 + (4*13 + 4*13)*45 + 4*3*14 ) / (47*46*45),
                        ( 11.0*46*45 + (4*13 + 4*16)*45 + 4*3*15 ) / (47*46*45)} },
        { {{Card::_4, Card::_6, Card::_A}, {Card::_9, Card::_5}},
            Probability{36.0/47 + 3.0/47*41.0/46 + 3.0/47*2.0/46*42.0/45 + 4.0/47*43.0/46,
                        4.0/47 + 3.0/47*3.0/46 + 3.0/47*2.0/46*3.0/45 + 4.0/47*3.0/46,
                        0,
                        36.0/47 + 3.0/47*41.0/46 + 3.0/47*2.0/46*42.0/45 + 4.0/47*43.0/46} },
    };
    // clang-format on

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
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndTwo_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_2 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndThree_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_3 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndFour_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_4 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndFive_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_5 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndSix_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndSeven_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_7 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndEight_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_8 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndNine_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_9 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndTen_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_10 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndAce_DealerHasNineAndSix )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_A );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndTwo_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_2 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndThree_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_3 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndFour_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_4 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndFive_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_5 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndSix_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndSeven_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_7 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
}

TEST_F( TestDealerProbabilities, PlayerHasFourAndSixAndAce_DealerHasNineAndFive )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( player, Card::_A );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_5 );

    const auto probability = computeProbabilityAfterPlayer( player, dealer, deck );
    const auto expectation = expectedProbabilityAfterPlayer[ std::make_pair(
        player.hands.front(), dealer.hands.front() ) ];
    EXPECT_THAT( probability.win, DoubleEq( expectation.win ) );
    EXPECT_THAT( probability.tie, DoubleEq( expectation.tie ) );
    EXPECT_THAT( probability.loss, DoubleEq( expectation.loss ) );
    EXPECT_THAT( probability.expectedPayout, DoubleEq( expectation.expectedPayout * betSize ) );
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

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndTen_DoubleDown )
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

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndNine_DoubleDown )
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

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndEight_DoubleDown )
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

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndSeven_DoubleDown )
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

TEST_F( TestProbabilities, PlayerHasFourAndSix_DealerHasNineAndSix_DoubleDown )
{
    drawCard( player, Card::_4 );
    drawCard( player, Card::_6 );
    drawCard( dealer, Card::_9 );
    drawCard( dealer, Card::_6 );

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
