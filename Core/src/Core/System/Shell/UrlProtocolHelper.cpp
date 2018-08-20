#include <Core/System/Shell/UrlProtocolHelper.h>

#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

namespace P1 {
  namespace Core {
    namespace System {
      namespace Shell {

        UrlProtocolHelper::UrlProtocolHelper()
        {
        }

        UrlProtocolHelper::~UrlProtocolHelper()
        {
        }

        void UrlProtocolHelper::registerProtocol(const QString& name)
        {
          QString key = QString("HKEY_CLASSES_ROOT\\%1").arg(name);
          QString exe = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());

          QSettings settings(key, QSettings::NativeFormat);
          settings.setValue("URL Protocol", "");
          
          settings.beginGroup("DefaultIcon");
          settings.setValue(".", QString("\"%1\",0").arg(exe));
          settings.endGroup();

          settings.beginGroup("shell");
          settings.beginGroup("open");
          settings.beginGroup("command");
          settings.setValue(".", QString("\"%1\" \"/uri:%2\"").arg(exe, "%1"));
        }
      }
    }
  }
}