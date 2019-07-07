#pragma once

#include <blackjack/Card.h>
#include <blackjack/Expectation.h>

#include <vector>
#include <future>

namespace blackjack
{
    struct UndrawLastCard
    {
        ~UndrawLastCard();

        Hand& hand;
        Deck& deck;
    };

    template < class F >
    void drawPossibleCards( Hand& hand, Deck& deck, F f )
    {
        for ( auto card : deck.getCardTypes() )
        {
            const auto count = deck.getCount( card );
            if ( count == 0 )
                continue;

            const auto p = deck.getRatio( card );
            hand.push_back( deck.draw( card ) );
            UndrawLastCard discard{hand, deck};
            f( p );
        }
    }

    template < class F >
    Expectation drawPossibleCardsAndEvaluate( Hand& hand, Deck& deck, F f )
    {
        Expectation probability;
        drawPossibleCards( hand, deck,
                           [f, &probability]( double p ) { probability.axpy( p, f() ); } );
        return probability;
    }

    template < class F >
    Expectation drawPossibleCardsAndEvaluateParallel( Hand& hand, Deck& deck, F f )
    {
        std::vector< std::pair< double, std::future< Expectation > > > probabilities;
        drawPossibleCards( hand, deck, [f, &probabilities]( double p ) {
            probabilities.emplace_back( p, std::async( std::launch::async, f() ) );
        } );
        Expectation probability;
        for ( auto& p : probabilities )
            probability.axpy( p.first, p.second.get() );
        return probability;
    }
}
