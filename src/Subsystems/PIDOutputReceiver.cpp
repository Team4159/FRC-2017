#include "PIDOutputReceiver.h"
void PIDOutputReceiver::PIDWrite ( double output )
{
    value = output;
}

double PIDOutputReceiver::GetValue()
{
    return value;
}