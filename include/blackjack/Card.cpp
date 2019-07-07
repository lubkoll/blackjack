#include "Card.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <ostream>

#define likely( x ) __builtin_expect( !!( x ), 1 )

namespace blackjack
{

#define X( key, value, index )                                                                     \
    if ( Card::_##key == card )                                                                    \
        return os << #key;
    std::ostream& operator<<( std::ostream& os, Card card )
    {
        CARDS;
        return os;
    }
#undef X

#define X( key, value, index )                                                                     \
    case Card::_##key:                                                                             \
        return value;
    int getValue( Card card )
    {
        switch ( card )
        {
            CARDS
        }
        return -1;
    }
#undef X

#define X( key, value, index )                                                                     \
    case Card::_##key:                                                                             \
        return index;
    int getIndex( Card card )
    {
        switch ( card )
        {
            CARDS
        }
        return -1;
    }
#undef X

    Card min( Card lhs, Card rhs )
    {
        return ( static_cast< int >( lhs ) < static_cast< int >( rhs ) ) ? lhs : rhs;
    }

    Card max( Card lhs, Card rhs )
    {
        return ( static_cast< int >( lhs ) > static_cast< int >( rhs ) ) ? lhs : rhs;
    }

    int getMinValue( Card lhs, Card rhs )
    {
        return getValue( min( lhs, rhs ) );
    }

    int getMaxValue( Card lhs, Card rhs )
    {
        return getValue( max( lhs, rhs ) );
    }

    std::ostream& operator<<( std::ostream& os, const Hand& hand )
    {
        for ( auto value : hand )
            os << value << " ";
        return os;
    }

    bool isPair( const Hand& hand )
    {
        return hand.size() == 2 and hand[ 0 ] == hand[ 1 ];
    }

    int getValue( const Hand& hand )
    {
        return accumulate( begin( hand ), end( hand ), 0,
                           []( int sum, Card card ) { return sum + getValue( card ); } );
    }

    int getNumberOf( const Hand& hand, Card c )
    {
        return count_if( begin( hand ), end( hand ), [c]( auto card ) { return card == c; } );
    }

    int getNumberOf( const Hand& hand, int value )
    {
        return count_if( begin( hand ), end( hand ),
                         [value]( auto card ) { return getValue( card ) == value; } );
    }

    int getNumberOfExcept( const Hand& hand, Card c )
    {
        return count_if( begin( hand ), end( hand ), [c]( auto card ) { return card != c; } );
    }

    int getNumberOfExcept( const Hand& hand, int value )
    {
        return count_if( begin( hand ), end( hand ),
                         [value]( auto card ) { return getValue( card ) != value; } );
    }

    int getMaxValidValue( int value, int acesCount )
    {
        if ( value <= 21 )
            return value;

        const auto minOffset = ( value - 12 ) / 10;
        if ( minOffset > acesCount )
            return -1;

        value -= minOffset * 10;

        return value;
    }

    int getMaxValidValue( const Hand& hand )
    {
        return getMaxValidValue( getValue( hand ), getNumberOf( hand, Card::_A ) );
    }

    bool isSoft( const Hand& hand )
    {
        return ( getValue( hand ) - getMaxValidValue( hand ) -
                 10 * getNumberOf( hand, Card::_A ) ) < 0;
    }

    bool isBust( const Hand& hand )
    {
        return getMaxValidValue( hand ) == -1;
    }

    Deck::Deck( bool useFastGetIndex ) noexcept : useFastGetIndex( useFastGetIndex )
    {
    }

    Card Deck::getRandomCard()
    {
        using clock = std::chrono::system_clock;

        static auto seed = clock::from_time_t( std::time( nullptr ) ).time_since_epoch().count();
        static std::minstd_rand engine( seed );
        std::discrete_distribution< int > distribution{begin( counts ), end( counts )};

        const auto card = cards[ distribution( engine ) ];
        std::cout << "drawing " << card << std::endl;
        draw( card );
        return card;
    }

    void Deck::add( Card card, int count )
    {
        const auto index = getIndex( card );
        if ( index < counts.size() )
        {
            counts[ index ] += count;
            fullCount[ index ] += count;
            return;
        }

        cards.push_back( card );
        counts.push_back( count );
        fullCount.push_back( count );
        usedCount.push_back( 0 );
        initialSize += count;
        nCards += count;
    }

    Card Deck::draw( Card card, int count )
    {
        counts[ getIndex( card ) ] -= count;
        nCards -= count;
        if ( size() == 0 )
            reshuffle();
        return card;
    }

    void Deck::undraw( Card card, int count )
    {
        counts[ getIndex( card ) ] += count;
        nCards += count;
    }

    void Deck::discard( const std::vector< Hand >& hands )
    {
        for ( const auto& hand : hands )
        {
            for ( auto card : hand )
            {
                discard( card );
            }
        }
    }

    void Deck::discard( Card card )
    {
        usedCount[ getIndex( card ) ]++;
    }

    void Deck::burn( Card card )
    {
        discard( draw( card ) );
    }

    int Deck::size() const
    {
        return nCards;
    }

    int Deck::getCount( Card card ) const
    {
        return counts[ getIndex( card ) ];
    }

    int Deck::getCount( int value ) const
    {
        return accumulate( begin( cards ), end( cards ), 0, [value, this]( int sum, Card card ) {
            return sum + ( getValue( card ) == value ? getCount( card ) : 0 );
        } );
    }

    int Deck::getCountExcept( Card card ) const
    {
        return nCards - getCount( card );
    }

    int Deck::getCountExcept( int value ) const
    {
        return accumulate( begin( cards ), end( cards ), 0, [value, this]( int sum, Card card ) {
            return sum + ( getValue( card ) != value ? getCount( card ) : 0 );
        } );
    }

    int Deck::getFullCount( Card card ) const
    {
        return fullCount[ getIndex( card ) ];
    }

    int Deck::getFullCount( int value ) const
    {
        return accumulate( begin( cards ), end( cards ), 0, [value, this]( int sum, Card card ) {
            return sum + ( getValue( card ) == value ? getFullCount( card ) : 0 );
        } );
    }

    int Deck::getUsedCount( Card card ) const
    {
        return usedCount[ getIndex( card ) ];
    }

    int Deck::getUsedCount( int value ) const
    {
        return accumulate( begin( cards ), end( cards ), 0, [value, this]( int sum, Card card ) {
            return sum + ( getValue( card ) == value ? getUsedCount( card ) : 0 );
        } );
    }

    int Deck::getUsedCountExcept( Card card ) const
    {
        const auto offset = -getUsedCount( card );
        return accumulate( begin( usedCount ), end( usedCount ), offset );
    }

    int Deck::getUsedCountExcept( int value ) const
    {
        const auto offset = -getUsedCount( value );
        return accumulate( begin( usedCount ), end( usedCount ), offset );
    }

    int Deck::getInitialSize() const
    {
        return initialSize;
    }

    double Deck::getRatio( Card card ) const
    {
        return double( getCount( card ) ) / size();
    }

    const Hand& Deck::getCardTypes() const
    {
        return cards;
    }

    void Deck::reshuffle()
    {
        for ( auto i = 0u; i < counts.size(); ++i )
        {
            counts[ i ] += usedCount[ i ];
            usedCount[ i ] = 0;
        }
        nCards = initialSize;
        //            std::cout << "after reset: " << size() << " vs. " << getInitialSize() <<
        //            std::endl;
    }

    int Deck::getIndex( Card card ) const
    {
        if ( likely( useFastGetIndex ) )
            return blackjack::getIndex( card );

        return distance( begin( cards ), find_if( begin( cards ), end( cards ),
                                                  [card]( Card c ) { return c == card; } ) );
    }

    namespace
    {
        Deck create52CardDecks( int n )
        {
            assert( n > 0 );
            Deck deck;
            const auto cardCount = 4 * n;
            deck.add( Card::_2, cardCount );
            deck.add( Card::_3, cardCount );
            deck.add( Card::_4, cardCount );
            deck.add( Card::_5, cardCount );
            deck.add( Card::_6, cardCount );
            deck.add( Card::_7, cardCount );
            deck.add( Card::_8, cardCount );
            deck.add( Card::_9, cardCount );
            deck.add( Card::_10, cardCount );
            deck.add( Card::_J, cardCount );
            deck.add( Card::_Q, cardCount );
            deck.add( Card::_K, cardCount );
            deck.add( Card::_A, cardCount );
            return deck;
        }
    }

    Deck create52CardDeck()
    {
        return create52CardDecks( 1 );
    }

    std::ostream& operator<<( std::ostream& os, const Deck& deck )
    {
        auto ratioSum = 0.0;
        for ( auto card : deck.getCardTypes() )
        {
            ratioSum += deck.getRatio( card );
            os << card << ": " << deck.getCount( card ) << ", " << deck.getUsedCount( card )
               << " -> " << deck.getRatio( card ) << std::endl;
        }
        os << "sum: " << ratioSum << std::endl;
        return os;
    }
}

#undef likely
