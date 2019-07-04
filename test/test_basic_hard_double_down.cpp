#include <blackjack/Card.h>
#include <blackjack/Player.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using blackjack::Card;
using blackjack::Hand;
using blackjack::basic::do_double_down;

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

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eleven_as_nine_two )
{
    const auto first = Card::_9;
    const auto second = Card::_2;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eleven_as_eight_three )
{
    const auto first = Card::_8;
    const auto second = Card::_3;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eleven_as_seven_four )
{
    const auto first = Card::_7;
    const auto second = Card::_4;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eleven_as_six_five )
{
    const auto first = Card::_6;
    const auto second = Card::_5;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_ten_as_eight_two )
{
    const auto first = Card::_8;
    const auto second = Card::_2;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_ten_as_seven_three )
{
    const auto first = Card::_7;
    const auto second = Card::_3;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_ten_as_six_four )
{
    const auto first = Card::_6;
    const auto second = Card::_4;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_ten_as_five_five )
{
    const auto first = Card::_5;
    const auto second = Card::_5;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_nine_as_seven_two )
{
    const auto first = Card::_7;
    const auto second = Card::_2;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_nine_as_six_three )
{
    const auto first = Card::_6;
    const auto second = Card::_3;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_nine_as_five_four )
{
    const auto first = Card::_5;
    const auto second = Card::_4;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eight_as_six_two )
{
    const auto first = Card::_6;
    const auto second = Card::_2;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eight_as_five_three )
{
    const auto first = Card::_5;
    const auto second = Card::_3;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}

TEST_F( TestBasicStrategyComponent, do_double_down_hard_for_eight_as_four_four )
{
    const auto first = Card::_4;
    const auto second = Card::_4;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 3;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 4;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 5;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 6;
    addCards( first, second );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_TRUE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 7;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 8;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 9;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 10;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();

    openDealerValue = 11;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
}
