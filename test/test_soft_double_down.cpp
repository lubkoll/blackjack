#include <Card.h>
#include <Player.h>

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

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_seven )
{
    const auto first = Card::_A;
    const auto second = Card::_7;

    openDealerValue = 2;
    addCards( first, second );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
    hand.clear();
    addCards( second, first );
    EXPECT_FALSE( do_double_down( hand, openDealerValue ) );
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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_six )
{
    const auto first = Card::_A;
    const auto second = Card::_6;

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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_five )
{
    const auto first = Card::_A;
    const auto second = Card::_5;

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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_four )
{
    const auto first = Card::_A;
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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_three )
{
    const auto first = Card::_A;
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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_two )
{
    const auto first = Card::_A;
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
}

TEST_F( TestBasicStrategyComponent, do_double_down_soft_for_ace_ace )
{
    const auto first = Card::_A;
    const auto second = Card::_A;

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
}
