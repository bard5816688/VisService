#pragma once
#include "../../Basic/ReturnDefs.h"

class QWidget;

VISSERVICE_NAMESPACE_BEGIN

class ModuleBase;
class ModuleRegistry 
{
public:
    using ModuleCreator = std::function<ModuleBase* (void)>;
    using ModuleUiCreator = std::function<ModuleUiBase* (QWidget* parent)>;

    static ModuleRegistry& Instance() 
    {
        static ModuleRegistry registry;
        return registry;
    }

	void RegisterLogic(const std::string& moduleType, ModuleCreator logicCreator)
    {
        logicFactory_[moduleType] = logicCreator;
    }

    void RegisterUi(const std::string& moduleType, ModuleUiCreator uiCreator)
    {
        uiFactory_[moduleType] = uiCreator;
    }

    Return<ModuleBase*> CreateLogic(const std::string& moduleType) const
    {
        auto it = logicFactory_.find(moduleType);
        if (it != logicFactory_.end()) 
        {
            return it->second();
        }
        return nullptr;
    }

	Return<ModuleUiBase*> CreateUi(const std::string& moduleType, ModuleUiBase* parent) const
    {
        auto it = uiFactory_.find(moduleType);
        if (it != uiFactory_.end()) 
        {
			return it->second(parent);
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

#define REGISTER_MODULE_LOGIC(moduleType, logicClass)                        \
namespace                                                                   \
{                                                                           \
    struct ModuleAutoRegisterLogic_##logicClass                             \
    {                                                                       \
        ModuleAutoRegisterLogic_##logicClass()                              \
        {                                                                   \
            ModuleRegistry::Instance().RegisterLogic(                      \
                moduleType,                                                 \
                []() -> ModuleBase*                                         \
                {                                                           \
                    return new logicClass();                                 \
                });                                                         \
        }                                                                   \
    };                                                                      \
    static ModuleAutoRegisterLogic_##logicClass g_moduleAutoRegisterLogic_##logicClass; \
}

#define REGISTER_MODULE_UI(moduleType, uiClass)                                  \
namespace                                                                       \
{                                                                               \
    struct ModuleAutoRegisterUi_##uiClass                                        \
    {                                                                           \
        ModuleAutoRegisterUi_##uiClass()                                         \
        {                                                                       \
            ModuleRegistry::Instance().RegisterUi(                              \
                moduleType,                                                     \
                [](QWidget* parent) -> QWidget*    \
                {                                                               \
                    return new uiClass(parent);                        \
                });                                                             \
        }                                                                       \
    };                                                                          \
    static ModuleAutoRegisterUi_##uiClass g_moduleAutoRegisterUi_##uiClass;       \
}
