#include "CardinalDash/VictorSP.h"

namespace CardinalDash {
    VictorSP::VictorSP(int port) : frc::VictorSP(port) {
        std::string name = "VictorSP ";
        name += std::to_string(port);

        Dashboard::Subscribe(name, &getValue, this);
    };

    double VictorSP::getValue(void* instance)
    {
        return ((VictorSP*)instance)->Get();
    }
}
