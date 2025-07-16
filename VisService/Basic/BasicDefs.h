#pragma once
#include <QtCore/qglobal.h>
#include "CGraph.h"

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