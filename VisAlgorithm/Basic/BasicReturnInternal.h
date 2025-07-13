#pragma once

#include "BasicReturn.h"
#include "HalconCpp.h"

VISALGORITHM_NAMESPACE_BEGIN

#define VISALGORITHM_ERROR(procName, errormsg, errorCode) tl::unexpected(ErrorInfo(procName, errormsg, errorCode))

#define WRAP_HALCON_TRY(expr) \
    WrapHalconTry(__func__, [=]() -> decltype(expr) { return (expr); })

template<typename Func>
inline auto WrapHalconTry(const std::string& funcName, Func&& func) -> Result<decltype(func())>
{
    using Ret = decltype(func());
    try
    {
        if constexpr (std::is_void_v<Ret>)
        {
            func();
            return  Result<Ret>{};
        }
        else
        {
            return  Result<Ret>{ func() };
        }
    }
    catch (const HalconCpp::HException& e)
    {
        return VISALGORITHM_ERROR(funcName.c_str(), e.ErrorMessage().Text(), ErrorCode::HalconExcepetion);
    }
    catch (...)
    {
        return VISALGORITHM_ERROR(funcName.c_str(), "Unknown exception caught", ErrorCode::Unknown);
    }
}

VISALGORITHM_NAMESPACE_END