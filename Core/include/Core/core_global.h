#pragma once

#include <QtCore/qglobal.h>

#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__
#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__
#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

#ifdef CORE_STATIC_LIB
# define CORE_EXPORT 
#else

#ifdef CORE_LIB
# define CORE_EXPORT Q_DECL_EXPORT
#else
# define CORE_EXPORT Q_DECL_IMPORT
#endif

#endif

