#pragma once

#include <string>
#include "Expected.hpp"
#include "BasicDefs.h"

VISSERVICE_NAMESPACE_BEGIN
enum class ErrorCode
{
    None,
    Unknown,
    StdExcepetion,
    HalconExcepetion,
};

class ErrorInfo
{
public:
    ErrorInfo(const char* procName, const char* msg, ErrorCode err)
        : errorCode_(err)
        , errorMsg_(msg)
        , procName_(procName)
    {
    }

    virtual ~ErrorInfo() = default;

    const std::string& ProcName() const
    {
        return procName_;
    }
    const std::string& Message() const
    {
        return errorMsg_;
    }

    ErrorCode Code() const
    {
        return errorCode_;
    }

private:
    ErrorCode errorCode_;
    std::string errorMsg_;
    std::string procName_;
};

template<typename T>
using Result = tl::expected<T, ErrorInfo>;
using ResultVoid = tl::expected<void, ErrorInfo>;

VISSERVICE_NAMESPACE_END