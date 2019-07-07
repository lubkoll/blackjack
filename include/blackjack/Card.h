#pragma once

#include <chrono>
#include <random>
#include <vector>
#include <ostream>

#define CARDS                                                                                      \
    X( 2, 2, 0 )                                                                                   \
    X( 3, 3, 1 )                                                                                   \
    X( 4, 4, 2 )                                                                                   \
    X( 5, 5, 3 )                                                                                   \
    X( 6, 6, 4 )                                                                                   \
    X( 7, 7, 5 )                                                                                   \
    X( 8, 8, 6 )                                                                                   \
    X( 9, 9, 7 )                                                                                   \
    X( 10, 10, 8 )                                                                                 \
    X( J, 10, 9 )                                                                                  \
    X( Q, 10, 10 )                                                                                 \
    X( K, 10, 11 )                                                                                 \
    X( A, 11, 12 )

namespace blackjack
{
#define X( key, value, index ) _##key,
    enum class Card
    {
        CARDS
    };
#undef X

    std::ostream& operator<<( std::ostream& os, Card card );

#define X( key, value, index ) f( Card::_##key );
    template < class F >
    void forEachCard( F f )
    {
        CARDS
    }
#undef X

    int getValue( Card card );

    int getIndex( Card card );

    Card min( Card lhs, Card rhs );

    Card max( Card lhs, Card rhs );

    int getMinValue( Card lhs, Card rhs );

    int getMaxValue( Card lhs, Card rhs );

    using Hand = std::vector< Card >;

    std::ostream& operator<<( std::ostream& os, const Hand& hand );

    bool isPair( const Hand& hand );

    int getValue( const Hand& hand );

    int getNumberOf( const Hand& hand, Card c );

    int getNumberOf( const Hand& hand, int value );

    int getNumberOfExcept( const Hand& hand, Card c );

    int getNumberOfExcept( const Hand& hand, int value );

    int getMaxValidValue( int value, int acesCount );

    int getMaxValidValue( const Hand& hand );

    bool isSoft( const Hand& hand );

    bool isBust( const Hand& hand );

    template < class Index >
    Index getRandomIndex( Index high )
    {
        using clock = std::chrono::system_clock;

        static auto seed = clock::from_time_t( std::time( nullptr ) ).time_since_epoch().count();
        static std::minstd_rand engine( seed );
        static std::uniform_int_distribution< Index > distribution{};

        return distribution(
            engine, typename std::uniform_int_distribution< Index >::param_type( Index{0}, high ) );
    }

    class Deck
    {
    public:
        explicit Deck( bool useFastGetIndex = true ) noexcept;

        Card getRandomCard();

        void add( Card card, int count = 1 );

        Card draw( Card card, int count = 1 );

        void undraw( Card card, int count = 1 );

        void discard( const std::vector< Hand >& hands );

        void discard( Card card );

        void burn( Card card );

        int size() const;

        int getCount( Card card ) const;

        int getCount( int value ) const;

        int getCountExcept( Card card ) const;

        int getCountExcept( int value ) const;

        int getFullCount( Card card ) const;

        int getFullCount( int value ) const;

        int getUsedCount( Card card ) const;

        int getUsedCount( int value ) const;

        int getUsedCountExcept( Card card ) const;

        int getUsedCountExcept( int value ) const;

        int getInitialSize() const;

        double getRatio( Card card ) const;

        const Hand& getCardTypes() const;

        void reshuffle();

    private:
        int getIndex( Card card ) const;

        Hand cards;
        std::vector< int > counts;
        std::vector< int > usedCount;
        std::vector< int > fullCount;
        int initialSize = 0;
        int nCards = initialSize;
        const bool useFastGetIndex;
    };

    Deck create52CardDeck();

    std::ostream& operator<<( std::ostream& os, const Deck& deck );
}
