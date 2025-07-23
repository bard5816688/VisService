#pragma once
#include "Expected.hpp"
#include "ErrorCode.h"

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
using Return = tl::expected<T, ErrorParams>;
using ReturnVoid = tl::expected<void, ErrorParams>;

#define _IS_NULLPTR(ptr) (std::is_pointer<decltype(ptr)>::value && !(ptr))

#define VIS_RETURN_UNEXPECTED(moduleErrorCode, errorCode, errorMsg, procName) tl::unexpected<ErrorParams>({.moduleErrorCode_ = moduleErrorCode, .errorCode_ = errorCode, .errorMsg_ = errorMsg, .procName_ = procName})

#define VIS_RETURN_IF_NULLPTR_WITH_MSG(ptr, moduleErrorCode_, ...)                                               \
{                                                                                                       \
    if (_IS_NULLPTR(ptr))                                                                               \
    {                                                                                                   \
        return VIS_RETURN_UNEXPECTED(moduleErrorCode_, ErrorCode::NullPointer, ##__VA_ARGS__, __func__);         \
    }                                                                                                   \
}

#define VIS_RETURN_IF_UNEXPECTED(expr)                                  \
    [&]() -> decltype(auto) {                                           \
        auto _result = (expr);                                          \
        if (!_result.has_value())                                       \
            return tl::unexpected(_result.error());                     \
    }()


VISSERVICE_NAMESPACE_END