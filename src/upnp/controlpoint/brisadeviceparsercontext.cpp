#include "brisadeviceparsercontext.h"
#include "brisacontrolpointdevice.h"

using namespace BrisaUpnp;

BrisaDeviceParserContext::BrisaDeviceParserContext(
        BrisaDeviceParserContext *parent, BrisaControlPointDevice *target) :
    stateSkip(0), state(Root), parent(parent), device(target), service(0),
            icon(0) {
}
