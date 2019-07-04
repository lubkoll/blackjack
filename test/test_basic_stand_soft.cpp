#include <blackjack/Card.h>
#include <blackjack/Player.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::Hand;
using blackjack::basic::do_stand;

using testing::Eq;

class TestBasicStrategyComponent : public testing::Test
{
public:
    void addCards( Card first, Card second )
    {
        hand.push_back( first );
        hand.push_back( second );
    }

    Hand hand;
    int openDealerValue;
};

TEST_F( TestBasicStrategyComponent, do_stand_soft_for_nineteen_as_eleven_eight )
{
    Card first = Card::_A;
    Card second = Card::_8;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_stand_soft_for_eighteen_as_eleven_seven )
{
    Card first = Card::_A;
    Card second = Card::_7;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_stand( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_stand_soft_for_seventeen )
{
    Card first = Card::_A;
    Card second = Card::_6;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_stand( hand, openDealerValue ) );
    hand.clear();
}
