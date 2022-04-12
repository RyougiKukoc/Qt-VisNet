#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DATA_MANAGER_LIB)
#  define DATA_MANAGER_EXPORT Q_DECL_EXPORT
# else
#  define DATA_MANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define DATA_MANAGER_EXPORT
#endif
