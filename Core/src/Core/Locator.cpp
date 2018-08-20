#include <Core/Locator.h>

namespace P1 {
  namespace Core {
    Locator::Locator()
    {
      this->_services.clear();
    }

    Locator::~Locator()
    {
    }

    void Locator::RegisterService(const QString &name, QObject *service)
    {
      this->_services[name] = service;
    }

    QObject * Locator::Locate(const QString &name)
    {
      if (this->_services.contains(name)) 
        return this->_services[name];

      return 0;
    }
  }
}
