#include <blackjack/Card.h>
#include <blackjack/CompareStandingWithDrawing.h>
#include <blackjack/ComputeProbability.h>
#include <blackjack/Game.h>
#include <blackjack/Player.h>

#include <iostream>

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
    PointCount
};

// void evaluateStrategyForFirstGame

Player getPlayerWithStrategy( Player& dealer, Deck& deck, ChooseStrategy chooseStrategy )
{
    return chooseStrategy == ChooseStrategy::Basic
               ? blackjack::getPlayer( blackjack::BasicStrategy{dealer.hands.front()},
                                       blackjack::ConstantBetSize{} )
               : chooseStrategy == ChooseStrategy::TenCount
                     ? blackjack::getPlayer(
                           blackjack::TenCountStrategy{deck, dealer.hands.front()},
                           blackjack::ConstantBetSize{} )
                     : blackjack::getPlayer(
                           blackjack::PointCountStrategy{deck, dealer.hands.front()},
                           blackjack::ConstantBetSize{} );
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
        auto deck = blackjack::create52CardDeck();
        burnAllCards( deck, card );
        auto dealer = blackjack::getDealer();
        auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

        auto expectation =
            blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
        std::cout << "Expectation for deck without " << card << ":\n" << expectation << std::endl;
        expectation.axpy( -1, reference );
        std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
    } );

    auto deck = blackjack::create52CardDeck();
    burnAllCards( deck, Card::_10 );
    burnAllCards( deck, Card::_J );
    burnAllCards( deck, Card::_Q );
    burnAllCards( deck, Card::_K );
    auto dealer = blackjack::getDealer();
    auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

    auto expectation = blackjack::computeExpectationForFirstRound( player, dealer, deck, rules );
    std::cout << "Expectation for deck without 10, J, Q, K:\n" << expectation << std::endl;
    expectation.axpy( -1, reference );
    std::cout << "Difference to reference:\n" << expectation << "\n" << std::endl;
}

void evaluateStrategyForFirstGameAndOneMissingCard( ChooseStrategy chooseStrategy,
                                                    Expectation reference )
{
    blackjack::forEachCard( [chooseStrategy, reference]( Card card ) {
        auto deck = blackjack::create52CardDeck();
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
    auto deck = blackjack::create52CardDeck();
    auto dealer = blackjack::getDealer();
    auto player = getPlayerWithStrategy( dealer, deck, chooseStrategy );

    Rules rules;
    //    rules.isDoubleDownAllowed = Rules::isNeverAllowed;
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
    Hand playerHand = {Card::_10, Card::_5, Card::_A};
    auto openDealerCard = Card::_10;
    std::cout << "player hand: " << playerHand << std::endl;
    std::cout << "open dealer card: " << openDealerCard << std::endl;
    const auto result = blackjack::compareStandingWithDrawing( playerHand, openDealerCard );
    std::cout << "standing: " << result.standing << std::endl;
    std::cout << "drawing : " << result.drawing << std::endl;
}

int main( int argc, char* argv[] )
{
    using namespace std::chrono;
    const auto start = high_resolution_clock::now();

    //    const auto chooseStrategy = ChooseStrategy::Basic;
    //    const auto reference = evaluateStrategyForFirstGame(chooseStrategy);
    //    evaluateStrategyForFirstGameAndOneMissingCard(chooseStrategy, reference);
    //    compareStandingVsDrawing();
    //    const auto reference = evaluateStrategyForFirstGame(ChooseStrategy::PointCount);
    //    std::cout << reference << std::endl;

    if ( argc < 2 )
        return 1;
    const int N = std::atoi( argv[ 1 ] );
    std::cout << "Games: " << N << std::endl;

    auto deck = blackjack::create52CardDeck();
    auto dealer = blackjack::getDealer();
    Player player = blackjack::getPlayer( /*blackjack::BasicStrategy{dealer.hands.front().hand},*/
                                          blackjack::PointCountStrategy{deck, dealer.hands.front()},
                                          blackjack::PointCountBettingStrategy{1} );
    //    Player player =
    //        blackjack::getPlayer( /*blackjack::BasicStrategy{dealer.hands.front().hand},*/
    //                              blackjack::TenCountStrategy{deck, dealer.hands.front()},
    //                              blackjack::TenCountBettingStrategy{1, 1, 12.5, 12.5, 12.5} );
    Rules rules;
    rules.isSplittingAllowed = Rules::isAlwaysAllowed;
    const auto record = blackjack::playAgainstDealer( player, dealer, deck, rules, N );
    std::cout << record << std::endl;
    const auto payoff =
        double( record.wins - record.losses ) / ( record.wins + record.ties + record.losses );
    std::cout << "payoff: " << payoff << std::endl;
    std::cout << "final cash: " << player.decider.getCash() << std::endl;
    std::cout << "min cash: " << player.decider.getMinCash() << std::endl;

    std::cout << "time: "
              << duration_cast< seconds >( high_resolution_clock::now() - start ).count() << " s"
              << std::endl;
    return 0;
}
