#include "ComputeProbability.h"

#include <blackjack/Card.h>
#include <blackjack/Draw.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

#include <cassert>
#include <iostream>
#include <map>
#include <tuple>

namespace blackjack
{
    Expectation computeExpectationAfterPlayer( Player& player, Player& dealer, Deck& deck,
                                               bool firstCall )
    {
        assert( player.hands.size() <= 2 );
        Expectation probability;
        bool allBust = true;
        if ( firstCall )
        {
            for ( auto i = 0u; i < player.hands.size(); ++i )
            {
                const auto maxPlayerValue = getMaxValidValue( player.hands[ i ] );
                if ( maxPlayerValue == -1 )
                {
                    const auto p = 1.0 / player.hands.size();
                    probability.loss += p;
                    probability.payout -= p * player.bets[ i ];
                }
                else
                {
                    allBust = false;
                }
            }
        }

        if ( firstCall && allBust )
        {
            return probability;
        }

        const auto decision = dealer.decider( dealer.hands, dealer.hands.front() );
        if ( decision == Decision::Draw )
        {
            return drawPossibleCardsAndEvaluate(
                dealer.hands.front(), deck, [&player, &dealer, &deck] {
                    return computeExpectationAfterPlayer( player, dealer, deck, false );
                } );
        }

        const auto p = 1.0 / player.hands.size();
        for ( auto i = 0u; i < player.hands.size(); ++i )
        {
            //            std::cout << "bet: " << player.bets[ i ] << std::endl;
            //            std::cout << "final player hand: " << std::endl;
            //            std::cout << player.hands[ i ] << std::endl;
            //            std::cout << "final dealer hand: " << std::endl;
            //            std::cout << dealer.hands.front() << std::endl;
            const auto maxPlayerValue = getMaxValidValue( player.hands[ i ] );
            const auto maxDealerValue = getMaxValidValue( dealer.hands.front() );
            if ( maxPlayerValue == -1 )
                continue;
            if ( maxPlayerValue > maxDealerValue )
            {
                probability.win += p;
                probability.payout += p * player.bets[ i ];
                continue;
            }
            if ( maxPlayerValue == maxDealerValue )
            {
                probability.tie += p;
                continue;
            }

            probability.loss += p;
            probability.payout -= p * player.bets[ i ];
        }

        return probability;
    }

    namespace
    {
        Expectation computeProbabilityAfterStartingHandImpl( Player& player, Player& dealer,
                                                             Deck& deck, const Rules& rules,
                                                             bool splitAces = false,
                                                             bool wasSplit = false )
        {
            //            std::cout << __PRETTY_FUNCTION__ << std::endl;
            for ( auto i = 0u; i < player.hands.size(); ++i )
            {
                auto& hand = player.hands[ i ];
                auto decision = hand.size() > 1
                                    ? player.decider( player.hands, hand,
                                                      rules.isSplittingAllowed( hand ) && !wasSplit,
                                                      rules.isDoubleDownAllowed( hand ), false )
                                    : Decision::Draw;

                //                std::cout << player.hands[i] <<  ": " << decision << std::endl;
                if ( splitAces )
                    decision = Decision::Stand;

                if ( decision == Decision::Split )
                {
                    //                    std::cout << "N: " << player.hands.size() << std::endl;
                    //                    std::cout << "SPLIT: " << player.hands[i] << std::endl;
                    hand.pop_back();
                    auto copy = hand;
                    const auto card = copy.front();
                    player.hands.push_back( copy );
                    player.bets.push_back( player.bets[ i ] );
                    const auto probability = computeProbabilityAfterStartingHandImpl(
                        player, dealer, deck, rules, card == Card::_A, true );
                    deck.undraw( player.hands.back().front() );
                    player.hands.pop_back();
                    player.bets.pop_back();
                    return probability;
                }

                if ( decision == Decision::DoubleDown )
                {
                    //                std::cout << "double down" << std::endl;
                    //                std::cout << dealer.hands.front().hand.values[0] << std::endl;
                    //                std::cout << handWithBet.hand << std::endl;
                    player.bets[ i ] *= 2;

                    const auto probability =
                        drawPossibleCardsAndEvaluate( hand, deck, [&player, &dealer, &deck] {
                            return computeExpectationAfterPlayer( player, dealer, deck );
                        } );
                    player.bets[ i ] = player.decider.chooseBet( deck );
                    return probability;
                }

                if ( decision == Decision::Draw )
                {
                    return drawPossibleCardsAndEvaluate( hand, deck, [&player, &dealer, &deck,
                                                                      &rules, splitAces, wasSplit] {
                        return computeProbabilityAfterStartingHandImpl( player, dealer, deck, rules,
                                                                        splitAces, wasSplit );
                    } );
                }
            }

            return computeExpectationAfterPlayer( player, dealer, deck );
        }
    }

    Expectation computeExpectationAfterStartingHand( Player& player, Player& dealer, Deck& deck,
                                                     const Rules& rules )
    {
        //        std::cout << __PRETTY_FUNCTION__ << std::endl;
        const auto playerValue = getMaxValidValue( player.hands.front() );
        const auto dealerValue = getMaxValidValue( dealer.hands.front() );

        const auto decision = player.decider( player.hands, player.hands.front(), false, false,
                                              rules.isInsuranceAllowed( player.hands.front() ) );

        Expectation expectation;
        if ( playerValue == 21 and dealerValue == 21 )
        {
            if ( decision == Decision::Insure )
            {
                expectation.win = 0.5;
                expectation.tie = 0.5;
                expectation.payout = player.bets.front();
            }
            else
            {
                expectation.tie++;
            }
            return expectation;
        }

        if ( playerValue == 21 and dealerValue != 21 )
        {
            if ( decision == Decision::Insure )
            {
                expectation.win = 0.5;
                expectation.loss = 0.5;
                expectation.payout = player.bets.front();
            }
            else
            {
                expectation.win = 1;
                expectation.payout = rules.factorForNaturals * player.bets.front();
            }
            return expectation;
        }

        if ( playerValue != 21 and dealerValue == 21 )
        {
            if ( decision == Decision::Insure )
            {
                expectation.win = 0.5;
                expectation.loss = 0.5;
            }
            else
            {
                expectation.loss = 1;
                expectation.payout = -player.bets.front();
            }
            return expectation;
        }

        return computeProbabilityAfterStartingHandImpl( player, dealer, deck, rules );
    }

    std::future< Expectation > computeExpectationAfterStartingHandAsync( Player& player,
                                                                         Player& dealer, Deck& deck,
                                                                         const Rules& rules )
    {
        return std::async( std::launch::async, [player, dealer, deck, rules]() mutable {
            return computeExpectationAfterStartingHand( player, dealer, deck, rules );
        } );
    }

    Expectation computeExpectationAfterOpenCards( Player& player, Player& dealer, Deck& deck,
                                                  const Rules& rules )
    {
        //        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return drawPossibleCardsAndEvaluate(
            dealer.hands.front(), deck, [&player, &dealer, &deck, &rules] {
                //            std::cout << "second dealer card: " << dealer.hands.front().back() <<
                //            std::endl;
                return computeExpectationAfterStartingHand( player, dealer, deck, rules );
            } );
        //        return drawPossibleCardsAndEvaluateParallel(dealer.hands.front(), deck,
        //                                                    [&player, &dealer, &deck, &rules]
        //        {
        //            return [player, dealer, deck, &rules] () mutable
        //            {
        //                return computeExpectationAfterStartingHand( player, dealer, deck, rules);
        //            };
        //        });
    }

    void allProbabilites( Player& player, Player& dealer, Deck& deck, const Rules& rules,
                          std::ostream& os )
    {
        drawPossibleCards( player.hands.front(), deck, [&]( double ) {
            //            std::cout << "first player card: " << player.hands.front().back() <<
            //            std::endl;
            drawPossibleCards( player.hands.front(), deck, [&]( double ) {
                //                std::cout << "second player card: " << player.hands.front().back()
                //                << std::endl;
                os << player.hands.front() << ": " << std::flush;
                drawPossibleCards( dealer.hands.front(), deck, [&]( double ) {
                    //                    std::cout << "first dealer card: " <<
                    //                    dealer.hands.front().back() << std::endl;
                    const auto subProbability =
                        computeExpectationAfterOpenCards( player, dealer, deck, rules );
                    os << subProbability.payout << ", " << std::flush;
                } );
                os << std::endl;
            } );
        } );
    }

    Expectation computeExpectationForFirstRound( Player& player, Player& dealer, Deck& deck,
                                                 const Rules& rules )
    {
        //        static int counter = 0;
        std::map< std::tuple< Card, Card, Card >, Expectation > cachedProbabilities;
        return DrawPossibleCardsAndEvaluate< 2 >::apply( deck, player.hands.front(), [&] {
            return drawPossibleCardsAndEvaluate( dealer.hands.front(), deck, [&] {
                const auto key = std::make_tuple(
                    min( player.hands.front().front(), player.hands.front().back() ),
                    max( player.hands.front().front(), player.hands.front().back() ),
                    dealer.hands.front().front() );
                auto iter = cachedProbabilities.find( key );
                if ( iter != end( cachedProbabilities ) )
                {
                    return iter->second;
                }

                auto p = computeExpectationAfterOpenCards( player, dealer, deck, rules );
                cachedProbabilities[ key ] = p;
                return p;
            } );
        } );
    }
}
