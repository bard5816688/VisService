#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(VISCAPTURE_LIB)
#  define VISCAPTURE_EXPORT Q_DECL_EXPORT
# else
#  define VISCAPTURE_EXPORT Q_DECL_IMPORT
# endif
#else
# define VISCAPTURE_EXPORT
#endif
