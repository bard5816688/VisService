#include "BindingResolver.h"
#include "../Module/ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

QVariant BindingResolver::ResolveInput(const std::string& moduleName, const std::string& inputKey)
{
    if (!bindingMap_.contains(moduleName) || !bindingMap_[moduleName].contains(inputKey))
    {
        return {};
    }
    const BindingInfo& info = bindingMap_[moduleName][inputKey];
    if (info.type == BindingInfo::SourceType::GlobalVar) 
    {
        return globalVars_.contains(info.key_) ? globalVars_.at(info.key_) : QVariant{};
    }
    else if (info.type == BindingInfo::SourceType::ModuleOutput) 
    {
        if (!moduleMap_.contains(info.sourceId_)) return {};
        BaseModule* src = moduleMap_.at(info.sourceId_);
        return src->GetOutParam(info.key_);
    }
    return {};
}

void BindingResolver::FillAllInputs(BaseModule* module, const std::string& moduleName)
{
    if (!bindingMap_.contains(moduleName)) return;
    for (const auto& [inputKey, _] : bindingMap_[moduleName]) 
    {
        QVariant val = ResolveInput(moduleName, inputKey);
        module->SetInputParam(inputKey, val);
    }
}

void BindingResolver::RegisterBinding(const std::string& nodeId, const std::string& inputKey, const BindingInfo& info)
{
	bindingMap_[nodeId][inputKey] = info;
}

void BindingResolver::AddModule(const std::string& moduleName, BaseModule* module)
{
	moduleMap_.insert(std::make_pair(moduleName, module));
}

VISSERVICE_NAMESPACE_END