#pragma once
#include "CGrapExtension/PipeLine.h"
#include "CGrapExtension/PipeLineUi.h"

#define USE_PREDEFINED_PIPELINE

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowBuilder
{
public:
	TaskFlowBuilder();
	~TaskFlowBuilder();
	Return<std::shared_ptr<PipeLine>> GetPipeLine(const std::string& pipeLineName);
	Return<QWidget*> GetPipeLineUi(const std::string& pipeLineName);

private:
#ifdef USE_PREDEFINED_PIPELINE
	ReturnVoid BuildDispensingMatching(const std::shared_ptr<PipeLine>& pipeLine);
	ReturnVoid BuildDispensingMatchingUi(PipeLineUi* pipelineUi);
	ReturnVoid BuildPostDispensingInspectionNormal(const std::shared_ptr<PipeLine>& pipeLine);
	ReturnVoid BuildPostDispensingInspectionNormalUi(PipeLineUi* pipelineUi);

#elif
	Return<std::shared_ptr<PipeLine>> BuildFromJson(const std::string& pipeLineName);
#endif

private:
	std::unordered_map<std::string, std::shared_ptr<PipeLine>> pipeLineMap_;
	std::unordered_map<std::string, QWidget*> pipeLineUiMap_;
	std::mutex mutex_;

};

TaskFlowBuilder& GlobalTaskFlowBuilder();

VISSERVICE_NAMESPACE_END