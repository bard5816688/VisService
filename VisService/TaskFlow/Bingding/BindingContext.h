#pragma once
#include <QVariant>
#include "../../Basic/ReturnDefs.h"

VISSERVICE_NAMESPACE_BEGIN

class BaseModule;
class BindingContext 
{
public:
    virtual ~BindingContext() = default;
    virtual QVariant ResolveInput(const std::string& moduleName, const std::string& inputKey) = 0;
    virtual void FillAllInputs(BaseModule* module, const std::string& moduleName) = 0;

};

VISSERVICE_NAMESPACE_END