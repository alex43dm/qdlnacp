#ifndef AVTRANSPORT_H
#define AVTRANSPORT_H

#include "device.h"

class AVTransport : public Device
{
    public:
        AVTransport(const Upnp_Discovery* d);
        ~AVTransport();
        bool GetCurrentTransportActions();
    protected:
    private:
};

#endif // AVTRANSPORT_H
