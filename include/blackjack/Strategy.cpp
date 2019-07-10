#include "Strategy.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace blackjack
{
    Decision defaultDealerStrategy( const std::vector< Hand >&, const Hand& hand, bool, bool, bool )
    {
        const auto max = getMaxValidValue( hand );
        return ( max < 17 && max != -1 ) ? Decision::Draw : Decision::Stand;
    }

    Decision alwaysStandStrategy( const std::vector< Hand >&, const Hand&, bool, bool, bool )
    {
        return Decision::Stand;
    }

    namespace basic
    {
        const std::vector< int > hardStandingNumbers = {13, 13, 12, 12, 12, 17, 17, 17, 17, 17};

        const std::vector< int > softStandingNumbers = {18, 18, 18, 18, 18, 18, 18, 19, 19, 18};

        const std::vector< std::vector< int > > pairSplittingNumbers = {
            {2, 3, 6, 7, 8, 9, 11},    // 2
            {2, 3, 6, 7, 8, 9, 11},    // 3
            {2, 3, 6, 7, 8, 9, 11},    // 4
            {2, 3, 4, 6, 7, 8, 9, 11}, // 5
            {2, 3, 6, 7, 8, 9, 11},    // 6
            {2, 3, 6, 7, 8, 11},       // 7
            {7, 8, 9, 11},             // 8
            {8, 9, 11},                // 9
            {8, 11},                   // 10
            {8, 11},                   // 11
        };

        const std::vector< std::vector< std::pair< int, int > > > softDoublingNumbers = {
            {{11, 6}},                                                        // 2
            {{11, 6}, {11, 7}},                                               // 3
            {{11, 2}, {11, 3}, {11, 4}, {11, 5}, {11, 6}, {11, 7}},           // 4
            {{11, 11}, {11, 2}, {11, 3}, {11, 4}, {11, 5}, {11, 6}, {11, 7}}, // 5
            {{11, 11}, {11, 2}, {11, 3}, {11, 4}, {11, 5}, {11, 6}, {11, 7}}  // 6
        };

        const std::vector< std::vector< int > > hardDoublingNumbers = {
            {9, 10, 11}, // 2
            {9, 10, 11}, // 3
            {9, 10, 11}, // 4
            {9, 10, 11}, // 5
            {9, 10, 11}, // 6
            {10, 11},    // 7
            {10, 11},    // 8
            {10, 11},    // 9
            {11},        // 10
            {11}         // 11
        };

        bool do_stand( const Hand& hand, int openDealerValue )
        {
            const auto max = getMaxValidValue( hand );
            if ( max == 14 && hand[ 0 ] == Card::_7 && hand[ 1 ] == Card::_7 &&
                 openDealerValue == 10 )
                return true;
            if ( max == 16 and hand.size() > 2 )
                return true;

            const auto threshold = isSoft( hand ) ? softStandingNumbers[ openDealerValue - 2 ]
                                                  : hardStandingNumbers[ openDealerValue - 2 ];
            return max >= threshold || max == -1;
        }

        bool do_split( const Hand& hand, int openDealerValue )
        {
            if ( !isPair( hand ) )
                return false;

            const auto& numbers = pairSplittingNumbers[ openDealerValue - 2 ];
            return find( begin( numbers ), end( numbers ), getValue( hand.front() ) ) !=
                   end( numbers );
        }

        bool do_double_down( const Hand& hand, int openDealerValue )
        {
            if ( hand.size() > 2 )
                return false;
            if ( isSoft( hand ) )
            {
                if ( openDealerValue - 2 >= softDoublingNumbers.size() )
                    return false;

                const auto& numbers = softDoublingNumbers[ openDealerValue - 2 ];
                const auto pair = std::pair< int, int >( getMaxValue( hand[ 0 ], hand[ 1 ] ),
                                                         getMinValue( hand[ 0 ], hand[ 1 ] ) );
                return std::find( begin( numbers ), end( numbers ), pair ) != end( numbers );
            }

            const auto max = getMaxValidValue( hand );
            if ( ( openDealerValue == 5 or openDealerValue == 6 ) and max == 8 )
            {
                return !( ( hand[ 0 ] == Card::_6 and hand[ 1 ] == Card::_2 ) or
                          ( hand[ 0 ] == Card::_2 and hand[ 1 ] == Card::_6 ) );
            }

            const auto& numbers = hardDoublingNumbers[ openDealerValue - 2 ];
            return find( begin( numbers ), end( numbers ), max ) != end( numbers );
        }
    }

    BasicStrategy::BasicStrategy( Hand& dealerHand ) : dealerHand( dealerHand )
    {
    }

    Decision BasicStrategy::operator()( const std::vector< Hand >&, const Hand& hand,
                                        bool splitAllowed, bool doubleDownAllowed, bool )
    {
        using namespace basic;
        const auto openDealerValue = getValue( dealerHand.front() );
        if ( splitAllowed && do_split( hand, openDealerValue ) )
            return Decision::Split;

        //            std::cout << openDealerValue << " || " << hand << std::endl;
        if ( doubleDownAllowed && do_double_down( hand, openDealerValue ) )
            return Decision::DoubleDown;

        if ( do_stand( hand, openDealerValue ) )
            return Decision::Stand;
        return Decision::Draw;
    }

    namespace ten_count
    {
        const auto dmin = std::numeric_limits< double >::lowest();
        const auto dmax = std::numeric_limits< double >::max();

        static const auto yes = dmax;
        static const auto no = dmin;
        static const auto stand = dmax;
        static const auto draw = dmin;

        const std::vector< std::vector< double > > splittingNumbers = {
            // 2    3       4       5       6       7       8       9       10      11
            {3.1, 3.8, yes, yes, yes, 1.1, 3.8, no, no, no},    // 2
            {yes, yes, yes, yes, yes, 1.1, 2.4, 4.2, 5.3, no},  // 3
            {1.3, 1.6, 1.9, 2.4, 2.1, no, no, no, no, no},      // 4
            {no, no, no, no, no, no, no, no, no, no},           // 5
            {2.4, 2.6, 3.0, 3.6, 4.1, 3.4, no, no, no, no},     // 6
            {yes, yes, yes, yes, yes, yes, yes, no, no, 1.4},   // 7
            {yes, yes, yes, yes, yes, yes, yes, yes, 1.6, 4.8}, // 8
            {2.4, 2.8, 3.1, 3.7, 3.2, 1.6, yes, 4.2, no, 1.5},  // 9
            {1.4, 1.5, 1.7, 1.9, 1.8, no, no, no, no, no},      // 10
            {4.0, 4.1, 4.5, 4.9, 5.0, 3.8, 3.3, 3.1, 3.2, 2.6}, // 11
        };

        namespace
        {
            struct pair
            {
                int dealerValue;
                int playerValue;
            };

            bool operator==( const pair& lhs, const pair& rhs )
            {
                return lhs.dealerValue == rhs.dealerValue && lhs.playerValue == rhs.playerValue;
            }
        }

        const std::vector< pair > inverseRatios = {{10, 8}, {7, 3}, {8, 3}, {9, 3},
                                                   {10, 3}, {7, 3}, {8, 3}};

        const std::vector< std::vector< double > > softDoubleDownNumbers = {
            // 2    3       4       5       6       7
            {1.5, 1.7, 2.1, 2.6, 2.7, no},  // A,2
            {1.5, 1.8, 2.3, 2.9, 3.0, no},  // A,3
            {1.6, 1.9, 2.4, 3.0, 3.2, no},  // A,4
            {1.6, 1.9, 2.5, 3.1, 4.0, no},  // A,5
            {2.1, 2.5, 3.2, 4.8, 4.8, 1.1}, // A,6
            {2.0, 2.2, 3.3, 3.8, 3.5, no},  // A,7
            {1.4, 1.7, 1.8, 2.0, 2.0, no},  // A,8
            {1.3, 1.3, 1.5, 1.6, 1.6, no}   // A,9

        };

        const std::vector< std::vector< double > > hardDoubleDownNumbers = {
            // 2    3       4       5       6       7       8       9       10      11
            {no, no, 1.0, 1.1, 1.1, no, no, no, no, no},        // 5
            {no, no, 1.0, 1.2, 1.3, no, no, no, no, no},        // 6
            {0.9, 1.1, 1.2, 1.4, 1.4, no, no, no, no, no},      // 7
            {1.3, 1.5, 1.7, 2.0, 2.1, 1.0, no, no, no, no},     // 8
            {2.2, 2.4, 2.8, 3.3, 3.4, 2.0, 1.6, no, no, 0.9},   // 9
            {3.7, 4.2, 4.8, 5.6, 5.7, 3.8, 3.0, 2.5, 1.9, 1.8}, // 10
            {3.9, 4.2, 4.8, 5.5, 5.5, 3.7, 3.0, 2.6, 2.8, 2.2}, // 11
        };

        const std::vector< std::vector< double > > softStandingNumbers = {
            // 2    3       4       5       6       7       8       9       10      11
            {stand, stand, stand, stand, stand, stand, stand, draw, draw, 2.2},     // 18
            {stand, stand, stand, stand, stand, stand, stand, stand, stand, stand}, // 19
        };

        const std::vector< std::vector< double > > hardStandingNumbers = {
            // 2    3       4       5       6       7       8       9       10      11
            {2.0, 2.1, 2.2, 2.4, 2.3, draw, draw, draw, 1.1, 1.0},                  // 12
            {2.3, 2.5, 2.6, 3.0, 2.7, draw, draw, draw, 1.3, 1.1},                  // 13
            {2.7, 2.9, 3.3, 3.7, 3.4, draw, draw, 1.1, 1.6, 1.2},                   // 14
            {3.2, 3.6, 4.1, 4.8, 4.3, draw, draw, 1.4, 1.9, 1.3},                   // 15
            {3.9, 4.5, 5.3, 6.5, 4.6, draw, 1.2, 1.7, 2.2, 1.4},                    // 16
            {stand, stand, stand, stand, stand, stand, stand, stand, stand, 3.1},   // 17
            {stand, stand, stand, stand, stand, stand, stand, stand, stand, stand}, // 18
        };

        bool do_split( const Hand& hand, int openDealerValue, double tenRatio,
                       bool doubleDownOnEightAllowed )
        {
            if ( !isPair( hand ) )
                return false;

            auto threshold =
                splittingNumbers[ getValue( hand.front() ) - 2 ][ openDealerValue - 2 ];
            if ( hand.front() == Card::_4 && openDealerValue == 6 )
            {
                if ( !doubleDownOnEightAllowed )
                    return tenRatio <= threshold;
                return false;
            }
            const auto useInverseRatios =
                find( begin( inverseRatios ), end( inverseRatios ),
                      pair{openDealerValue, getValue( hand.front() )} ) != end( inverseRatios );
            if ( useInverseRatios )
                return tenRatio > threshold;
            return tenRatio <= threshold;
        }

        bool do_double_down( const Hand& hand, int openDealerValue, double tenRatio )
        {
            double threshold = 0;
            if ( isSoft( hand ) )
            {
                const auto minValue = getMinValue( hand[ 0 ], hand[ 1 ] );
                if ( openDealerValue > 7 || hand.size() > 2 || minValue > 9 )
                    return false;
                threshold = softDoubleDownNumbers[ minValue - 2 ][ openDealerValue - 2 ];
            }
            else
            {
                const auto max = getMaxValidValue( hand );
                if ( max == -1 || max == 4 || max > 11 || ( max == 6 && hand[ 0 ] == Card::_3 ) )
                    return false;
                threshold = hardDoubleDownNumbers[ max - 5 ][ openDealerValue - 2 ];
            }

            return tenRatio <= threshold;
        }

        int findStandingNumber( const std::vector< std::vector< double > >& standingNumbers,
                                int openDealerValue, double tenRatio )
        {
            for ( int i = 0; i < standingNumbers.size(); ++i )
            {
                if ( tenRatio <= standingNumbers[ i ][ openDealerValue - 2 ] )
                    return i;
            }
            std::cout << "Could not find standing number for " << openDealerValue << ", "
                      << tenRatio << std::endl;
            std::cout << standingNumbers[ 0 ][ 0 ] << std::endl;
            assert( false );
            return -1;
        }

        bool do_stand( const Hand& hand, int openDealerValue, double tenRatio )
        {
            const auto playerValue = getMaxValidValue( hand );
            //            std::cout << " = do_stand: soft: " << isSoft(hand) << std::endl;
            const auto standingNumber =
                isSoft( hand )
                    ? findStandingNumber( softStandingNumbers, openDealerValue, tenRatio ) + 18
                    : findStandingNumber( hardStandingNumbers, openDealerValue, tenRatio ) + 12;
            //            std::cout << "standing number: " << standingNumber << std::endl;
            //            std::cout << "max: " << getMaxValidValue(hand) << std::endl;
            return standingNumber <= playerValue;
        }
    }

    TenCountStrategy::TenCountStrategy( Deck& deck, Hand& dealerHand )
        : deck( deck ), dealerHand( dealerHand )
    {
    }

    TenCountStrategy::~TenCountStrategy()
    {
        //        std::cout << "min ratio: " << minRatio << std::endl;
    }

    Decision TenCountStrategy::operator()( const std::vector< Hand >& hands, const Hand& hand,
                                           bool splitAllowed, bool doubleDownAllowed,
                                           bool insuranceAllowed ) const
    {
        const auto tenRatio = computeTenCount( hands );
        if ( insuranceAllowed && dealerHand.front() == Card::_A && tenRatio < 2 )
            return Decision::Insure;

        if ( isBust( hand ) )
            return Decision::Stand;
        const auto openDealerValue = getValue( dealerHand.front() );
        if ( splitAllowed && ten_count::do_split( hand, openDealerValue, tenRatio ) )
            return Decision::Split;

        //            std::cout << openDealerValue << " || " << hand << std::endl;
        if ( doubleDownAllowed && ten_count::do_double_down( hand, openDealerValue, tenRatio ) )
            return Decision::DoubleDown;

        if ( ten_count::do_stand( hand, openDealerValue, tenRatio ) )
            return Decision::Stand;
        return Decision::Draw;
    }

    double TenCountStrategy::computeTenCount( const std::vector< Hand >& hands ) const
    {
        const auto fullTenCount = deck.getFullCount( 10 );
        //            std::cout << "full ten count: " << fullTenCount << ", " <<
        //            deck.getFullCount(Card::_K) << std::endl;

        //            std::cout << "tens in hand: " << getNumberOf(hand, 10) << std::endl;
        auto tensInPlay = ( ( getValue( dealerHand.front() ) == 10 ) ? 1 : 0 );
        auto nonTensInPlay = 1;
        for ( auto& hand : hands )
        {
            tensInPlay += getNumberOf( hand, 10 );
            nonTensInPlay += hand.size();
        }
        nonTensInPlay -= tensInPlay;
        //            std::cout << "dealer tens: " << (tensInPlay - getNumberOf(hand, 10)) <<
        //            std::endl;

        const auto tens = fullTenCount - deck.getUsedCount( 10 ) - tensInPlay;
        const auto nonTens = ( deck.getInitialSize() - fullTenCount ) -
                             deck.getUsedCountExcept( 10 ) - nonTensInPlay;

        //            std::cout << "used tens: " << deck.getUsedCount(10) << std::endl;
        //            std::cout << "used nontens: " << deck.getUsedCountExcept(10) << std::endl;

        //            std::cout << "deck non tens: " << ((deck.getInitialSize() - fullTenCount) -
        //            deck.getUsedCountExcept(10)) << std::endl;
        //            std::cout << "non tens in play: " << nonTensInPlay << std::endl;
        //            std::cout << "non tens: " << nonTens << std::endl;
        //            std::cout << "deck tens: " << (fullTenCount - deck.getUsedCount(10)) <<
        //            std::endl;
        //            std::cout << "tens in play: " << tensInPlay << std::endl;
        //            std::cout << "tens: " << tens << std::endl;
        const auto tenRatio =
            tens == 0 ? std::numeric_limits< double >::max() : double( nonTens ) / tens;
        minRatio = std::min( minRatio, tenRatio );
        std::cout << "ratio: " << tenRatio << std::endl;
        return tenRatio;
    }
}
