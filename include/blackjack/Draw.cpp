#include "Draw.h"

namespace blackjack
{
    UndrawLastCard::~UndrawLastCard()
    {
        if ( !hand.empty() )
        {
            deck.undraw( hand.back() );
            hand.pop_back();
        }
    }
}
