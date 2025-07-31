#pragma once
#include "../../Component/CGraph/CGraph.h"
#include "../../Basic/BasicObject.h"

VISSERVICE_NAMESPACE_BEGIN

class ModuleBase;
class PipeLine : public CGraph::GPipeline
{
public:
    ReturnVoid RegisterGNode(ModuleBase* nodePtr,
        const std::set<ModuleBase*>& depends = std::initializer_list<ModuleBase*>(),
        const std::string& name = "",
        CSize loop = 1);

	Return<QJsonObject> GetResult();

private:
	std::unordered_map<std::string, ModuleBase*> registedModules_;

};

VISSERVICE_NAMESPACE_END