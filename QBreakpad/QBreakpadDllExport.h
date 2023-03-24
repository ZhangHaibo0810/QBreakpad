#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QBREAKPAD_LIB)
#  define QBREAKPAD_EXPORT Q_DECL_EXPORT
# else
#  define QBREAKPAD_EXPORT Q_DECL_IMPORT
# endif
#else
# define QBREAKPAD_EXPORT
#endif
