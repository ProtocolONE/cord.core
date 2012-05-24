#ifndef _GGS_CORE_GLOBAL_H
#define _GGS_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__
#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__
#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

#ifdef CORE_LIB
# define CORE_EXPORT Q_DECL_EXPORT
#else
# define CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // _GGS_CORE_GLOBAL_H
