#include "CardinalDash/VictorSP.h"

namespace CardinalDash {
    double VictorSP::getValue(void* instance)
    {
        return ((VictorSP*)instance)->Get();
    }
}
