#pragma once
#include "../../Basic/BasicObject.h"
#include "../../CGraph/CGraph.h"
#include <QPointF>
#include "VisAlgorithm.h"
#include "ReflectableStruct.h"

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
using ModuleInputParamPath = std::pair<std::string, T>;

template<typename T>
class GParam :public CGraph::GParam
{
public:
    T value_;

};

class ModuleBase : public CGraph::GNode
{
public:
	virtual std::vector<std::string> GetOutputParamNames() = 0;

};


#define CREATE_GPARAM(type, member) CGRAPH_CREATE_GPARAM(type, #member)


inline std::pair<std::string, std::string> splitInputParamsPath(const std::string& str)
{
    size_t dotPos = str.find('.');
    // 检查输入是否符合 "struct.member" 格式
    assert(dotPos == std::string::npos || dotPos == 0 || dotPos == str.length() - 1);
    std::string structName = str.substr(0, dotPos);
    std::string memberName = str.substr(dotPos + 1);
    return std::make_pair(structName, memberName);
}

VISSERVICE_NAMESPACE_END