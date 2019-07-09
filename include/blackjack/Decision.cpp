#include "Decision.h"

namespace blackjack
{
#define X( a )                                                                                     \
    if ( Decision::a == decision )                                                                 \
        return os << #a;
    std::ostream& operator<<( std::ostream& os, Decision decision )
    {
        DECISIONS
        return os;
    }
#undef X
}
