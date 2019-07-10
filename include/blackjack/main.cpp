#include <blackjack/Card.h>
#include <blackjack/CompareStandingWithDrawing.h>
#include <blackjack/ComputeProbability.h>
#include <blackjack/Draw.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>
#include <blackjack/PointCount.h>
#include <blackjack/ZenCount.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

using blackjack::Card;
using blackjack::Decision;
using blackjack::Decider;
using blackjack::Deck;
using blackjack::Expectation;
using blackjack::Hand;
using blackjack::Result;
using blackjack::Rules;
using blackjack::Player;

enum class ChooseStrategy
{
    Basic,
    TenCount,
    PointCount,
    ZenCount
};

// void evaluateStrategyForFirstGame

Player getPlayerWithStrategy( Player& dealer, Deck& deck, ChooseStrategy chooseStrategy )
{
    const auto minBet = 1.0;
    return chooseStrategy == ChooseStrategy::Basic
               ? blackjack::getPlayer( blackjack::BasicStrategy{dealer.hands.front()},
                                       blackjack::ConstantBetSize{} )
               : chooseStrategy == ChooseStrategy::TenCount
                     ? blackjack::getPlayer(
                           blackjack::TenCountStrategy{deck, dealer.hands.front()},
                           blackjack::TenCountBettingStrategy{minBet} )
                     : chooseStrategy == ChooseStrategy::PointCount
                           ? blackjack::getPlayer(
                                 blackjack::PointCountStrategy{deck, dealer.hands.front()},
                                 blackjack::PointCountBettingStrategy{minBet} )
                           : blackjack::getPlayer(
                                 blackjack::ZenCountStrategy{deck, dealer.hands.front()},
                                 blackjack::ZenCountBettingStrategy{minBet} );
}

void evaluateStrategyForFirstGameAndDifferentDecks( ChooseStrategy chooseStrategy,
                                                    Expectation reference )
{
    Rules rules;
    //    rules.isDoubleDownAllowed = Rules::isNeverAllowed;
    rules.isSplittingAllowed = Rules::isNeverAllowed;

    const auto burnAllCards = []( Deck& deck, Card card ) {
        while ( deck.getCount( card ) > 0 )
            deck.burn( card );
    };

    blackjack::forEachCard( [chooseStrategy, reference, rules, burnAllCards]( Card card ) {
        auto deck = blackjack::create52CardDecks();
        burnAllCards( deck, card );
        auto dealer = blackjack::getDealer();
        auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

        auto expectation =
            blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
        std::cout << "Expectation for deck without " << card << ":\n" << expectation << std::endl;
        expectation.axpy( -1, reference );
        std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
    } );

    {
        auto deck = blackjack::create52CardDecks();
        burnAllCards( deck, Card::_10 );
        burnAllCards( deck, Card::_J );
        burnAllCards( deck, Card::_Q );
        burnAllCards( deck, Card::_K );
        auto dealer = blackjack::getDealer();
        auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

        auto expectation =
            blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
        std::cout << "Expectation for deck without 10, J, Q, K:\n" << expectation << std::endl;
        expectation.axpy( -1, reference );
        std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
    }

    {
        auto deck = blackjack::create52CardDecks();
        burnAllCards( deck, Card::_2 );
        burnAllCards( deck, Card::_3 );
        burnAllCards( deck, Card::_4 );
        burnAllCards( deck, Card::_5 );
        burnAllCards( deck, Card::_6 );
        burnAllCards( deck, Card::_7 );
        burnAllCards( deck, Card::_8 );
        auto dealer = blackjack::getDealer();
        auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

        auto expectation =
            blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
        std::cout << "Expectation for deck without 2,3,...,8:\n" << expectation << std::endl;
        expectation.axpy( -1, reference );
        std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
    }
}

void evaluateStrategyForFirstGameAndOneMissingCard( ChooseStrategy chooseStrategy,
                                                    Expectation reference )
{
    blackjack::forEachCard( [chooseStrategy, reference]( Card card ) {
        auto deck = blackjack::create52CardDecks();
        deck.burn( card );
        auto dealer = blackjack::getDealer();
        auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

        Rules rules;
        //    rules.isDoubleDownAllowed = Rules::isNeverAllowed;
        rules.isSplittingAllowed = Rules::isNeverAllowed;

        auto expectation =
            blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
        std::cout << "Expectation for deck without " << card << ":\n" << expectation << std::endl;
        expectation.axpy( -1, reference );
        std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
    } );
}

Expectation evaluateStrategyForFirstGame( ChooseStrategy chooseStrategy )
{
    auto deck = blackjack::createSimplified52CardDecks();
    auto dealer = blackjack::getDealer();
    auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

    Rules rules;
    rules.isDoubleDownAllowed = Rules::isAlwaysAllowed;
    rules.isSplittingAllowed = Rules::isNeverAllowed;
    rules.isInsuranceAllowed = Rules::isAlwaysAllowed;
    std::cout << "compute probabilities" << std::endl;
    //    const auto firstPlayerCard = Card::_10;
    //    const auto secondPlayerCard = Card::_A;
    //    const auto firstDealerCard = Card::_A;
    //    player.hands.front().push_back(firstPlayerCard);
    //    deck.draw(firstPlayerCard);
    //    player.hands.front().push_back(secondPlayerCard);
    //    deck.draw(secondPlayerCard);
    //    dealer.hands.front().push_back(firstDealerCard);
    //    deck.draw(firstDealerCard);
    //    const auto p = blackjack::computeProbabilityAfterOpenCards(player, dealer, deck, rules);
    //    std::cout << p << std::endl;
    //    blackjack::allProbabilites(player, dealer, deck, rules, std::cout);
    return blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
}

void compareStandingVsDrawing()
{
    Hand playerHand = {Card::_2, Card::_7, Card::_7};
    auto openDealerCard = Card::_9;
    std::cout << "player hand: " << playerHand << std::endl;
    std::cout << "open dealer card: " << openDealerCard << std::endl;
    const auto result = blackjack::compareStandingWithDrawing( playerHand, openDealerCard );
    std::cout << "standing: " << result.standing << std::endl;
    std::cout << "drawing : " << result.drawing << std::endl;
}

template < int rounds >
void computePointCountDistribution( int n )
{
    Deck deck( false );
    deck.add( Card::_2, 24 * n );
    deck.add( Card::_8, 4 * n );
    deck.add( Card::_10, 24 * n );

    std::vector< std::pair< int, double > > percentagePerRange;
    const auto insertPointCount = [&percentagePerRange]( double pointCount, double p ) {
        static auto range = 10.0;
        const auto index =
            int( std::round( pointCount / range ) + ( ( pointCount > 0 ) ? 0.1 : -0.1 ) );
        const auto iter = find_if( begin( percentagePerRange ), end( percentagePerRange ),
                                   [index]( const auto& pair ) { return pair.first == index; } );
        if ( iter != end( percentagePerRange ) )
        {
            iter->second += p;
        }
        else
        {
            percentagePerRange.emplace_back( index, p );
        }
    };

    auto maxRatio = std::numeric_limits< double >::lowest();
    auto minRatio = std::numeric_limits< double >::max();

    Hand hand;
    blackjack::DrawPossibleCards< rounds >::apply(
        deck, hand, [&hand, &deck, &insertPointCount, &maxRatio, &minRatio]( double p ) {
            const auto pointRatio =
                blackjack::computePointRatio( blackjack::computePoints( hand ), deck );
            maxRatio = std::max( maxRatio, pointRatio );
            minRatio = std::min( minRatio, pointRatio );
            insertPointCount( pointRatio, p );
        } );

    sort( begin( percentagePerRange ), end( percentagePerRange ),
          []( const auto& lhs, const auto& rhs ) { return lhs.first < rhs.first; } );

    std::cout << "max: " << maxRatio << ", min: " << minRatio << std::endl;
    std::cout << "point ratio distribution" << std::endl;
    for ( const auto& entry : percentagePerRange )
        std::cout << entry.first << ": " << entry.second << std::endl;
}

void estimatePointCountDistribution( int nDecks, int nCards )
{
    std::unordered_map< int, double > pointCountRangePercentages;
    const auto N = 500000;
    for ( auto j = 0; j < N; ++j )
    {
        auto deck = blackjack::createSimplified52CardDecks( nDecks );
        Hand hand;
        for ( auto i = 0; i < nCards; ++i )
            hand.push_back( deck.getRandomCard() );

        static const auto range = 5.0;
        const auto pointRatio =
            blackjack::computePointRatio( blackjack::computePoints( hand ), deck );
        const auto index =
            int( std::round( pointRatio / range ) + ( ( pointRatio > 0 ) ? 0.1 : -0.1 ) );
        pointCountRangePercentages[ index ] += 1.0 / N;
    }

    std::vector< std::pair< int, double > > percentagePerRange;
    transform( begin( pointCountRangePercentages ), end( pointCountRangePercentages ),
               back_inserter( percentagePerRange ), []( const auto& p ) { return p; } );

    sort( begin( percentagePerRange ), end( percentagePerRange ),
          []( const auto& lhs, const auto& rhs ) { return lhs.first < rhs.first; } );

    std::cout << "point ratio distribution" << std::endl;
    for ( const auto& entry : percentagePerRange )
        std::cout << entry.first << ": " << entry.second << std::endl;
}

void simulateGames( int nDecks, int nGames, ChooseStrategy chooseStrategy )
{
    auto deck = blackjack::create52CardDecks( nDecks );
    auto dealer = blackjack::getDealer();
    auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );
    Rules rules;
    const auto record = blackjack::playAgainstDealer( player, dealer, deck, rules, nGames );
    std::cout << record << std::endl;
    const auto payoff =
        double( record.wins - record.losses ) / ( record.wins + record.ties + record.losses );
    std::cout << "payoff: " << payoff << std::endl;
    std::cout << "final cash: " << player.decider.getCash() << std::endl;
    std::cout << "min cash: " << player.decider.getMinCash() << std::endl;
}

int main( int argc, char* argv[] )
{
    using namespace std::chrono;
    const auto start = high_resolution_clock::now();

    const auto chooseStrategy = ChooseStrategy::ZenCount;
    //        const auto reference = evaluateStrategyForFirstGame(chooseStrategy);
    //        evaluateStrategyForFirstGameAndDifferentDecks(chooseStrategy, reference);
    //        compareStandingVsDrawing();
    //        const auto reference = evaluateStrategyForFirstGame(chooseStrategy);
    //        std::cout << reference << std::endl;
    //    constexpr auto rounds = 35;
    //    const auto nDecks = 8;
    ////    computePointCountDistribution<rounds>(nDecks);
    //    estimatePointCountDistribution(nDecks, rounds);

    if ( argc < 3 )
        return 1;
    const int N = std::atoi( argv[ 1 ] );
    const int nDecks = std::atoi( argv[ 2 ] );
    std::cout << "Games: " << N << std::endl;
    simulateGames( nDecks, N, chooseStrategy );

    std::cout << "time: "
              << duration_cast< seconds >( high_resolution_clock::now() - start ).count() << " s"
              << std::endl;
    return 0;
}
