#pragma once
#include "CGrapExtension/PipelineFactory.h"

#define USE_PREDEFINED_PIPELINE

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowBuilder
{
public:
	Return<std::shared_ptr<PipeLine>> GetPipeLine(const std::string& pipeLineName);
	Return<QWidget*> GetPipeLineUi(const std::string& pipeLineName, QWidget* parent);

private:
#ifdef USE_PREDEFINED_PIPELINE
	Return<std::shared_ptr<PipeLine>> BuildDispensingMatching(const std::string& pipeLineName);
	Return<std::shared_ptr<PipeLine>> BuildPostDispensingInspectionNormal(const std::string& pipeLineName);

#elif
	static Return<std::shared_ptr<PipeLine>> BuildFromJson(const std::string& pipeLineName);
#endif

private:
	std::unordered_map<std::string, std::shared_ptr<PipeLine>> cache_;
	std::mutex mutex_;

};

TaskFlowBuilder& GlobalTaskFlowBuilder();

VISSERVICE_NAMESPACE_END