#include "ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

ModuleBase::ModuleBase()
{
    pipelineName_ = "";
}

void ModuleBase::SetPipeLineName(const std::string& pipelineName)
{
    pipelineName_ = pipelineName;
}

void ModuleBase::SetModuleName(const std::string& moduleName)
{
    moduleName_ = moduleName;
}

ModuleUiBase::ModuleUiBase(QWidget* parent)
    : QWidget(parent)
{
    pipelineName_ = "";
}

void ModuleUiBase::SetPipeLineName(const std::string& pipelineName)
{
    pipelineName_ = pipelineName;
}

void ModuleUiBase::SetModuleName(const std::string& moduleName)
{
    moduleName_ = moduleName;
}

VISSERVICE_NAMESPACE_END