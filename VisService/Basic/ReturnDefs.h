#pragma once
#include "Expected.hpp"
#include "ErrorCode.h"

namespace tl
{
    template<typename T>
    struct is_expected : std::false_type {};

    template<typename T>
    struct is_expected<tl::expected<T, VisService::ErrorParams>> : std::true_type {};
}

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
using Return = tl::expected<T, ErrorParams>;
using ReturnVoid = tl::expected<void, ErrorParams>;

#define _IS_NULLPTR(ptr) (std::is_pointer<decltype(ptr)>::value && !(ptr))

#define VIS_RETURN_UNEXPECTED(moduleErrorCode, errorCode, errorMsg, procName) \
    tl::unexpected<ErrorParams>(ErrorParams(moduleErrorCode, errorCode, errorMsg, procName))

#define VIS_RETURN_IF_NULLPTR_WITH_MSG(ptr, moduleErrorCode_, ...)                                               \
{                                                                                                       \
    if (_IS_NULLPTR(ptr))                                                                               \
    {                                                                                                   \
        return VIS_RETURN_UNEXPECTED(moduleErrorCode_, ErrorCode::NullPointer, ##__VA_ARGS__, __func__);         \
    }                                                                                                   \
}

#define VIS_RETURN_IF_UNEXPECTED(res, expr)                             \
    auto res = (expr);                                                  \
    static_assert(tl::is_expected<decltype(res)>::value,                \
        #res " must be tl::expected<T, ErrorInfo>");                    \
    if (!res)                                                           \
        return tl::unexpected(res.error());


VISSERVICE_NAMESPACE_END