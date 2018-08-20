#pragma once

#include <Core/core_global.h>

#include <QtCore/QString>
#include <QtCore/QMutex>

namespace P1 {
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
