#include "PointCount.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

namespace blackjack
{
    namespace point_count
    {
        const auto stand = std::numeric_limits< int >::lowest();
        const auto draw = std::numeric_limits< int >::max();

        // clang-format off
        const std::vector<std::vector<int> > hardStandingNumbers =
        {
            {    14,     6,     2,    -1,     0,  draw,  draw,  draw,  draw,  draw }, // 12
            {     1,    -2,    -5,    -9,    -8,    50,  draw,  draw,  draw,  draw }, // 13
            {    -5,    -8,   -13,   -17,   -17,    20,    38,  draw,  draw,  draw }, // 14
            {   -12,   -17,   -21,   -26,   -28,    13,    15,    12,     8,    16 }, // 15
            {   -21,   -25,   -30,   -34,   -35,    10,    11,     6,     2,    14 }, // 16
            { stand, stand, stand, stand, stand, stand, stand, stand, stand,   -15 }  // 17
        };

        const auto none = std::numeric_limits<int>::max();

        const std::vector<std::vector<int> > hardDoubleDownNumbers =
        {
            {  none,  none,  none,    20,    26,  none,  none,  none,  none,  none }, // 5
            {  none,  none,    27,    18,    24,  none,  none,  none,  none,  none }, // 6
            {  none,    45,    21,    14,    17,  none,  none,  none,  none,  none }, // 7
            {  none,    22,    11,     5,     5,    22,  none,  none,  none,  none }, // 8
            {     3,     0,    -5,   -10,   -12,     4,    14,  none,  none,  none }, // 9
            {   -15,   -17,   -21,   -24,   -26,   -17,    -9,    -3,     7,     6 }, // 10
            {   -23,   -26,   -29,   -33,   -35,   -26,   -16,   -10,    -9,    -3 }  // 11
        };

        const std::vector< std::vector< int > > softDoubleDownNumbers = {
            // 3       4       5       6       7
            { 10,   2, -19, -13 }, // A,2
            { 11,  -3, -13, -19 }, // A,3
            { 19,  -7, -16, -23 }, // A,4
            { 21,  -6, -16, -32 }, // A,5
            { -6, -14, -28, -30 }, // A,6
            { -2, -15, -18, -23 }, // A,7
            {  9,   5,   1,   0 }, // A,8
            { 20,  12,   8,   8 }  // A,9
        };

        const auto split = std::numeric_limits<int>::lowest();
        const std::vector<std::vector<int> > splittingNumbers =
        {
            {    -9,   -15,   -22,   -30, split, split,  none,  none,  none,  none }, // 2
            {   -21,   -34, split, split, split, split,  none,  none,  none,  none }, // 3
            {  none,    18,     8,     0,  none,  none,  none,  none,  none,  none }, // 4
            {  none,  none,  none,  none,  none,  none,  none,  none,  none,  none }, // 5
            {     0,    -3,    -8,   -13,   -16,    -8,  none,  none,  none,  none }, // 6
            {   -22,   -29,   -35, split, split, split, split,  none,  none,  none }, // 7
            { split, split, split, split, split, split, split, split,  none,   -18 }, // 8
            {    -3,    -8,   -10,   -15,   -14,     8,   -16,   -22,  none,    10 }, // 9
            {    25,    17,    10,     6,     7,    19,  none,  none,  none,  none }, // 10
            { split, split, split, split, split,   -33,   -24,   -22,   -20,   -17 }, // 11
        };
        // clang-format on

        bool do_split( const Hand& hand, int openDealerValue, double pointRatio,
                       bool doubleDownOnEightAllowed )
        {
            if ( !isPair( hand ) )
                return false;

            if ( hand.front() == Card::_8 && openDealerValue == 10 && pointRatio < 24 )
                return true;
            if ( hand.front() == Card::_4 && openDealerValue == 6 && !doubleDownOnEightAllowed &&
                 pointRatio > 5 )
                return true;
            if ( hand.front() == Card::_3 && openDealerValue == 8 &&
                 ( pointRatio > 6 || pointRatio < -2 ) )
                return true;
            return pointRatio >
                   splittingNumbers[ getValue( hand.front() ) - 2 ][ openDealerValue - 2 ];
        }

        bool do_double_down( const Hand& hand, int openDealerValue, double pointRatio )
        {
            if ( isSoft( hand ) )
            {
                const auto minValue = getMinValue( hand.front(), hand.back() );
                if ( hand.size() != 2 || openDealerValue > 6 || minValue > 9 )
                    return false;
                if ( openDealerValue == 2 && minValue == 6 && pointRatio > 0 && pointRatio < 11 )
                    return true;
                return pointRatio > softDoubleDownNumbers[ minValue - 2 ][ openDealerValue - 2 ];
            }

            const auto value = getMaxValidValue( hand );
            if ( value < 5 || value > 11 )
                return false;

            return pointRatio > hardDoubleDownNumbers[ value - 5 ][ openDealerValue - 2 ];
        }

        bool do_stand( const Hand& hand, int openDealerValue, double pointRatio )
        {
            const auto playerValue = getMaxValidValue( hand );
            if ( isSoft( hand ) )
            {
                if ( playerValue > 18 )
                    return true;
                if ( playerValue == 18 )
                {
                    if ( openDealerValue < 9 || ( openDealerValue == 10 && pointRatio > 12 ) ||
                         ( openDealerValue == 11 && pointRatio > -6 ) )
                        return true;
                }
                if ( playerValue == 17 && openDealerValue == 7 && pointRatio > 29 )
                    return true;
                return false;
            }

            if ( playerValue < 12 )
                return false;

            if ( playerValue > 17 )
                return true;

            return pointRatio > hardStandingNumbers[ playerValue - 12 ][ openDealerValue - 2 ];
        }
    }

    PointCountStrategy::PointCountStrategy( Deck& deck, Hand& dealerHand )
        : deck( deck ), dealerHand( dealerHand )
    {
    }

    Decision PointCountStrategy::operator()( const std::vector< Hand >& hands, const Hand& hand,
                                             bool splitAllowed, bool doubleDownAllowed,
                                             bool insuranceAllowed ) const
    {
        const auto pointRatio = computePointCountRatio( hands );
        if ( insuranceAllowed )
        {
            if ( dealerHand.front() == Card::_A && pointRatio > 8 )
                return Decision::Insure;
        }

        if ( isBust( hand ) )
            return Decision::Stand;
        const auto openDealerValue = getValue( dealerHand.front() );
        if ( splitAllowed && point_count::do_split( hand, openDealerValue, pointRatio ) )
            return Decision::Split;

        //            std::cout << openDealerValue << " || " << hand << std::endl;
        if ( doubleDownAllowed && point_count::do_double_down( hand, openDealerValue, pointRatio ) )
            return Decision::DoubleDown;

        if ( point_count::do_stand( hand, openDealerValue, pointRatio ) )
            return Decision::Stand;
        return Decision::Draw;
    }

    double PointCountStrategy::computePointCountRatio( const std::vector< Hand >& hands ) const
    {
        const auto pointsInPlay = computePointsInPlay( hands, dealerHand.front() );
        return computePointRatio( pointsInPlay, deck );
    }

    namespace simplified_point_count
    {
        bool do_split( const Hand& hand, int openDealerValue, double, bool )
        {
            if ( !isPair( hand ) )
                return false;

            return hand.front() == Card::_A || hand.front() == Card::_8 ||
                   ( openDealerValue < 8 &&
                     ( hand.front() == Card::_7 || hand.front() == Card::_6 ||
                       hand.front() == Card::_3 || hand.front() == Card::_2 ) );
        }

        bool do_double_down( const Hand& hand, int openDealerValue, double pointRatio )
        {
            if ( isSoft( hand ) )
            {
                const auto minValue = getMinValue( hand.front(), hand.back() );
                return minValue < 8 && ( openDealerValue == 5 || openDealerValue == 6 );
            }

            const auto value = getMaxValidValue( hand );
            if ( value > 11 )
                return false;
            if ( value == 11 )
                return true;
            if ( value == 10 && ( openDealerValue < 10 || pointRatio > 10 ) )
                return true;
            if ( value == 9 )
            {
                if ( pointRatio > 10 )
                {
                    return openDealerValue < 8;
                }
                return openDealerValue < 7 && openDealerValue > 3;
            }

            if ( pointRatio > 10 && value == 8 )
            {
                return openDealerValue < 7 && openDealerValue > 3;
            }

            return false;
        }

        bool do_stand( const Hand& hand, int openDealerValue, double pointRatio )
        {
            const auto playerValue = getMaxValidValue( hand );
            if ( playerValue < 12 )
                return false;
            if ( playerValue > 18 )
                return true;

            if ( isSoft( hand ) )
            {
                if ( openDealerValue > 8 )
                    return playerValue > 18;
                return playerValue > 17;
            }

            if ( openDealerValue < 4 )
            {
                return playerValue > std::min( 12 - int( pointRatio ) / 8, 16 );
            }

            if ( openDealerValue < 7 )
            {
                return playerValue > std::min( 11 - int( pointRatio ) / 8, 16 );
            }

            return playerValue > 16 - ( pointRatio > 14 ? 2 : 0 );
        }
    }

    SimplifiedPointCountStrategy::SimplifiedPointCountStrategy( Deck& deck, Hand& dealerHand )
        : deck( deck ), dealerHand( dealerHand )
    {
    }

    Decision SimplifiedPointCountStrategy::operator()( const std::vector< Hand >& hands,
                                                       const Hand& hand, bool splitAllowed,
                                                       bool doubleDownAllowed,
                                                       bool insuranceAllowed ) const
    {
        const auto pointRatio = computePointCountRatio( hands );
        if ( insuranceAllowed )
        {
            if ( dealerHand.front() == Card::_A && pointRatio > 8 )
                return Decision::Insure;
        }

        if ( isBust( hand ) )
            return Decision::Stand;
        const auto openDealerValue = getValue( dealerHand.front() );
        if ( splitAllowed && simplified_point_count::do_split( hand, openDealerValue, pointRatio ) )
            return Decision::Split;

        if ( doubleDownAllowed &&
             simplified_point_count::do_double_down( hand, openDealerValue, pointRatio ) )
            return Decision::DoubleDown;

        if ( simplified_point_count::do_stand( hand, openDealerValue, pointRatio ) )
            return Decision::Stand;
        return Decision::Draw;
    }

    double
    SimplifiedPointCountStrategy::computePointCountRatio( const std::vector< Hand >& hands ) const
    {
        const auto pointsInPlay = computePointsInPlay( hands, dealerHand.front() );
        return computePointRatio( pointsInPlay, deck );
    }

    PointCountBettingStrategy::PointCountBettingStrategy( double minBet ) noexcept
        : minBet( minBet )
    {
    }

    double PointCountBettingStrategy::operator()( const Deck& deck ) const noexcept
    {
        const auto pointRatio = computePointRatio( 0, deck );
        const auto edge = std::floor( pointRatio / 2 );
        if ( edge < 1.9 )
            return minBet;
        return std::min( edge, 5.0 ) * minBet;
    }

    int getPoints( Card card )
    {
        const auto maxSmallValue = 7;
        const auto minLargeValue = 9;
        const auto value = getValue( card );
        if ( value <= maxSmallValue )
            return 1;
        if ( value >= minLargeValue )
            return -1;
        return 0;
    }

    int computePoints( const Hand& hand )
    {
        return accumulate( begin( hand ), end( hand ), 0,
                           []( int sum, Card card ) { return sum + getPoints( card ); } );
    }

    int computePointsInPlay( const std::vector< Hand >& hands, Card openDealerCard )
    {
        return accumulate(
            begin( hands ), end( hands ), getPoints( openDealerCard ),
            []( int sum, const Hand& hand ) { return sum + computePoints( hand ); } );
    }

    double computePointRatio( int pointsInPlay, const Deck& deck )
    {
        const auto points = deck.getUsedCount( Card::_2 ) + deck.getUsedCount( Card::_3 ) +
                            deck.getUsedCount( Card::_4 ) + deck.getUsedCount( Card::_5 ) +
                            deck.getUsedCount( Card::_6 ) + deck.getUsedCount( Card::_7 ) -
                            deck.getUsedCount( Card::_9 ) - deck.getUsedCount( Card::_10 ) -
                            deck.getUsedCount( Card::_J ) - deck.getUsedCount( Card::_Q ) -
                            deck.getUsedCount( Card::_K ) - deck.getUsedCount( Card::_A );
        return 100 * double( points + pointsInPlay ) / deck.size();
    }
}
