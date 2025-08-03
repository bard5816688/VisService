#include "PipeLine.h"
#include "../Module/ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

ReturnVoid PipeLine::RegisterModule(ModuleBase* module,
	const std::set<ModuleBase*>& depends,
	const std::string& moduleName,
	CSize loop)
{
	auto ele = reinterpret_cast<CGraph::GElementPPtr>(&module);
    CGraph::GElementPtrSet dependsGElementPtrSet;
    std::transform(
        depends.begin(),
        depends.end(),
        std::inserter(dependsGElementPtrSet, dependsGElementPtrSet.end()),
        [](ModuleBase* d) -> CGraph::GElementPtr 
        {
            return static_cast<CGraph::GElementPtr>(d);
        }
    );
	registerGNode(ele, dependsGElementPtrSet, moduleName, loop);

	registedModules_.insert(std::make_pair(moduleName, module));
}

ReturnVoid PipeLine::Initialize(const std::string& pipelineName)
{
	for (auto module : registedModules_)
    {
        module.second->SetPipeLineName(pipelineName);
        module.second->SetModuleName(module.first);
    }
    init();
}

Return<QJsonObject> PipeLine::GetResult()
{

}

PipeLine::PipeLine()
    : CGraph::GPipeline()
{

}

PipeLine::~PipeLine()
{

}


VISSERVICE_NAMESPACE_END