#include "PipelineFactory.h"

VISSERVICE_NAMESPACE_BEGIN

std::unordered_map <std::string, PipeLine*> PipelineFactory::s_pipeLineMap_;
std::mutex PipelineFactory::s_lock_;

PipeLine* PipelineFactory::Create(const std::string& lineName)
{
    auto pipeline = new PipeLine;
    {
        std::lock_guard<std::mutex> lock(s_lock_);
		s_pipeLineMap_.insert(std::make_pair(lineName, pipeline));
    }
    return pipeline;
}


ReturnVoid PipelineFactory::Remove(const std::string& lineName)
{
    std::lock_guard<std::mutex> lock(s_lock_);
    auto line = s_pipeLineMap_.find(lineName);
    if (line != s_pipeLineMap_.end())
    {
        if (s_pipeLineMap_.at(lineName) != nullptr)
        {
            delete s_pipeLineMap_.at(lineName);
        }
    }
    s_pipeLineMap_.erase(lineName);
}


ReturnVoid PipelineFactory::Clear() 
{
    std::lock_guard<std::mutex> lock(s_lock_);
    for (auto pipeline : s_pipeLineMap_)
    {
        if (pipeline.second)
        {
            delete pipeline.second;
        }
    }
    s_pipeLineMap_.clear();
}

VISSERVICE_NAMESPACE_END