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

template<typename T>
concept RuleOfFive =
std::copy_constructible<T> &&              // 1. 拷贝构造
std::is_copy_assignable_v<T> &&            // 2. 拷贝赋值
std::move_constructible<T> &&              // 3. 移动构造
std::is_move_assignable_v<T> &&            // 4. 移动赋值
std::is_destructible_v<T>;                 // 5. 析构函数


#define USE_HALCON