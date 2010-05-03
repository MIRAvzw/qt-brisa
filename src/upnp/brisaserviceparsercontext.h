#ifndef _BRISASERVICEPARSERCONTEXT_H
#define _BRISASERVICEPARSERCONTEXT_H

#include "brisaaction.h"
#include "brisaargument.h"
#include "brisastatevariable.h"
#include "brisaabstractservice.h"
#include "brisaglobal.h"

namespace BrisaUpnp {

typedef enum {
    ServiceStart,
    Scpd,
    ServiceSpecVersion,
    ServiceSpecVersionMajor,
    ServiceSpecVersionMinor,
    ActionList,
    Action,
    ActionName,
    ArgumentList,
    Argument,
    ArgumentName,
    ArgumentDirection,
    RelatedStateVariable,
    ServiceStateTable,
    StateVariable,
    StateVariableName,
    StateVariableDataType,
    StateVariableDefaultValue,
    StateVariableAllowedValueList,
    StateVariableAllowedValue,
    StateVariableAllowedValueRange,
    StateVariableAllowedValueRangeMinimum,
    StateVariableAllowedValueRangeMaximum,
    StateVariableAllowedValueRangeStep,
    ServiceFinished,
    ServiceError = -1
} saxParserState;

class BRISA_UPNP_EXPORT BrisaServiceParserContext {
public:
    BrisaServiceParserContext(BrisaServiceParserContext *parent = 0,
            BrisaAbstractService *target = 0);

    BrisaAction *getAction(void) {
        return action;
    }
    BrisaAbstractService *getService(void) {
        return service;
    }
    BrisaStateVariable *getStateVariable(void) {
        return stateVariable;
    }
    BrisaArgument *getArgument(void) {
        return argument;
    }

    inline void setAction(BrisaAction *action) {
        this->action = action;
    }
    inline void setService(BrisaAbstractService *service) {
        this->service = service;
    }
    inline void setStateVariable(BrisaStateVariable *stateVariable) {
        this->stateVariable = stateVariable;
    }
    inline void setArgument(BrisaArgument *argument) {
        this->argument = argument;
    }

    inline bool hasParent(void) {
        return (parent != 0);
    }
    inline BrisaServiceParserContext *getParent(void) {
        return parent;
    }

    int stateSkip;
    saxParserState state;

private:
    BrisaServiceParserContext *parent;
    BrisaAbstractService *service;
    BrisaAction *action;
    BrisaStateVariable *stateVariable;
    BrisaArgument *argument;
};

}

#endif /* _BRISASERVICEPARSERCONTEXT_H */
