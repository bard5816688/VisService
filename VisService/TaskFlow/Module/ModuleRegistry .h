#pragma once
#include "../../Basic/ReturnDefs.h"

class QWidget;

VISSERVICE_NAMESPACE_BEGIN

class ModuleBase;
class ModuleRegistry 
{
public:
    using ModuleCreator = std::function<ModuleBase* (const std::string& taskName)>;
    using ModuleUiCreator = std::function<QWidget* (const std::string& taskName, QWidget* parent)>;

    static ModuleRegistry& Instance() 
    {
        static ModuleRegistry registry;
        return registry;
    }

	void RegisterLogic(const std::string& moduleName, ModuleCreator logicCreator)
    {
        logicFactory_[moduleName] = logicCreator;
    }

    void RegisterUi(const std::string& moduleName, ModuleUiCreator uiCreator)
    {
        uiFactory_[moduleName] = uiCreator;
    }

    ModuleBase* CreateLogic(const std::string& moduleName, const std::string& taskName) const
    {
        auto it = logicFactory_.find(moduleName);
        if (it != logicFactory_.end()) 
        {
            return it->second(taskName);
        }
        return nullptr;
    }

	QWidget* CreateUi(const std::string& moduleName, const std::string& taskName, QWidget* parent) const
    {
        auto it = uiFactory_.find(moduleName);
        if (it != uiFactory_.end()) 
        {
			return it->second(taskName, parent);
        }
        return nullptr;
    }

private:
    ModuleRegistry() = default;

private:
    std::unordered_map<std::string, ModuleCreator> logicFactory_;
    std::unordered_map<std::string, ModuleUiCreator> uiFactory_;
};

VISSERVICE_NAMESPACE_END

#define REGISTER_MODULE_LOGIC(ModuleName, LogicType)                        \
namespace                                                                   \
{                                                                           \
    struct ModuleAutoRegisterLogic_##LogicType                             \
    {                                                                       \
        ModuleAutoRegisterLogic_##LogicType()                              \
        {                                                                   \
            ModuleRegistry::Instance().RegisterLogic(                      \
                ModuleName,                                                 \
                [](const std::string& taskName) -> ModuleBase*              \
                {                                                           \
                    return new LogicType(taskName);                         \
                });                                                         \
        }                                                                   \
    };                                                                      \
    static ModuleAutoRegisterLogic_##LogicType g_moduleAutoRegisterLogic_##LogicType; \
}

#define REGISTER_MODULE_UI(ModuleName, UiType)                                  \
namespace                                                                       \
{                                                                               \
    struct ModuleAutoRegisterUi_##UiType                                        \
    {                                                                           \
        ModuleAutoRegisterUi_##UiType()                                         \
        {                                                                       \
            ModuleRegistry::Instance().RegisterUi(                              \
                ModuleName,                                                     \
                [](const std::string& taskName, QWidget* parent) -> QWidget*    \
                {                                                               \
                    return new UiType(taskName, parent);                        \
                });                                                             \
        }                                                                       \
    };                                                                          \
    static ModuleAutoRegisterUi_##UiType g_moduleAutoRegisterUi_##UiType;       \
}
