#include "PipeLine.h"

VISSERVICE_NAMESPACE_BEGIN

ReturnVoid PipeLine::RegisterGNode(ModuleBase* nodePtr,
	const std::set<ModuleBase*>& depends,
	const std::string& name,
	CSize loop)
{
	auto ele = reinterpret_cast<CGraph::GElementPPtr>(&nodePtr);
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
	registerGNode(ele, dependsGElementPtrSet, name, loop);

	registedModules_.insert(std::make_pair(name, nodePtr));
}

Return<QJsonObject> PipeLine::GetResult()
{

}

VISSERVICE_NAMESPACE_END