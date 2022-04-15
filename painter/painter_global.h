#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PAINTER_LIB)
#  define PAINTER_EXPORT Q_DECL_EXPORT
# else
#  define PAINTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define PAINTER_EXPORT
#endif
