#include "TaskFlowBuilder.h"
#include "./Module/Matching/ShapeMatching.h"
#include "./Module/Matching/ShapeMatchingUi.h"

VISSERVICE_NAMESPACE_BEGIN



TaskFlowBuilder& GlobalTaskFlowBuilder()
{
	static TaskFlowBuilder s_builder;
	return s_builder;
}

VISSERVICE_NAMESPACE_END