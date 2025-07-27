#pragma once
#include <unordered_map>
#include "BindingContext.h"

VISSERVICE_NAMESPACE_BEGIN

struct BindingInfo 
{
    enum class SourceType 
    {
        GlobalVar,
        ModuleOutput
    };

    SourceType type;
	std::string sourceId_;  // 对于 ModuleOutput：表示来源模块
    std::string key_;       // 全局变量名 或 输出键名
};


class BaseModule;
class BindingResolver : public BindingContext
{
public:
    virtual QVariant ResolveInput(const std::string& moduleName, const std::string& inputKey) override;
    virtual void FillAllInputs(BaseModule* module, const std::string& moduleName) override;

    void RegisterBinding(const std::string& moduleName, const std::string& inputKey, const BindingInfo& info);
	void AddModule(const std::string& moduleName, BaseModule* module);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, BindingInfo>> bindingMap_;
    std::unordered_map<std::string, BaseModule*> moduleMap_;
    std::unordered_map<std::string, QVariant> globalVars_;
};

VISSERVICE_NAMESPACE_END