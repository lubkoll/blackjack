#include <blackjack/Card.h>
#include <blackjack/Player.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::Hand;
using blackjack::basic::do_split;

using testing::Eq;

class TestBasicStrategyComponent : public testing::Test
{
public:
    void add( Card value )
    {
        hand.push_back( value );
        hand.push_back( value );
    }

    Hand hand;
    int openDealerValue;
};

TEST_F( TestBasicStrategyComponent, do_split_aces )
{
    const auto value = Card::_A;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_tens )
{
    const auto value = Card::_Q;

    openDealerValue = 2;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_nines )
{
    const auto value = Card::_9;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_eights )
{
    const auto value = Card::_8;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_sevens )
{
    const auto value = Card::_7;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_sixes )
{
    const auto value = Card::_6;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_fives )
{
    const auto value = Card::_5;

    openDealerValue = 2;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_fours )
{
    const auto value = Card::_4;

    openDealerValue = 2;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_threes )
{
    const auto value = Card::_3;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_split_twos )
{
    const auto value = Card::_2;

    openDealerValue = 2;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    add( value );
    EXPECT_TRUE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    add( value );
    EXPECT_FALSE( do_split( hand, openDealerValue ) );
    hand.clear();
}
