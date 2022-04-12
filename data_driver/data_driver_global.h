#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DATA_DRIVER_LIB)
#  define DATA_DRIVER_EXPORT Q_DECL_EXPORT
# else
#  define DATA_DRIVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define DATA_DRIVER_EXPORT
#endif
