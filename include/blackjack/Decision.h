#pragma once

#include <ostream>

#define DECISIONS                                                                                  \
    X( Draw )                                                                                      \
    X( Stand )                                                                                     \
    X( Split )                                                                                     \
    X( DoubleDown )                                                                                \
    X( Insure )

namespace blackjack
{
#define X( a ) a,
    enum class Decision
    {
        DECISIONS
    };
#undef X

    std::ostream& operator<<( std::ostream& os, Decision decision );
}
