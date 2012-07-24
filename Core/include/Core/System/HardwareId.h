/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_CORE_SYSTEM_HARDWAREID_H_
#define _GGS_CORE_SYSTEM_HARDWAREID_H_

#include <Core/core_global>

#include <QtCore/QString>
#include <QtCore/QMutex>

namespace GGS {
  namespace Core {
    namespace System {

      class CORE_EXPORT HardwareId
      {
      public:
        static const QString& value();

      private:
        HardwareId();
        ~HardwareId();

        static QString _hwid;
        static bool _isInitialized;
        static QMutex _mutex;
      };
    }
  }
}

#endif //_GGS_CORE_SYSTEM_HARDWAREID_H_