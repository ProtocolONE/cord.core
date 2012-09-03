#pragma once

#include <Core/core_global>

#include <QtCore/QString>

namespace GGS{
  namespace Core {
    namespace System {
      namespace Shell {

        class CORE_EXPORT UrlProtocolHelper
        {
        public:

          /*!
            \fn static void UrlProtocolHelper::registerProtocol(const QString& name);
            \brief Registers the url protocol described by name.
            \author Ilya.Tkachenko
            \date 03.09.2012
            \param name The name.
          */
          static void registerProtocol(const QString& name);

        private:
          UrlProtocolHelper();
          ~UrlProtocolHelper();
        };
      }
    }
  }
}