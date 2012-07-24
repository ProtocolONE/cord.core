/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <Core/System/HardwareId.h>

#include <HWID/utilities.h>

#include <QtCore/QMutexLocker>

namespace GGS {
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

        std::wstring whwid;
        if (Syncopate::Common::GetHWID(whwid)) {
          _hwid = QString::fromStdWString(whwid);
          _isInitialized = true;
        }

        return _hwid;
      }

    }
  }
}