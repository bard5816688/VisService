#pragma once
#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(VISSERVICE_LIB)
#  define VISSERVICE_EXPORT Q_DECL_EXPORT
# else
#  define VISSERVICE_EXPORT Q_DECL_IMPORT
# endif
#else
# define VISSERVICE_EXPORT
#endif


#define VISSERVICE_NAMESPACE_BEGIN                                          \
namespace VisService {                                                      \

#define  VISSERVICE_NAMESPACE_END                                           \
}   

VISSERVICE_NAMESPACE_BEGIN

template<typename T>
concept RuleOfFive =
std::copy_constructible<T> &&
std::is_copy_assignable_v<T> &&
std::move_constructible<T> &&
std::is_move_assignable_v<T> &&
std::is_destructible_v<T>;

VISSERVICE_NAMESPACE_END