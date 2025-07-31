#pragma once
#include "../../Basic/BasicObject.h"
#include "../../Component/CGraph/CGraph.h"
#include "PipeLine.h"

VISSERVICE_NAMESPACE_BEGIN

class PipelineFactory
{
public:
    static PipeLine* Create(const std::string& lineName);
    static ReturnVoid Remove(const std::string& lineName);
    static ReturnVoid Clear();

private:
	static std::unordered_map <std::string, PipeLine*> s_pipeLineMap_;
    static std::mutex s_lock_;

};

VISSERVICE_NAMESPACE_END