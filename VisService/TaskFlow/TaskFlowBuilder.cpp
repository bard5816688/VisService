#include "TaskFlowBuilder.h"
#include "CGrapExtension/PipeLineUi.h"
#include "./Module/Matching/ShapeMatching.h"
#include "./Module/Matching/ShapeMatchingUi.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlowBuilder::TaskFlowBuilder()
{
}

TaskFlowBuilder::~TaskFlowBuilder()
{
	for (auto ui : pipeLineUiMap_)
	{
		if (ui.second)
		{
			delete ui.second;
		}
	}
	pipeLineUiMap_.clear();
}

Return<std::shared_ptr<PipeLine>> TaskFlowBuilder::GetPipeLine(const std::string& pipeLineName)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pipeLineMap_.contains(pipeLineName))
	{
		return pipeLineMap_.at(pipeLineName);
	}
#ifdef USE_PREDEFINED_PIPELINE
	std::shared_ptr<PipeLine> pipeLine = std::make_shared<PipeLine>();
	pipeLine->setName(pipeLineName);
	if (pipeLineName == "DispensingMatching")
	{
		BuildDispensingMatching(pipeLine);
	}
	else if (pipeLineName == "PostDispensingInspectionNormal")
	{
		BuildPostDispensingInspectionNormal(pipeLine);
	}
	else
	{
		return VIS_RETURN_UNEXPECTED(ModuleErrorCode::TaskFlow, ErrorCode::SystemError, "Cannot support task flow type", "TaskFlow::GetTaskName()");
	}
#elif
	return BuildFromJson(pipeLineName);
#endif
	pipeLineMap_[pipeLineName] = pipeLine;
	return pipeLine;
}

Return<QWidget*> TaskFlowBuilder::GetPipeLineUi(const std::string& pipeLineName)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pipeLineUiMap_.contains(pipeLineName))
	{
		return pipeLineUiMap_.at(pipeLineName);
	}
#ifdef USE_PREDEFINED_PIPELINE
	PipeLineUi* pipeLineUi = new PipeLineUi();
	if (pipeLineName == "DispensingMatching")
	{
		BuildDispensingMatchingUi(pipeLineUi);
	}
	else if (pipeLineName == "PostDispensingInspectionNormal")
	{
		BuildPostDispensingInspectionNormalUi(pipeLineUi);
	}
	else
	{
		return VIS_RETURN_UNEXPECTED(ModuleErrorCode::TaskFlow, ErrorCode::SystemError, "Cannot support task flow type", "TaskFlow::GetTaskName()");
	}
#elif
	return BuildFromJson(pipeLineName);
#endif
	pipeLineUiMap_[pipeLineName] = pipeLineUi;
	return pipeLineUi;
}

ReturnVoid TaskFlowBuilder::BuildDispensingMatching(const std::shared_ptr<PipeLine>& pipeLine)
{
	VIS_RETURN_IF_UNEXPECTED(ShapeMatching, ModuleRegistry::Instance().CreateLogic("ShapeMatching"));
	auto status = pipeLine->RegisterGNode(*ShapeMatching, {}, "形状匹配");
	pipeLine->dump();
	return ReturnVoid();
}

ReturnVoid TaskFlowBuilder::BuildDispensingMatchingUi(PipeLineUi* pipelineUi)
{
	VIS_RETURN_IF_UNEXPECTED(ShapeMatchingUi, ModuleRegistry::Instance().CreateUi("ShapeMatching", nullptr));
	pipelineUi->RegisterNode(*ShapeMatchingUi, "形状匹配");
	return ReturnVoid();
}

ReturnVoid TaskFlowBuilder::BuildPostDispensingInspectionNormal(const std::shared_ptr<PipeLine>& pipeLine)
{
	return ReturnVoid();
}

ReturnVoid TaskFlowBuilder::BuildPostDispensingInspectionNormalUi(PipeLineUi* pipelineUi)
{
	return ReturnVoid();
}


TaskFlowBuilder& GlobalTaskFlowBuilder()
{ 
	static TaskFlowBuilder s_builder;
	return s_builder;
}

VISSERVICE_NAMESPACE_END