#ifndef _GGS_CORE_CORE_H
#define _GGS_CORE_CORE_H

#include <Core/core_global.h>
#include <QObject>
#include <QMap>

namespace GGS {
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

#endif // _GGS_CORE_CORE_H
