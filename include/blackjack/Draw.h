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

    template < int rounds >
    struct DrawPossibleCardsAndEvaluate
    {
        template < class F >
        static Expectation apply( Deck& deck, Hand& hand, F f )
        {
            return drawPossibleCardsAndEvaluate( hand, deck, [&] {
                return DrawPossibleCardsAndEvaluate< rounds - 1 >::apply( deck, hand, f );
            } );
        }
    };

    template <>
    struct DrawPossibleCardsAndEvaluate< 0 >
    {
        template < class F >
        static Expectation apply( Deck&, Hand&, F f )
        {
            return f();
        }
    };

    template < int rounds >
    struct DrawPossibleCards
    {
        template < class F >
        static void apply( Deck& deck, Hand& hand, F f )
        {
            drawPossibleCards( hand, deck, [&]( double p ) {
                DrawPossibleCards< rounds - 1 >::apply( deck, hand,
                                                        [p, f]( double q ) { f( p * q ); } );
            } );
        }
    };

    template <>
    struct DrawPossibleCards< 1 >
    {
        template < class F >
        static void apply( Deck& deck, Hand& hand, F f )
        {
            drawPossibleCards( hand, deck, [&]( double p ) { f( p ); } );
        }
    };
}
