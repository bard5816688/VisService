#pragma once

#define VISALGORITHM_NAMESPACE_BEGIN                                          \
namespace VisAlgorithm {                                                      \

#define  VISALGORITHM_NAMESPACE_END                                           \
}

#ifndef VISALGORITHM_EXPORTS
#define VisAlgorithmApi __declspec(dllimport)
#else
#define VisAlgorithmApi __declspec(dllexport)
#endif

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
concept RuleOfFive =
std::copy_constructible<T> &&
std::is_copy_assignable_v<T> &&
std::move_constructible<T> &&
std::is_move_assignable_v<T> &&
std::is_destructible_v<T>;

VISALGORITHM_NAMESPACE_END

#define USE_HALCON