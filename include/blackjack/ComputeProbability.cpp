#include "ComputeProbability.h"

#include <blackjack/Card.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

#include <cassert>
#include <iostream>

namespace blackjack
{

    std::ostream& operator<<( std::ostream& os, const Probability& probability )
    {
        return os << "win: " << probability.win << ", tie: " << probability.tie
                  << ", loss: " << probability.loss
                  << ", expected payout: " << probability.expectedPayout;
    }

    namespace
    {
        void draw( Hand& hand, Deck& deck, Card& card )
        {
            deck.draw( card );
            hand.push_back( card );
        }

        struct DiscardLastCard
        {
            ~DiscardLastCard()
            {
                deck.undraw( hand.back() );
                hand.pop_back();
            }

            Hand& hand;
            Deck& deck;
        };

        template < class F >
        Probability drawPossibleCardsAndEvaluate( Hand& hand, Deck& deck, F f )
        {
            Probability probability;
            for ( auto card : deck.getCardTypes() )
            {
                const auto count = deck.getCount( card );
                if ( count == 0 )
                    continue;

                const auto p = double( count ) / deck.size();
                draw( hand, deck, card );
                DiscardLastCard discard{hand, deck};
                const auto subProbability = f();
                probability.axpy( p, subProbability );
            }
            return probability;
        }
    }

    Probability computeProbabilityAfterPlayer( Player& player, Player& dealer, Deck& deck,
                                               bool firstCall )
    {
        assert( player.hands.size() <= 2 );
        Probability probability;
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
                    probability.expectedPayout -= p * player.bets[ i ];
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
                    return computeProbabilityAfterPlayer( player, dealer, deck, false );
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
                probability.expectedPayout += p * player.bets[ i ];
                continue;
            }
            if ( maxPlayerValue == maxDealerValue )
            {
                probability.tie += p;
                continue;
            }

            probability.loss += p;
            probability.expectedPayout -= p * player.bets[ i ];
        }

        return probability;
    }

    namespace
    {
        Probability computeProbabilityAfterStartingHandImpl( Player& player, Player& dealer,
                                                             Deck& deck, const Rules& rules,
                                                             bool splitAces = false )
        {
            for ( auto i = 0u; i < player.hands.size(); ++i )
            {
                auto decision =
                    player.hands[ i ].size() > 1
                        ? player.decider( player.hands, player.hands[ i ],
                                          rules.isSplittingAllowed( player.hands[ i ] ) &&
                                              !splitAces )
                        : Decision::Draw;

                if ( splitAces )
                    decision = Decision::Stand;

                if ( decision == Decision::Split )
                {
                    player.hands[ i ].pop_back();
                    auto copy = player.hands[ i ];
                    const auto card = copy.front();
                    player.hands.push_back( copy );
                    player.bets.push_back( player.bets[ i ] );
                    return computeProbabilityAfterStartingHandImpl( player, dealer, deck, rules,
                                                                    card == Card::_A );
                }

                if ( decision == Decision::DoubleDown )
                {
                    //                std::cout << "double down" << std::endl;
                    //                std::cout << dealer.hands.front().hand.values[0] << std::endl;
                    //                std::cout << handWithBet.hand << std::endl;
                    player.bets[ i ] *= 2;

                    return drawPossibleCardsAndEvaluate(
                        player.hands[ i ], deck, [&player, &dealer, &deck] {
                            return computeProbabilityAfterPlayer( player, dealer, deck );
                        } );
                    //                    Probability probability;
                    //                    for(auto card : deck.getCardTypes())
                    //                    {
                    //                        const auto count = deck.getCount(card);
                    //                        if(count == 0)
                    //                            continue;

                    //                        const auto p = double(count)/deck.size();
                    //                        draw(player.hands[i], deck, card);
                    //                        DiscardLastCard discard(player.hands[i], deck);
                    //                        const auto subProbability =
                    //                        playDealerAfterStartingHand(player, dealer, deck);
                    //                        probability.axpy(p, subProbability);
                    //                    }
                }

                if ( decision == Decision::Draw )
                {
                    return drawPossibleCardsAndEvaluate(
                        player.hands[ i ], deck, [&player, &dealer, &deck, &rules] {
                            return computeProbabilityAfterStartingHandImpl( player, dealer, deck,
                                                                            rules );
                        } );
                }
            }

            return computeProbabilityAfterPlayer( player, dealer, deck );
        }
    }

    Probability::Probability( double win, double tie, double loss, double expectedPayout )
        : win( win ), tie( tie ), loss( loss ), expectedPayout( expectedPayout )
    {
    }

    Probability& Probability::axpy( double a, const Probability& other )
    {
        win += a * other.win;
        tie += a * other.tie;
        loss += a * other.loss;
        expectedPayout += a * other.expectedPayout;
        return *this;
    }

    Probability computeProbabilityAfterStartingHand( Player& player, Player& dealer, Deck& deck,
                                                     const Rules& rules )
    {
        const auto playerValue = getMaxValidValue( player.hands.front() );
        const auto dealerValue = getMaxValidValue( dealer.hands.front() );

        Probability probability;
        if ( playerValue == 21 and dealerValue == 21 )
        {
            probability.tie++;
            return probability;
        }

        if ( playerValue == 21 and dealerValue != 21 )
        {
            probability.win++;
            probability.expectedPayout = 1.5 * player.bets.front();
            return probability;
        }

        if ( playerValue != 21 and dealerValue == 21 )
        {
            probability.loss++;
            probability.expectedPayout = -player.bets.front();
            return probability;
        }

        return computeProbabilityAfterStartingHandImpl( player, dealer, deck, rules );
    }

    Probability computeProbabilityAfterOpenCards( Player& player, Player& dealer, Deck& deck,
                                                  const Rules& rules )
    {
        return drawPossibleCardsAndEvaluate(
            dealer.hands.front(), deck, [&player, &dealer, &deck, &rules] {
                return computeProbabilityAfterStartingHand( player, dealer, deck, rules );
            } );
    }
}
