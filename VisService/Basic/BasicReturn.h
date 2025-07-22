#pragma once

#include <string>
#include "Expected.hpp"
#include "BasicDefs.h"

VISSERVICE_NAMESPACE_BEGIN
enum class ErrorCode
{
	None,
	Unknown,
	NullPointer,
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
using Return = tl::expected<T, ErrorInfo>;
using ReturnVoid = tl::expected<void, ErrorInfo>;

#define _IS_NULLPTR(ptr) (std::is_pointer<decltype(ptr)>::value && !(ptr))

#define VIS_RETURN_IF_NULLPTR(ptr)                                                              \
{                                                                                               \
    if (_IS_NULLPTR(ptr))                                                                         \
    {                                                                                           \
        return tl::unexpected(ErrorInfo(__func__, "Null Pointer!", ErrorCode::NullPointer));    \
    }                                                                                           \
}

#define VIS_RETURN_IF_NULLPTR_WITH_MSG(ptr, ...)                                                \
{                                                                                               \
    if (_IS_NULLPTR(ptr))                                                                         \
    {                                                                                           \
        return tl::unexpected(ErrorInfo(__func__, ##__VA_ARGS__, ErrorCode::NullPointer));      \
    }                                                                                           \
}

#define VIS_RETURN_UNEXPECTE(procName, errormsg, errorCode) tl::unexpected(ErrorInfo(procName, errormsg, errorCode))

VISSERVICE_NAMESPACE_END