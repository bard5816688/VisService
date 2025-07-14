#pragma once

#include "BasicReturn.h"
#include "HalconCpp.h"

namespace tl
{
    template<typename T>
    struct is_expected : std::false_type {};

    template<typename T, typename E>
    struct is_expected<tl::expected<T, E>> : std::true_type {};
}

VISALGORITHM_NAMESPACE_BEGIN

#define VISALGORITHM__RETURN_UNEXPECTE(procName, errormsg, errorCode) tl::unexpected(ErrorInfo(procName, errormsg, errorCode))

template<typename Func>
inline auto WrapTryCatch(const std::string& funcName, Func&& func) -> Result<decltype(func())>
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
    catch (const std::exception& e)
    {
        return VISALGORITHM__RETURN_UNEXPECTE(funcName.c_str(), e.what(), ErrorCode::StdExcepetion);
    }
    catch (const HalconCpp::HException& e)
    {
        return VISALGORITHM__RETURN_UNEXPECTE(funcName.c_str(), e.ErrorMessage().Text(), ErrorCode::HalconExcepetion);
    }
    catch (...)
    {
        return VISALGORITHM__RETURN_UNEXPECTE(funcName.c_str(), "Unknown exception caught", ErrorCode::Unknown);
    }
}

#define VISALGORITHM_WRAP_TRY_CATCH(expr) \
    WrapTryCatch(__func__, [=]() -> decltype(expr) { return (expr); })

#define VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(varName, expr)                \
    auto varName = VISALGORITHM_WRAP_TRY_CATCH(expr);                                                  \
    static_assert(tl::is_expected<decltype(varName)>::value,                \
        #varName " must be tl::expected<T, ErrorInfo>");                    \
    if (!varName)                                                           \
        return tl::unexpected(varName.error());


VISALGORITHM_NAMESPACE_END