#include "ZenCount.h"

namespace blackjack
{
    namespace zen_count
    {
        const auto stand = std::numeric_limits< int >::lowest();
        const auto draw = std::numeric_limits< int >::max();

        // clang-format off
        const std::vector<std::vector<int> > hardStandingNumbers =
        {
            {     1,     1,     0,    -1,     0,  draw,  draw,  draw,  draw,  draw }, // 12
            {     0,    -1,    -1,    -2,    -2,  draw,  draw,  draw,  draw,  draw }, // 13
            {    -1,    -2,    -2,    -3,    -3,  draw,  draw,  draw,     3,     5 }, // 14
            {    -2,    -3,    -4,    -4, stand,  draw,     5,     4,     1,     4 }, // 15
            {    -4, stand, stand, stand, stand,     5,     4,     2,     0,     3 }, // 16
            { stand, stand, stand, stand, stand, stand, stand, stand, stand,    -3 }  // 17
        };

        const auto none = std::numeric_limits<int>::max();
        const auto dd = std::numeric_limits<int>::lowest();

        const std::vector<std::vector<int> > hardDoubleDownNumbers =
        {
            {  none,  none,     5,     5,     5,  none,  none,  none,  none,  none }, // 7
            {     5,     4,     3,     2,     1,  none,  none,  none,  none,  none }, // 8
            {     0,     0,    -1,    -2,    -3,     2,     4,  none,  none,  none }, // 9
            {    -4,    -4,    dd,    dd,    dd,    -3,    -2,    -1,     1,     1 }, // 10
            {    dd,    dd,    dd,    dd,    dd,    -4,    -3,    -2,    -2,     0 }  // 11
        };

        const std::vector< std::vector< int > > softDoubleDownNumbers = {
            //   2    3    4    5    6
            { none,   3,   1,   0,  -1 }, // A,2
            { none,   3,   1,  -1,  -2 }, // A,3
            { none,   2,   0,  -2,  -4 }, // A,4
            {    5,   1,  -1,  -3,  dd }, // A,5
            {    0,  -1,  -2,  -4,  dd }, // A,6
            {    0,  -1,  -2,  -3,  -3 }, // A,7
            {    3,   2,   1,   0,   0 }, // A,8
            {    4,   3,   3,   2,   2 }  // A,9
        };

        const auto split = std::numeric_limits<int>::lowest();
        const std::vector<std::vector<int> > splittingNumbers =
        {
            {    -2,    -2, split, split, split, split,     3,  none,  none,  none }, // 2
            {    -2, split, split, split, split, split,     2,  none,  none,  none }, // 3
            {  none,     3,     1,     0,    -1,  none,  none,  none,  none,  none }, // 4
            {  none,  none,  none,  none,  none,  none,  none,  none,  none,  none }, // 5
            {    -1,    -2, split, split, split, split,  none,  none,  none,  none }, // 6
            { split, split, split, split, split, split,     1,  none,  none,  none }, // 7
            { split, split, split, split, split, split, split, split,     4, split }, // 8
            {    -1,    -2,    -2, split, split,     1, split, split,  none,     1 }, // 9
            {     4,     3,     3,     2,     2,  none,  none,  none,  none,  none }, // 10
            { split, split, split, split, split, split, split, split, split,    -2 }, // 11
        };
        // clang-format on

        bool do_split( const Hand& hand, int openDealerValue, double pointRatio )
        {
            if ( !isPair( hand ) )
                return false;

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
                return pointRatio > softDoubleDownNumbers[ minValue - 2 ][ openDealerValue - 2 ];
            }

            const auto value = getMaxValidValue( hand );
            if ( value < 7 || value > 11 )
                return false;

            return pointRatio > hardDoubleDownNumbers[ value - 7 ][ openDealerValue - 2 ];
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
                    if ( openDealerValue < 9 || ( openDealerValue == 11 && pointRatio > 2 ) )
                        return true;
                }
                return false;
            }

            if ( playerValue < 12 )
                return false;

            if ( playerValue > 17 )
                return true;

            return pointRatio > hardStandingNumbers[ playerValue - 12 ][ openDealerValue - 2 ];
        }
    }

    ZenCountStrategy::ZenCountStrategy( Deck& deck, Hand& dealerHand )
        : deck( deck ), dealerHand( dealerHand )
    {
    }

    Decision ZenCountStrategy::operator()( const std::vector< Hand >& hands, const Hand& hand,
                                           bool splitAllowed, bool doubleDownAllowed,
                                           bool insuranceAllowed ) const
    {
        const auto pointRatio = computeZenCountRatio( hands );
        if ( insuranceAllowed )
        {
            if ( dealerHand.front() == Card::_A && pointRatio > 8 )
                return Decision::Insure;
        }

        if ( isBust( hand ) )
            return Decision::Stand;
        const auto openDealerValue = getValue( dealerHand.front() );
        if ( splitAllowed && zen_count::do_split( hand, openDealerValue, pointRatio ) )
            return Decision::Split;

        //            std::cout << openDealerValue << " || " << hand << std::endl;
        if ( doubleDownAllowed && zen_count::do_double_down( hand, openDealerValue, pointRatio ) )
            return Decision::DoubleDown;

        if ( zen_count::do_stand( hand, openDealerValue, pointRatio ) )
            return Decision::Stand;
        return Decision::Draw;
    }

    double ZenCountStrategy::computeZenCountRatio( const std::vector< Hand >& hands ) const
    {
        const auto pointsInPlay = computeZenPointsInPlay( hands, dealerHand.front() );
        return computeZenPointRatio( pointsInPlay, deck );
    }

    ZenCountBettingStrategy::ZenCountBettingStrategy( double minBet ) noexcept : minBet( minBet )
    {
    }

    double ZenCountBettingStrategy::operator()( const Deck& deck ) const noexcept
    {
        const auto pointRatio = computeZenPointRatio( 0, deck );
        if ( pointRatio < 2 )
            return minBet;

        return std::min( std::round( pointRatio ), 5.0 ) * 4;
        //        const auto edge = int(std::floor( pointRatio ) + 0.1);
        //        if(edge == 2)
        //            return minBet;
        //        if(edge == 3)
        //            return 5*minBet;
        //        if(edge == 4)
        //            return 12*minBet;

        //        return 20*minBet;
    }

    int getZenPoints( Card card )
    {
        if ( Card::_2 == card || Card::_3 == card || Card::_7 == card )
            return 1;
        if ( Card::_4 == card || Card::_5 == card || Card::_6 == card )
            return 2;
        if ( Card::_10 == card )
            return -2;
        if ( Card::_A == card )
            return -1;
        return 0;
    }

    int computeZenPoints( const Hand& hand )
    {
        return accumulate( begin( hand ), end( hand ), 0,
                           []( int sum, Card card ) { return sum + getZenPoints( card ); } );
    }

    int computeZenPointsInPlay( const std::vector< Hand >& hands, Card openDealerCard )
    {
        return accumulate(
            begin( hands ), end( hands ), getZenPoints( openDealerCard ),
            []( int sum, const Hand& hand ) { return sum + computeZenPoints( hand ); } );
    }

    double computeZenPointRatio( int pointsInPlay, const Deck& deck )
    {
        const auto points = deck.getUsedCount( Card::_2 ) + deck.getUsedCount( Card::_3 ) +
                            2 * deck.getUsedCount( Card::_4 ) + 2 * deck.getUsedCount( Card::_5 ) +
                            2 * deck.getUsedCount( Card::_6 ) + deck.getUsedCount( Card::_7 ) -
                            2 * deck.getUsedCount( Card::_10 ) - 2 * deck.getUsedCount( Card::_J ) -
                            2 * deck.getUsedCount( Card::_Q ) - 2 * deck.getUsedCount( Card::_K ) -
                            deck.getUsedCount( Card::_A );
        return double( points + pointsInPlay ) / deck.size() * 13;
    }
}
