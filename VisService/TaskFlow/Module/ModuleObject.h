#pragma once
#include "../../Basic/BasicObject.h"
#include "../../Component/CGraph/CGraph.h"
#include "../../Component/ParamManager/ParamManager .h"
#include "VisAlgorithm.h"
#include "ReflectableStruct.h"
#include "ModuleRegistry .h"
#include <QPointF>
#include <QWidget>

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
    ModuleBase(const std::string& taskName)
        : taskName_(taskName)
    {
    }
    virtual~ModuleBase() = default;
    virtual std::string GetModuleName() = 0;
	virtual std::vector<std::string> GetOutputParamNames() = 0;

protected:
    std::string taskName_;
};

class ModuleUiBase : public QWidget
{
    Q_OBJECT

public:
	ModuleUiBase(const std::string& taskName, QWidget* parent)
        : QWidget(parent)
        , taskName_(taskName)
    {
    }
    virtual~ModuleUiBase() = default;
    virtual std::string GetModuleName() = 0;

protected:
    std::string taskName_;
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