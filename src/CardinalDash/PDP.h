#ifndef CARDINAL_DASH_PDP_H
#define CARDINAL_DASH_PDP_H

#include "CardinalDash/Dashboard.h"

#include "WPILib.h"

namespace CardinalDash {

    class PDP {
    public:
        static void Init();
        static double GetVoltage();
        static double GetChannelCurrent(int channel);

        // This is pathetic... whatever. I have no standards anymore
        static double GetChannelCurrent0() { return GetChannelCurrent(0); };
        static double GetChannelCurrent1() { return GetChannelCurrent(1); };
        static double GetChannelCurrent2() { return GetChannelCurrent(2); };
        static double GetChannelCurrent3() { return GetChannelCurrent(3); };

        static double GetChannelCurrent4() { return GetChannelCurrent(4); };
        static double GetChannelCurrent5() { return GetChannelCurrent(5); };
        static double GetChannelCurrent6() { return GetChannelCurrent(6); };
        static double GetChannelCurrent7() { return GetChannelCurrent(7); };

        static double GetChannelCurrent8() { return GetChannelCurrent(8); };
        static double GetChannelCurrent9() { return GetChannelCurrent(9); };
        static double GetChannelCurrent10() { return GetChannelCurrent(10); };
        static double GetChannelCurrent11() { return GetChannelCurrent(11); };

        static double GetChannelCurrent12() { return GetChannelCurrent(12); };
        static double GetChannelCurrent13() { return GetChannelCurrent(13); };
        static double GetChannelCurrent14() { return GetChannelCurrent(14); };
        static double GetChannelCurrent15() { return GetChannelCurrent(15); };
    private:
        // Stop looking at my privates
        static std::unique_ptr<PowerDistributionPanel> pdp;
    };

};

#endif // CARDINAL_DASH_PDP_H
