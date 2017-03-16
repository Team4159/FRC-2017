#ifndef CARDINAL_DASH_STATUS_H
#define CARDINAL_DASH_STATUS_H

namespace CardinalDash
{
    class Status
    {
        public:
            static void Init();

            static bool GetEnabled();
            static int GetMode();
            static int GetAlliance();

            enum Mode {
                DISABLED = 0, TELEOP, AUTONOMOUS, TEST, INVALID
            };

            enum Alliance {
                RED = 0, BLUE, NONE
            };
        private:
    };
};

#endif // CARDINAL_DASH_STATUS_H
