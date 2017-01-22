#ifndef CARDINAL_DASH_VICTORSP_H
#define CARDINAL_DASH_VICTORSP_H

#include <VictorSP.h>

#include "CardinalDash/Dashboard.h"

namespace CardinalDash {

    class VictorSP : public frc::VictorSP {
    public:
        explicit VictorSP(int port) : frc::VictorSP(port) {
            std::string name = "VictorSP ";
            name += std::to_string(port);

            Dashboard::Subscribe(name, &getValue, this);
        };
        static double getValue(void* instance);
    private:

    };

};

#endif // CARDINAL_DASH_VICTORSP_H
