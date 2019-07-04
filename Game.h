#pragma once

#include "Card.h"
#include "Player.h"

#include <cassert>
#include <iostream>
#include <functional>
#include <ostream>

#include <unordered_map>

namespace blackjack
{
    struct Record
    {
        Record& operator+=( const Record& other )
        {
            wins += other.wins;
            ties += other.ties;
            losses += other.losses;
            return *this;
        }

        int wins{0};
        int ties{0};
        int losses{0};
    };

    struct Rules
    {
        std::function< bool( const Hand& ) > isSplittingAllowed = []( const Hand& ) {
            return true;
        };
        std::function< bool( const Hand& ) > isDoubleDownAllowed = []( const Hand& ) {
            return true;
        };
        std::function< bool( const Hand& ) > isInsuranceAllowed = []( const Hand& ) {
            return false;
        };
    };

    struct DiscardCardsAtEndOfGame
    {
        ~DiscardCardsAtEndOfGame()
        {
            deck.discard( player.hands );

            //            std::cout << " === End Game" << std::endl;
            //            std::cout << deck << std::endl;
        }

        Player& player;
        Deck& deck;
    };

    inline std::ostream& operator<<( std::ostream& os, const Record& record )
    {
        const auto sum = record.wins + record.ties + record.losses;
        os << "wins  : " << record.wins << " (" << ( double( record.wins ) / sum ) << ") -> ("
           << ( double( record.wins + record.ties / 2 ) / sum ) << ")"
           << "\nties  : " << record.ties << " (" << ( double( record.ties ) / sum ) << ")"
           << "\nlosses: " << record.losses << " (" << ( double( record.losses ) / sum ) << ") -> ("
           << ( double( record.losses + record.ties / 2 ) / sum ) << ")"
           << "\nspread: " << ( double( record.wins - record.losses ) / sum )
           << "\noverall: " << sum << std::endl;
        return os;
    }

    inline void draw( Hand& hand, Deck& deck )
    {
        const auto card = deck.getRandomValue();
        hand.push_back( card );
    }

    static std::unordered_map< double, int > wins, ties, losses;

    inline Record playDealerAfterStartingHand( Deck& deck, Player& player, Player& dealer )
    {
        auto decision = dealer.decider( dealer.hands, dealer.hands.front() );
        while ( decision == Decision::Draw )
        {
            draw( dealer.hands.front(), deck );
            decision = dealer.decider( dealer.hands, dealer.hands.front() );
        }

        Record record;
        //        std::cout << "Hands: " << player.hands.size() << std::endl;
        for ( auto i = 0u; i < player.hands.size(); ++i )
        {

            std::cout << "bet: " << player.bets[ i ] << std::endl;
            std::cout << "final player hand: " << std::endl;
            std::cout << player.hands[ i ] << std::endl;
            std::cout << "final dealer hand: " << std::endl;
            std::cout << dealer.hands.front() << std::endl;
            const auto maxPlayerValue = getMaxValidValue( player.hands[ i ] );
            const auto maxDealerValue = getMaxValidValue( dealer.hands.front() );
            if ( maxPlayerValue == -1 )
            {
                record.losses++;
                player.decider.removeCash( player.bets[ i ] );
                losses[ player.bets[ i ] ]++;
                continue;
            }
            if ( maxPlayerValue > maxDealerValue )
            {
                record.wins++;
                player.decider.addCash( player.bets[ i ] );
                wins[ player.bets[ i ] ]++;
                continue;
            }
            if ( maxPlayerValue == maxDealerValue )
            {
                record.ties++;
                ties[ player.bets[ i ] ]++;
                //                std::cout << "draw" << std::endl;
                continue;
            }

            record.losses++;
            player.decider.removeCash( player.bets[ i ] );
            losses[ player.bets[ i ] ]++;
        }

        return record;
    }

    inline Record playAfterStartingHand( Deck& deck, Player& player, Player& dealer,
                                         bool allowSplitting = true, bool splitAces = false )
    {
        for ( auto i = 0u; i < player.hands.size(); ++i )
        {
            auto decision = player.decider( player.hands, player.hands[ i ], allowSplitting );
            if ( splitAces )
                decision = Decision::Stand;

            if ( decision == Decision::Split )
            {
                std::cout << " -> SPLIT" << std::endl;
                std::cout << dealer.hands.front()[ 0 ] << std::endl;
                std::cout << player.hands[ i ] << std::endl;
                player.hands[ i ].pop_back();
                auto copy = player.hands[ i ];
                const auto card = copy.front();
                player.hands[ i ].push_back( deck.getRandomValue() );
                copy.push_back( deck.getRandomValue() );
                player.hands.push_back( copy );
                player.bets.push_back( player.bets[ i ] );
                return playAfterStartingHand( deck, player, dealer, false, card == Card::_A );
            }

            if ( decision == Decision::DoubleDown )
            {
                //                std::cout << "double down" << std::endl;
                //                std::cout << dealer.hands.front().hand.values[0] << std::endl;
                //                std::cout << handWithBet.hand << std::endl;
                player.bets[ i ] *= 2;
                draw( player.hands[ i ], deck );
                decision = Decision::Stand;
            }

            while ( decision == Decision::Draw )
            {
                draw( player.hands[ i ], deck );
                decision = player.decider( player.hands, player.hands[ i ], allowSplitting );
            }
        }

        return playDealerAfterStartingHand( deck, player, dealer );
    }

    inline Record playAgainstDealer( Player& player, Player& dealer, Deck& deck )
    {
        std::cout << "\n === New Game" << std::endl;
        static int counter = 0;
        ++counter;
        if ( deck.size() < 8 /*|| counter == 3*/ )
        {
            std::cout << "RESHUFFLE" << std::endl;
            deck.reshuffle();
            //            std::cout << deck << std::endl;
            counter = 1;
        }

        player.hands = {Hand{}};
        player.bets = {player.decider.chooseBet( deck )};
        dealer.hands.front() = Hand{};
        DiscardCardsAtEndOfGame playerDiscard{player, deck};
        DiscardCardsAtEndOfGame dealerDiscard{dealer, deck};
        player.hands.front().push_back( deck.getRandomValue() );
        player.hands.front().push_back( deck.getRandomValue() );
        dealer.hands.front().push_back( deck.getRandomValue() );
        dealer.hands.front().push_back( deck.getRandomValue() );
        std::cout << "initial player hand: " << std::endl;
        std::cout << player.hands.front() << std::endl;
        std::cout << "initial dealer hand: " << std::endl;
        std::cout << dealer.hands.front() << std::endl;

        const auto playerValue = getMaxValidValue( player.hands.front() );
        const auto dealerValue = getMaxValidValue( dealer.hands.front() );

        Record record;
        if ( playerValue == 21 and dealerValue == 21 )
        {
            record.ties++;
            ties[ player.bets.front() ]++;
            //            std::cout << "draw" << std::endl;
            return record;
        }

        if ( playerValue == 21 and dealerValue != 21 )
        {
            record.wins++;
            player.decider.addCash( 1.5 * player.bets.front() );
            wins[ 1.5 * player.bets.front() ]++;
            return record;
        }

        if ( playerValue != 21 and dealerValue == 21 )
        {
            record.losses++;
            player.decider.removeCash( player.bets.front() );
            losses[ player.bets.front() ]++;
            return record;
        }

        const auto result = playAfterStartingHand( deck, player, dealer );
        return result;
    }

    template < class Map, class Cond >
    int count( const Map& m, double bet, Cond cond )
    {
        return accumulate( begin( m ), end( m ), 0, [bet, cond]( int sum, auto& e ) {
            return sum + ( cond( e.first, bet ) ? e.second : 0 );
        } );
    }

    template < class Cond >
    double percentage( const std::unordered_map< double, int >& m, double bet, Cond cond )
    {
        const auto winCount = count( wins, bet, cond );
        const auto tieCount = count( ties, bet, cond );
        const auto lossCount = count( losses, bet, cond );
        const auto mCount = count( m, bet, cond );

        return double( mCount ) / ( winCount + tieCount + lossCount );
    }

    template < class CondNormal, class CondDouble, class CondBlackJack >
    double getEarnings( CondNormal cNormal, CondDouble cDouble, CondBlackJack cBlackjack,
                        double bet )
    {
        return bet *
               ( count( wins, bet, cNormal ) - count( losses, bet, cNormal ) +
                 2 * ( count( wins, bet, cDouble ) - count( losses, bet, cDouble ) ) +
                 1.5 * ( count( wins, bet, cBlackjack ) - count( losses, bet, cBlackjack ) ) );
    }

    inline bool same( double a, double b )
    {
        return std::abs( a - b ) / std::max( std::abs( a ), std::abs( b ) ) <
               10 * std::numeric_limits< double >::epsilon();
    }

    inline void printPLStats()
    {
        std::cout << "earnings distribution" << std::endl;
        for ( const auto& p : wins )
            std::cout << p.first << ":\t" << p.second << std::endl;

        std::cout << "losses distribution" << std::endl;
        for ( const auto& p : losses )
            std::cout << p.first << ":\t" << p.second << std::endl;

        const auto cond = []( double bet, double baseBet ) {
            return same( bet, baseBet ) || same( bet, baseBet * 2 ) || same( bet, 1.5 * baseBet );
        };

        const auto doubleDownCond = []( double bet, double baseBet ) {
            return same( bet, baseBet * 2 );
        };

        const auto normalCond = []( double bet, double baseBet ) { return same( bet, baseBet ); };

        const auto blackjackCond = []( double bet, double baseBet ) {
            return same( bet, 1.5 * baseBet );
        };

        std::cout << "\nresults per bet size" << std::endl;
        std::cout << "bet, % wins, %ties, % losses, % dd wins, % dd ties, % dd losses, %bj wins, "
                     "%bj ties, %bj losses"
                  << std::endl;
        auto printStats = [&]( double bet ) {
            std::cout << "  " << bet << ": " << percentage( wins, bet, cond ) << ", "
                      << percentage( ties, bet, cond ) << ", " << percentage( losses, bet, cond )
                      << ", " << percentage( wins, bet, doubleDownCond ) << ", "
                      << percentage( ties, bet, doubleDownCond ) << ", "
                      << percentage( losses, bet, doubleDownCond ) << ": "
                      << getEarnings( normalCond, doubleDownCond, blackjackCond, bet ) << std::endl;
        };
        std::vector< double > bets = {1, 12.5};
        for ( auto bet : bets )
            printStats( bet );
    }

    inline Record playAgainstDealer( Player& player, Player& dealer, Deck& deck, int numberOfGames )
    {
        wins.clear();
        losses.clear();
        Record record;
        for ( auto i = 0; i < numberOfGames; ++i )
            record += playAgainstDealer( player, dealer, deck );

        std::cout << "final deck" << std::endl;
        std::cout << deck << std::endl;
        printPLStats();
        return record;
    }
}
