#pragma once
#include "BasicDefs.h"
#include "CGraph.h"
#include <unordered_map>
#include <string>
#include <any>
#include <memory>

VISSERVICE_NAMESPACE_BEGIN

class BaseNode : public CGraph::GNode 
{
public:
    using IoValue = std::any;
    BaseNode(std::string taskName)
        : taskName_(taskName)
    {

    }
    virtual ~BaseNode() = default;
    void setId(const std::string& id) { id_ = id; }
    std::string getId() const { return id_; }
    void bindInput(const std::string& inputKey, IoValue* sourcePtr) 
    {
        inputRefs_[inputKey] = sourcePtr;
    }
    void resolveInputs() 
    {
        for (auto& [key, ref] : inputRefs_) 
        {
            if (ref)
            {
                inputs_[key] = *ref;
            }
        }
    }
	virtual CStatus init() { return CStatus(); }
    virtual CStatus run() = 0;

protected:
    std::string id_;
    std::unordered_map<std::string, IoValue> inputs_;
    std::unordered_map<std::string, IoValue> outputs_;
    std::string taskName_;

private:
    std::unordered_map<std::string, IoValue*> inputRefs_;
};


VISSERVICE_NAMESPACE_END