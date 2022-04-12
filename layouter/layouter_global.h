#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LAYOUTER_LIB)
#  define LAYOUTER_EXPORT Q_DECL_EXPORT
# else
#  define LAYOUTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define LAYOUTER_EXPORT
#endif
