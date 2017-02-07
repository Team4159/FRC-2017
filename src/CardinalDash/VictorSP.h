#ifndef CARDINAL_DASH_VICTORSP_H
#define CARDINAL_DASH_VICTORSP_H

#include <VictorSP.h>

#include "CardinalDash/Dashboard.h"

namespace CardinalDash
{

    class VictorSP : public frc::VictorSP
    {
        public:
            VictorSP ( int port );
            static double getValue ( void* instance );
        private:

    };

};

#endif // CARDINAL_DASH_VICTORSP_H
