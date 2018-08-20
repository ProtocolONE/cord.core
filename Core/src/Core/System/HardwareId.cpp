#include <Core/System/HardwareId.h>

#include <QtCore/QMutexLocker>

namespace P1 {
  namespace Core {
    namespace System {

      QString HardwareId::_hwid = "";
      bool HardwareId::_isInitialized = false;
      QMutex HardwareId::_mutex;

      HardwareId::HardwareId()
      {
      }

      HardwareId::~HardwareId()
      {
      }

      const QString& HardwareId::value()
      {
        if (_isInitialized)
          return _hwid;

        QMutexLocker locker(&_mutex);

        if (_isInitialized)
          return _hwid;

        _hwid = "HWID"; // UNDON implement this
        _isInitialized = true;

        return _hwid;
      }

    }
  }
}