#ifndef PID_OUTPUT_RECEIVER
#define PID_OUTPUT_RECEIVER

#include "WPILib.h"
class PIDOutputReceiver : public PIDOutput
{
    public:
        void PIDWrite ( double output ) override;
        double GetValue();
    private:
        double value;
};

#endif