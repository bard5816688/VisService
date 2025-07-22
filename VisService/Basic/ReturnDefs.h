#pragma once
#include "Expected.hpp"
#include "ErrorCode.h"

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
using Return = tl::expected<T, ErrorParams>;
using ReturnVoid = tl::expected<void, ErrorParams>;

#define _IS_NULLPTR(ptr) (std::is_pointer<decltype(ptr)>::value && !(ptr))

#define VIS_RETURN_UNEXPECTED(moduleErrorCode, errorCode, errorMsg, procName) tl::unexpected({.moduleErrorCode_ = moduleErrorCode, .errorCode_ = errorCode, .errorMsg_ = errorMsg, .procName_ = procName})

#define VIS_RETURN_IF_NULLPTR_WITH_MSG(module_, ptr, ...)                                               \
{                                                                                                       \
    if (_IS_NULLPTR(ptr))                                                                               \
    {                                                                                                   \
        return VIS_RETURN_UNEXPECTED(module_, ErrorCode::NullPointer, ##__VA_ARGS__, __func__);         \
    }                                                                                                   \
}

VISSERVICE_NAMESPACE_END