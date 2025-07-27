#pragma once
#include "../../Basic/BasicObject.h"
#include "CGraph.h"
#include <cassert>
#include "../Bingding/BindingContext.h"

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
using ModuleInputParamsMember = std::pair<std::string, T>;

inline std::pair<std::string, std::string> splitInputParamsPath(const std::string& str)
{
    size_t dotPos = str.find('.');
    // 检查输入是否符合 "struct.member" 格式
    assert(dotPos == std::string::npos || dotPos == 0 || dotPos == str.length() - 1);
    std::string structName = str.substr(0, dotPos);
    std::string memberName = str.substr(dotPos + 1);
    return std::make_pair(structName, memberName);
}


class BaseModule : public CGraph::GNode
{
public:
	virtual void SetInputParam(const std::string& key, const QVariant& value) = 0;
	virtual QVariant GetOutParam(const std::string& key) = 0;
    void setBindingContext(BindingContext* ctx);

private:
    BindingContext* bindingContext_ = nullptr;

};

VISSERVICE_NAMESPACE_END