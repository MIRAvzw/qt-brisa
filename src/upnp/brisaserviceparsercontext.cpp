#include "brisaserviceparsercontext.h"

using namespace BrisaUpnp;

BrisaServiceParserContext::BrisaServiceParserContext(BrisaServiceParserContext *parent,
                           BrisaAbstractService *target) : stateSkip(0),
                           state(Scpd), parent(parent), service(target), action(0),
                           stateVariable(0), argument(0)
{
}
