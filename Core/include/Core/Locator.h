#pragma once

#include <Core/core_global.h>
#include <QtCore/QObject>
#include <QtCore/QMap>

namespace P1 {
  namespace Core {
    class CORE_EXPORT Locator
    {
    public:
      Locator();
      ~Locator();

      void RegisterService(const QString &name, QObject *service);
      QObject *Locate(const QString &name);

    private:
      QMap<QString, QObject*> _services;
    };
  }
}

