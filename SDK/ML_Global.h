#pragma once
#ifndef BUILD_STATIC
# if defined(DEVICE_LIBRARY_LIB)
#  define DEVICE_LIBRARY_API Q_DECL_EXPORT
# else
#  define DEVICE_LIBRARY_API Q_DECL_IMPORT
# endif
#else
# define DEVICE_LIBRARY_API
#endif
